# Code Saver Admin

本地题库编辑器，直接编辑现有 `problems/<id>/raw/`，不改变 GitHub Pages 的使用方式。

## 启动

在仓库根目录运行：

```bash
./admin.sh
# 或：python3 admin/server.py
```

浏览器打开：

```text
http://127.0.0.1:8765/
```

可改端口：

```bash
python3 admin/server.py --port 9000
```

默认只监听 `127.0.0.1`，不会向局域网公开文件编辑接口。

## 功能

- 搜索并编辑已有题目
- 新建题目
- 重命名题目 ID / 目录
- 可选 `>title ... <title` 展示名称
- 修改 difficulty / tag / from
- 任意 `#Link` 分组与链接的增删改
- Submission 编辑与 `*` 主记录选择
- `problem.conf` Raw 编辑，保存前检查 section 配对
- 新增、编辑、删除 `code*.cpp`、`sol*.md` 等文本文件
- 新建代码/题解时自动添加 `#Code` / `#Solution`
- 保存 conf 后自动运行 `./code0` 重新生成 `index.md` / `index.json`
- Git Diff 与 Git Commit（Commit 只会暂存本次 Admin 会话实际改过的题目文件，不会顺手提交仓库原本的其他未提交修改）

## title 兼容性

`title` 是可选的新 section：

```conf
>title
题目的展示名称
<title
```

没有 `title` 的旧题仍然使用目录名显示，因此现有题库无需迁移。

## 注意

- `raw/index.md` 是生成文件，Admin 中只读。
- Admin 不提供 Git push，避免一次误操作直接推送到远端。
- 普通题目文件限制在 `raw/` 下，接口会拒绝 `../` 等路径穿越。
