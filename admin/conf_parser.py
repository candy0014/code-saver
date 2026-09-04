from __future__ import annotations

from dataclasses import dataclass
from typing import Iterable

KNOWN_SECTIONS = ("title", "link", "df", "from", "tag", "sub")


@dataclass
class Section:
    name: str
    body: list[str]


def split_sections(text: str):
    """Split a conf while preserving all unknown text/sections verbatim-ish.

    Nodes are tuples ("raw", list[str]) or ("section", Section). Line endings are
    normalized to \n on write, but unknown section contents/order are preserved.
    """
    lines = text.splitlines()
    nodes = []
    raw = []
    i = 0
    while i < len(lines):
        s = lines[i].strip()
        if s.startswith(">") and len(s) > 1:
            name = s[1:].strip()
            j = i + 1
            depth = 1
            body = []
            while j < len(lines):
                t = lines[j].strip()
                if t.startswith(">") and t[1:].strip() == name:
                    depth += 1
                if t.startswith("<") and t[1:].strip() == name:
                    depth -= 1
                    if depth == 0:
                        break
                body.append(lines[j])
                j += 1
            if j < len(lines):
                if raw:
                    nodes.append(("raw", raw)); raw = []
                nodes.append(("section", Section(name, body)))
                i = j + 1
                continue
        raw.append(lines[i])
        i += 1
    if raw:
        nodes.append(("raw", raw))
    return nodes


def section_map(text: str) -> dict[str, list[str]]:
    out = {}
    for typ, node in split_sections(text):
        if typ == "section":
            out[node.name] = [x.strip() for x in node.body if x.strip()]
    return out


def _pairs(lines: Iterable[str]):
    out = []
    for line in lines:
        if ";" in line:
            name, url = line.split(";", 1)
        else:
            name, url = line, ""
        out.append({"name": name, "url": url})
    return out


def parse_known(text: str) -> dict:
    sec = section_map(text)
    links = []
    cur = None
    for line in sec.get("link", []):
        if line.startswith("#"):
            cur = {"name": line[1:], "items": []}
            links.append(cur)
        elif cur is not None:
            if ";" in line:
                name, url = line.split(";", 1)
            else:
                name, url = line, ""
            cur["items"].append({"name": name, "url": url})

    difficulty = ""
    if sec.get("df"):
        difficulty = sec["df"][0]

    subs = []
    for line in sec.get("sub", []):
        primary = line.startswith("*")
        if primary:
            line = line[1:]
        parts = line.split(";", 2)
        parts += [""] * (3 - len(parts))
        subs.append({"primary": primary, "time": parts[0], "name": parts[1], "url": parts[2]})

    title = sec.get("title", [""])[0] if sec.get("title") else ""
    return {
        "title": title,
        "difficulty": difficulty,
        "links": links,
        "from": _pairs(sec.get("from", [])),
        "tags": sec.get("tag", []),
        "submissions": subs,
    }


def render_section(name: str, body: list[str]) -> list[str]:
    return [f">{name}", *body, f"<{name}"]


def structured_sections(data: dict) -> dict[str, list[str] | None]:
    result: dict[str, list[str] | None] = {}
    title = str(data.get("title", "")).strip()
    # Optional by design. Removing the title restores legacy folder-name display.
    result["title"] = [title] if title else None

    link_body = []
    for group in data.get("links", []):
        gname = str(group.get("name", "")).strip()
        if not gname:
            continue
        link_body.append("#" + gname)
        for item in group.get("items", []):
            name = str(item.get("name", "")).strip()
            url = str(item.get("url", "")).strip()
            if not name:
                continue
            link_body.append(name + (";" + url if url else ""))
    result["link"] = link_body

    difficulty = str(data.get("difficulty", "")).strip()
    result["df"] = [difficulty] if difficulty else []

    from_body = []
    for item in data.get("from", []):
        name = str(item.get("name", "")).strip()
        url = str(item.get("url", "")).strip()
        if name:
            from_body.append(name + (";" + url if url else ""))
    result["from"] = from_body if from_body else None

    result["tag"] = [str(x).strip() for x in data.get("tags", []) if str(x).strip()]

    sub_body = []
    primary_used = False
    for sub in data.get("submissions", []):
        tim = str(sub.get("time", "")).strip()
        name = str(sub.get("name", "")).strip()
        url = str(sub.get("url", "")).strip()
        if not (tim or name or url):
            continue
        primary = bool(sub.get("primary")) and not primary_used
        primary_used |= primary
        sub_body.append(("*" if primary else "") + ";".join([tim, name, url]))
    result["sub"] = sub_body
    return result


def merge_structured(original: str, data: dict) -> str:
    replacements = structured_sections(data)
    seen = set()
    output = []
    nodes = split_sections(original)

    for typ, node in nodes:
        if typ == "raw":
            output.extend(node)
            continue
        name = node.name
        if name in replacements:
            seen.add(name)
            body = replacements[name]
            if body is not None:
                output.extend(render_section(name, body))
        else:
            output.extend(render_section(name, node.body))

    # New known sections are appended in stable order. Keep title first if added.
    for name in KNOWN_SECTIONS:
        if name in seen:
            continue
        body = replacements.get(name)
        if body is None:
            continue
        if output and output[-1] != "":
            output.append("")
        output.extend(render_section(name, body))

    # Clean excessive blank lines but do not disturb unknown section contents.
    cleaned = []
    blank = 0
    for line in output:
        if line == "":
            blank += 1
            if blank <= 1:
                cleaned.append(line)
        else:
            blank = 0
            cleaned.append(line)
    return "\n".join(cleaned).rstrip() + "\n"


def validate_conf(text: str) -> list[str]:
    errors = []
    stack = []
    for no, line in enumerate(text.splitlines(), 1):
        s = line.strip()
        if not s:
            continue
        if s.startswith(">") and len(s) > 1:
            stack.append((s[1:].strip(), no))
        elif s.startswith("<") and len(s) > 1:
            name = s[1:].strip()
            if not stack:
                errors.append(f"第 {no} 行：孤立结束标记 <{name}")
            else:
                open_name, open_no = stack.pop()
                if open_name != name:
                    errors.append(f"第 {no} 行：<{name} 与第 {open_no} 行 >{open_name} 不匹配")
    for name, no in stack:
        errors.append(f"第 {no} 行：>{name} 缺少结束标记 <{name}")
    return errors
