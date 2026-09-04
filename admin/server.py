#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
import mimetypes
import os
import sys
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
from pathlib import Path
from urllib.parse import unquote, urlparse

HERE = Path(__file__).resolve().parent
ROOT = HERE.parent
sys.path.insert(0, str(HERE))
from repository import RepoError, Repository  # noqa: E402

repo = Repository(ROOT)
STATIC = HERE / "static"


class Handler(BaseHTTPRequestHandler):
    server_version = "CodeSaverAdmin/1.0"

    def log_message(self, fmt, *args):
        sys.stderr.write("[admin] " + fmt % args + "\n")

    def _json(self, obj, status=200):
        raw = json.dumps(obj, ensure_ascii=False).encode("utf-8")
        self.send_response(status)
        self.send_header("Content-Type", "application/json; charset=utf-8")
        self.send_header("Content-Length", str(len(raw)))
        self.send_header("Cache-Control", "no-store")
        self.end_headers()
        self.wfile.write(raw)

    def _body(self):
        n = int(self.headers.get("Content-Length", "0"))
        if n > 20 * 1024 * 1024:
            raise RepoError("请求过大")
        raw = self.rfile.read(n)
        if not raw:
            return {}
        try:
            return json.loads(raw.decode("utf-8"))
        except Exception:
            raise RepoError("请求 JSON 无效")

    def _serve(self, path: Path, base: Path = STATIC):
        try:
            path = path.resolve()
            base = base.resolve()
            if base not in path.parents and path != base:
                raise FileNotFoundError
            if path.is_dir():
                path = path / "index.html"
            raw = path.read_bytes()
        except Exception:
            self.send_error(404)
            return
        ctype = mimetypes.guess_type(str(path))[0] or "application/octet-stream"
        self.send_response(200)
        self.send_header("Content-Type", ctype + ("; charset=utf-8" if ctype.startswith("text/") else ""))
        self.send_header("Content-Length", str(len(raw)))
        self.send_header("Cache-Control", "no-store")
        self.end_headers()
        self.wfile.write(raw)

    @staticmethod
    def _parts(path):
        return [unquote(x) for x in path.split("/") if x]

    def do_GET(self):
        try:
            u = urlparse(self.path)
            parts = self._parts(u.path)
            if u.path in {"/", "/index.html"}:
                return self._serve(STATIC / "index.html")
            if parts and parts[0] == "static":
                return self._serve(STATIC.joinpath(*parts[1:]))
            # Read-only preview of the existing static site. Absolute /code-saver/
            # paths in the original pages keep working on localhost.
            if parts and parts[0] == "code-saver":
                return self._serve(ROOT.joinpath(*parts[1:]), ROOT)
            if u.path == "/api/problems":
                return self._json({"problems": repo.list_problems()})
            if len(parts) == 3 and parts[:2] == ["api", "problems"]:
                return self._json(repo.get_problem(parts[2]))
            if len(parts) == 5 and parts[:2] == ["api", "problems"] and parts[3] == "files":
                content = repo.read_file(parts[2], parts[4])
                return self._json({"name": parts[4], "content": content})
            if u.path == "/api/git/diff":
                return self._json(repo.git_diff())
            if u.path == "/api/health":
                return self._json({"ok": True, "root": str(ROOT)})
            self.send_error(404)
        except RepoError as e:
            self._json({"error": str(e)}, 400)
        except Exception as e:
            self._json({"error": f"内部错误：{e}"}, 500)

    def do_POST(self):
        try:
            u = urlparse(self.path); parts = self._parts(u.path); body = self._body()
            if u.path == "/api/problems":
                return self._json(repo.create_problem(body), 201)
            if len(parts) == 4 and parts[:2] == ["api", "problems"] and parts[3] == "rename":
                return self._json(repo.rename_problem(parts[2], body.get("new_id", "")))
            if len(parts) == 5 and parts[:2] == ["api", "problems"] and parts[3] == "files":
                # /api/problems/{id}/files/create
                if parts[4] == "create":
                    return self._json(repo.create_file(parts[2], body.get("name", ""), body.get("kind", "other"), body.get("label", "")), 201)
            if u.path == "/api/rebuild":
                return self._json(repo.rebuild())
            if u.path == "/api/git/commit":
                return self._json(repo.git_commit(body.get("message", "")))
            self.send_error(404)
        except RepoError as e:
            self._json({"error": str(e)}, 400)
        except Exception as e:
            self._json({"error": f"内部错误：{e}"}, 500)

    def do_PUT(self):
        try:
            u = urlparse(self.path); parts = self._parts(u.path); body = self._body()
            if len(parts) == 3 and parts[:2] == ["api", "problems"]:
                return self._json(repo.save_structured(parts[2], body.get("data", {})))
            if len(parts) == 4 and parts[:2] == ["api", "problems"] and parts[3] == "conf":
                return self._json(repo.save_raw_conf(parts[2], body.get("content", "")))
            if len(parts) == 5 and parts[:2] == ["api", "problems"] and parts[3] == "files":
                return self._json(repo.save_file(parts[2], parts[4], body.get("content", "")))
            self.send_error(404)
        except RepoError as e:
            self._json({"error": str(e)}, 400)
        except Exception as e:
            self._json({"error": f"内部错误：{e}"}, 500)

    def do_DELETE(self):
        try:
            u = urlparse(self.path); parts = self._parts(u.path)
            if len(parts) == 5 and parts[:2] == ["api", "problems"] and parts[3] == "files":
                return self._json(repo.delete_file(parts[2], parts[4]))
            self.send_error(404)
        except RepoError as e:
            self._json({"error": str(e)}, 400)
        except Exception as e:
            self._json({"error": f"内部错误：{e}"}, 500)


def main():
    ap = argparse.ArgumentParser(description="Code Saver local admin")
    ap.add_argument("--host", default="127.0.0.1", help="默认只监听本机")
    ap.add_argument("--port", type=int, default=8765)
    args = ap.parse_args()
    httpd = ThreadingHTTPServer((args.host, args.port), Handler)
    print(f"Code Saver Admin: http://{args.host}:{args.port}/")
    print(f"Repository: {ROOT}")
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        print("\nStopped.")


if __name__ == "__main__":
    main()
