from __future__ import annotations

import json
import os
import re
import shutil
import subprocess
import tempfile
from pathlib import Path

from conf_parser import merge_structured, parse_known, validate_conf

SAFE_ID = re.compile(r"^[A-Za-z0-9_.+-]+$")
SAFE_FILE = re.compile(r"^[A-Za-z0-9_.+()\- ]+$")


class RepoError(RuntimeError):
    pass


class Repository:
    def __init__(self, root: Path):
        self.root = root.resolve()
        self.problems = self.root / "problems"
        self.template = self.root / "admin" / "templates" / "problem-index.html"
        self.touched: set[str] = set()

    def _id(self, problem_id: str) -> str:
        problem_id = str(problem_id).strip()
        if not problem_id or not SAFE_ID.fullmatch(problem_id) or problem_id in {".", ".."}:
            raise RepoError("题目 ID 只能包含字母、数字、_ . + -")
        return problem_id

    def problem_dir(self, problem_id: str) -> Path:
        pid = self._id(problem_id)
        p = (self.problems / pid).resolve()
        if p.parent != self.problems.resolve():
            raise RepoError("非法题目路径")
        return p

    def raw_dir(self, problem_id: str) -> Path:
        return self.problem_dir(problem_id) / "raw"

    def conf_path(self, problem_id: str) -> Path:
        return self.raw_dir(problem_id) / "problem.conf"

    def _filename(self, name: str) -> str:
        name = str(name).strip()
        if not name or name in {".", "..", "problem.conf", "index.md"}:
            raise RepoError("该文件名不可用于普通题目文件")
        if "/" in name or "\\" in name or not SAFE_FILE.fullmatch(name):
            raise RepoError("文件名包含不允许的字符")
        return name

    @staticmethod
    def _read(path: Path) -> str:
        try:
            return path.read_text(encoding="utf-8")
        except UnicodeDecodeError:
            raise RepoError(f"{path.name} 不是 UTF-8 文本文件")

    @staticmethod
    def _atomic_write(path: Path, text: str):
        path.parent.mkdir(parents=True, exist_ok=True)
        fd, tmp = tempfile.mkstemp(prefix=path.name + ".", suffix=".tmp", dir=path.parent)
        try:
            with os.fdopen(fd, "w", encoding="utf-8", newline="\n") as f:
                f.write(text)
                f.flush()
                os.fsync(f.fileno())
            os.replace(tmp, path)
        finally:
            if os.path.exists(tmp):
                os.unlink(tmp)

    def _rel(self, path: Path) -> str:
        return str(path.resolve().relative_to(self.root)).replace(os.sep, "/")

    def _touch(self, *paths: Path):
        for path in paths:
            try:
                self.touched.add(self._rel(path))
            except ValueError:
                pass

    def _save_conf_with_rebuild(self, path: Path, new_text: str):
        old = self._read(path) if path.exists() else None
        self._atomic_write(path, new_text)
        try:
            result = self.rebuild()
        except Exception:
            if old is None:
                path.unlink(missing_ok=True)
            else:
                self._atomic_write(path, old)
            # Best effort to restore generated files to the previous conf state.
            try:
                self.rebuild()
            except Exception:
                pass
            raise
        self._touch(path, self.problems / "index.json", path.parent / "index.md")
        return result

    def list_problems(self):
        ans = []
        if not self.problems.exists():
            return ans
        for p in self.problems.iterdir():
            if not p.is_dir():
                continue
            conf = p / "raw" / "problem.conf"
            if not conf.exists():
                continue
            try:
                meta = parse_known(self._read(conf))
            except Exception:
                meta = {"title": "", "difficulty": "", "tags": [], "submissions": []}
            # Keep lightweight relationship metadata in the list API so the
            # sidebar can search not only the problem itself, but also every
            # problem that references it from #Link/#Same/#Easy/#Hard/... .
            # Group names are deliberately not hard-coded: every group inside
            # >link participates in search, including future custom groups.
            link_targets = []
            link_search_parts = []
            for group in meta.get("links", []):
                link_search_parts.append(str(group.get("name", "")))
                for item in group.get("items", []):
                    name = str(item.get("name", "")).strip()
                    url = str(item.get("url", "")).strip()
                    if name:
                        link_targets.append(name)
                    if name:
                        link_search_parts.append(name)
                    if url:
                        link_search_parts.append(url)

            # Match code0.cpp's displayed submission time exactly:
            # 1) explicit * submission; 2) newest submission whose name equals
            #    the problem ID; 3) otherwise the oldest submission; 4) zero time.
            subs = list(meta.get("submissions", []))
            display_time = "0000-00-00 00:00:00"
            primary = next((x for x in subs if x.get("primary")), None)
            if primary is not None:
                display_time = str(primary.get("time", "")) or display_time
            elif subs:
                ordered = sorted(subs, key=lambda x: str(x.get("time", "")), reverse=True)
                same = next((x for x in ordered if str(x.get("name", "")) == p.name), None)
                chosen = same if same is not None else ordered[-1]
                display_time = str(chosen.get("time", "")) or display_time

            ans.append({
                "id": p.name,
                "title": meta.get("title") or p.name,
                "custom_title": bool(meta.get("title")),
                "difficulty": meta.get("difficulty", ""),
                "tags": meta.get("tags", []),
                "submission_count": len(subs),
                "time": display_time,
                "link_targets": link_targets,
                "link_search": " ".join(link_search_parts),
            })
        # Stable two-pass sort: ties by ID ascending, primary key time descending.
        ans.sort(key=lambda x: x["id"].lower())
        ans.sort(key=lambda x: x["time"], reverse=True)
        return ans

    def get_problem(self, problem_id: str):
        p = self.problem_dir(problem_id)
        conf = self.conf_path(problem_id)
        if not conf.exists():
            raise RepoError("题目不存在或缺少 raw/problem.conf")
        text = self._read(conf)
        files = []
        raw = p / "raw"
        for f in raw.iterdir():
            if f.is_file():
                files.append({
                    "name": f.name,
                    "size": f.stat().st_size,
                    "editable": f.name not in {"problem.conf", "index.md"},
                    "generated": f.name == "index.md",
                })
        files.sort(key=lambda x: (x["name"] not in ("problem.conf", "index.md"), x["name"]))
        return {
            "id": p.name,
            "data": parse_known(text),
            "raw_conf": text,
            "files": files,
        }

    def save_structured(self, problem_id: str, data: dict):
        path = self.conf_path(problem_id)
        if not path.exists():
            raise RepoError("题目不存在")
        old = self._read(path)
        new = merge_structured(old, data)
        errors = validate_conf(new)
        if errors:
            raise RepoError("；".join(errors))
        return self._save_conf_with_rebuild(path, new)

    def save_raw_conf(self, problem_id: str, text: str):
        path = self.conf_path(problem_id)
        if not path.exists():
            raise RepoError("题目不存在")
        errors = validate_conf(text)
        if errors:
            raise RepoError("；".join(errors))
        return self._save_conf_with_rebuild(path, text.rstrip() + "\n")

    def create_problem(self, data: dict):
        pid = self._id(data.get("id", ""))
        p = self.problem_dir(pid)
        if p.exists():
            raise RepoError("题目已经存在")
        raw = p / "raw"
        raw.mkdir(parents=True)
        try:
            shutil.copy2(self.template, p / "index.html")
            link_name = str(data.get("link", "")).strip() or pid
            difficulty = str(data.get("difficulty", "")).strip()
            title = str(data.get("title", "")).strip()
            tags = data.get("tags", [])
            conf_data = {
                "title": title,
                "difficulty": difficulty,
                "links": [
                    {"name": "Link", "items": [{"name": link_name, "url": ""}]},
                    {"name": "Code", "items": [{"name": "code", "url": "?file=code0.cpp"}]},
                ],
                "from": [], "tags": tags, "submissions": [],
            }
            conf = merge_structured("", conf_data)
            self._atomic_write(raw / "problem.conf", conf)
            self._atomic_write(raw / "code0.cpp", "#include <bits/stdc++.h>\nusing namespace std;\n\nint main() {\n    ios::sync_with_stdio(false);\n    cin.tie(nullptr);\n\n    return 0;\n}\n")
            if data.get("create_solution"):
                self._atomic_write(raw / "sol.md", "# Solution\n\n")
                parsed = parse_known(conf)
                parsed["links"].append({"name": "Solution", "items": [{"name": "solution", "url": "?file=sol.md"}]})
                self._atomic_write(raw / "problem.conf", merge_structured(conf, parsed))
            self.rebuild()
            self._touch(p, self.problems / "index.json")
            return self.get_problem(pid)
        except Exception:
            shutil.rmtree(p, ignore_errors=True)
            raise

    def rename_problem(self, old_id: str, new_id: str):
        old = self.problem_dir(old_id)
        new_id = self._id(new_id)
        new = self.problem_dir(new_id)
        if not old.exists():
            raise RepoError("原题目不存在")
        if new.exists():
            raise RepoError("目标题目 ID 已存在")
        old_rel = str(old.relative_to(self.root)).replace(os.sep, "/")
        old.rename(new)
        self.rebuild()
        self.touched.add(old_rel)
        self._touch(new, self.problems / "index.json")
        return self.get_problem(new_id)

    def read_file(self, problem_id: str, filename: str):
        name = self._filename(filename)
        path = self.raw_dir(problem_id) / name
        if not path.is_file():
            raise RepoError("文件不存在")
        return self._read(path)

    def save_file(self, problem_id: str, filename: str, content: str):
        name = self._filename(filename)
        path = self.raw_dir(problem_id) / name
        if not path.exists():
            raise RepoError("文件不存在")
        self._atomic_write(path, content)
        self._touch(path)
        return {"name": name, "size": path.stat().st_size}

    def create_file(self, problem_id: str, filename: str, kind: str = "other", label: str = ""):
        name = self._filename(filename)
        path = self.raw_dir(problem_id) / name
        if path.exists():
            raise RepoError("文件已存在")
        default = ""
        if name.endswith(".cpp"):
            default = "#include <bits/stdc++.h>\nusing namespace std;\n\nint main() {\n    ios::sync_with_stdio(false);\n    cin.tie(nullptr);\n\n    return 0;\n}\n"
        elif name.endswith(".md"):
            default = "# Solution\n\n" if kind == "solution" else ""
        self._atomic_write(path, default)

        if kind in {"code", "solution"}:
            conf = self.conf_path(problem_id)
            text = self._read(conf)
            data = parse_known(text)
            group_name = "Code" if kind == "code" else "Solution"
            group = next((g for g in data["links"] if g["name"] == group_name), None)
            if group is None:
                group = {"name": group_name, "items": []}
                data["links"].append(group)
            shown = label.strip() or ("code" if kind == "code" else "solution")
            group["items"].append({"name": shown, "url": f"?file={name}"})
            self._atomic_write(conf, merge_structured(text, data))
            self.rebuild()
        self._touch(path, self.conf_path(problem_id), self.problems / "index.json", self.raw_dir(problem_id) / "index.md")
        return self.get_problem(problem_id)

    def delete_file(self, problem_id: str, filename: str):
        name = self._filename(filename)
        path = self.raw_dir(problem_id) / name
        if not path.exists():
            raise RepoError("文件不存在")
        path.unlink()
        self._touch(path)

        conf = self.conf_path(problem_id)
        text = self._read(conf)
        data = parse_known(text)
        target = f"?file={name}"
        for g in data["links"]:
            g["items"] = [i for i in g["items"] if i.get("url") != target]
        data["links"] = [g for g in data["links"] if g["items"] or g["name"] in {"Link", "Code"}]
        self._atomic_write(conf, merge_structured(text, data))
        self.rebuild()
        self._touch(conf, self.problems / "index.json", self.raw_dir(problem_id) / "index.md")
        return self.get_problem(problem_id)

    def rebuild(self):
        exe = self.root / "code0"
        src = self.root / "code0.cpp"
        if src.exists() and (not exe.exists() or src.stat().st_mtime > exe.stat().st_mtime):
            cp = subprocess.run(["g++", "-std=c++17", "-O2", "-o", str(exe), str(src)], cwd=self.root, capture_output=True, text=True)
            if cp.returncode != 0:
                raise RepoError("code0.cpp 编译失败：\n" + cp.stderr[-5000:])
        cp = subprocess.run([str(exe)], cwd=self.root, capture_output=True, text=True)
        if cp.returncode != 0:
            raise RepoError("重新生成失败：\n" + cp.stderr[-5000:])
        return {"ok": True, "stderr_tail": cp.stderr[-1000:]}

    def git_diff(self):
        cp = subprocess.run(["git", "diff", "--", "problems", "code0.cpp", "viewer.js", "README_ADMIN.md", "admin.sh", "admin"], cwd=self.root, capture_output=True, text=True)
        cp2 = subprocess.run(["git", "status", "--short", "--", "problems", "code0.cpp", "viewer.js", "README_ADMIN.md", "admin.sh", "admin"], cwd=self.root, capture_output=True, text=True)
        return {"status": cp2.stdout, "diff": cp.stdout}

    def git_commit(self, message: str):
        message = message.strip()
        if not message:
            raise RepoError("Commit message 不能为空")
        if not self.touched:
            raise RepoError("本次 Admin 会话还没有修改题目文件")
        paths = sorted(self.touched)
        cp = subprocess.run(["git", "add", "--", *paths], cwd=self.root, capture_output=True, text=True)
        if cp.returncode != 0:
            raise RepoError(cp.stderr.strip() or "Git add 失败")
        cp = subprocess.run(["git", "commit", "-m", message, "--", *paths], cwd=self.root, capture_output=True, text=True)
        if cp.returncode != 0:
            raise RepoError(cp.stderr.strip() or cp.stdout.strip() or "Git commit 失败")
        self.touched.clear()
        return {"output": cp.stdout.strip()}
