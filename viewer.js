// ==========================
// 参数解析
// ==========================
function getParams() {
  const p = new URLSearchParams(location.search);

  const file = p.get("file") || "index.md";

  // 去掉空段
  let parts = location.pathname.split("/").filter(x => x);

  // 如果最后是 html（viewer.html），去掉它
  const last = parts[parts.length - 1];
  if (last && last.includes(".html")) {
    parts.pop();
  }

  // basePath = /code-saver/problems/P1001
  const basePath = "/" + parts.join("/");

  return { basePath, file };
}

// ==========================
// HTML 转义
// ==========================
function escapeHtml(str) {
  return str
    .replace(/&/g, "&amp;")
    .replace(/</g, "&lt;")
    .replace(/>/g, "&gt;");
}

// ==========================
// 扩展名
// ==========================
function getExt(file) {
  const i = file.lastIndexOf(".");
  return i === -1 ? "" : file.slice(i + 1).toLowerCase();
}

// ==========================
// 主逻辑
// ==========================
async function load() {
  const { basePath, file } = getParams();
  const ext = getExt(file);

  const titleEl = document.getElementById("title");
  const contentEl = document.getElementById("content");
  const baseEl = document.getElementById("base");
  const backEl = document.getElementById("back");

  console.log("basePath:", basePath);
  console.log("file:", file);

  if (!basePath) {
    contentEl.innerHTML = "<h2>❌ Invalid path</h2>";
    return;
  }

  // 标题
  if (titleEl) {
    titleEl.textContent = basePath.split("/").pop();
  }

  // base link
  if (baseEl) {
    baseEl.href = basePath + "/";
  }

  // ==========================
  // back 逻辑（核心）
  // ==========================
  if (backEl) {
    const params = new URLSearchParams(location.search);
    const hasFile = params.has("file");

    if (hasFile) {
      // 👉 只看文件：回到目录页（去掉 query）
      backEl.href = basePath + "/";
    } else {
      // 👉 目录页：回上一级
      const parts = basePath.split("/").filter(x => x);
      const parent = parts.slice(0, -1).join("/");
      backEl.href = "/" + parent + "/";
    }
  }

  try {
    // ==========================
    // 拼接 raw 路径
    // ==========================
    const url = basePath + "/raw/" + file;

    console.log("fetch:", url);

    const res = await fetch(url);

    if (!res.ok) {
      contentEl.innerHTML = "<h2>❌ File not found</h2>";
      return;
    }

    const text = await res.text();

    if (!text.trim()) {
      contentEl.innerHTML = "<h2>⚠️ Empty file</h2>";
      return;
    }

    // ==========================
    // 渲染
    // ==========================
    if (ext === "md") {
      contentEl.innerHTML = marked.parse(text);
    } else {
      contentEl.innerHTML =
        "<pre><code>" + escapeHtml(text) + "</code></pre>";
    }

    // ==========================
    // 高亮
    // ==========================
    if (window.hljs) {
      document.querySelectorAll("pre code").forEach(block => {
        hljs.highlightElement(block);
      });
    }

  } catch (err) {
    console.error(err);
    contentEl.innerHTML = "<h2>❌ Load failed</h2>";
  }
}

load();