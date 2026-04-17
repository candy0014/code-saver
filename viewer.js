// ==========================
// 获取当前文件
// ==========================
function getCurrentFile() {
  const params = new URLSearchParams(window.location.search);
  return params.get("file") || "index.md";
}

// ==========================
// 获取题目名
// ==========================
function getProblemName() {
  const parts = window.location.pathname.split("/");

  const idx = parts.indexOf("problems");
  if (idx !== -1 && parts.length > idx + 1) {
    return parts[idx + 1];
  }

  return "Problem";
}

// ==========================
// 修复 Markdown 内链接
// ==========================
function fixLinks(container) {
  container.querySelectorAll("a").forEach(a => {
    let href = a.getAttribute("href");
    if (!href) return;

    if (
      href.startsWith("http") ||
      href.startsWith("#") ||
      href.startsWith("mailto:")
    ) return;

    if (href.startsWith("./")) {
      href = href.slice(2);
    }

    // 保持 /xxx.md / xxx.cpp 形式（触发 404）
    if (href.match(/\.(md|cpp|txt|py|java|json)$/)) {
      a.href = href;
    }
  });
}

// ==========================
// HTML 转义（防止代码被解析）
// ==========================
function escapeHtml(str) {
  return str
    .replace(/&/g, "&amp;")
    .replace(/</g, "&lt;")
    .replace(/>/g, "&gt;");
}

// ==========================
// 根据扩展名判断类型
// ==========================
function getExt(file) {
  return file.split(".").pop().toLowerCase().trim();
}

// ==========================
// 主加载逻辑
// ==========================
async function load() {
  const file = getCurrentFile().trim();
  const ext = getExt(file);
  const problem = getProblemName();

  const titleEl = document.getElementById("title");
  const contentEl = document.getElementById("content");

  if (titleEl) titleEl.textContent = problem;

  try {
    const res = await fetch("raw/" + file);

    if (!res.ok) {
      contentEl.innerHTML = "<h2>❌ File not found</h2>";
      return;
    }

    const text = await res.text();

    // ======================
    // Markdown 文件
    // ======================
    if (ext === "md") {

      // ⚠️ 防止 HTML 被当标签解析（关键）
      const safeText = text
        .replace(/</g, "&lt;")
        .replace(/>/g, "&gt;");

      contentEl.innerHTML = marked.parse(safeText);

      fixLinks(contentEl);

      if (window.hljs) {
        document.querySelectorAll("pre code").forEach(block => {
          hljs.highlightElement(block);
        });
      }

    }
    // ======================
    // 代码 / 文本文件
    // ======================
    else {

      contentEl.innerHTML =
        "<pre><code>" +
        escapeHtml(text) +
        "</code></pre>";

      if (window.hljs) {
        document.querySelectorAll("pre code").forEach(block => {
          hljs.highlightElement(block);
        });
      }
    }

  } catch (err) {
    contentEl.innerHTML = "<h2>❌ Load failed</h2>";
    console.error(err);
  }
}

// ==========================
// 启动
// ==========================
load();