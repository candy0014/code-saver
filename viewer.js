// ==========================
// 获取参数
// ==========================
function getParams() {
  const p = new URLSearchParams(location.search);

  let problem = p.get("problem");
  let file = p.get("file") || "index.md";

  // 👇 如果没有 problem，从路径解析
  if (!problem) {
    const parts = location.pathname.split("/").filter(x => x);
    const idx = parts.indexOf("problems");
    if (idx !== -1 && parts.length > idx + 1) {
      problem = parts[idx + 1];
    }
  }

  return { problem, file };
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
// 获取扩展名
// ==========================
function getExt(file) {
  return file.split(".").pop().toLowerCase().trim();
}

// ==========================
// 主逻辑
// ==========================
async function load() {
  const { problem, file } = getParams();
  const ext = getExt(file);

  const titleEl = document.getElementById("title");
  const contentEl = document.getElementById("content");
  const baseEl = document.getElementById("base");

  if (titleEl) titleEl.textContent = problem;

  // ✅ 关键：设置 base 为当前目录
  baseEl.href = location.pathname.replace(/\/[^/]*$/, "/");

  try {
    const res = await fetch(
      "/code-saver/problems/" + problem + "/raw/" + file
    );

    if (!res.ok) {
      contentEl.innerHTML = "<h2>❌ File not found</h2>";
      return;
    }

    const text = await res.text();

    // ======================
    // Markdown
    // ======================
    if (ext === "md") {

      const safeText = text
        .replace(/</g, "&lt;")
        .replace(/>/g, "&gt;");

      contentEl.innerHTML = marked.parse(safeText);
    }
    // ======================
    // 代码
    // ======================
    else {
      contentEl.innerHTML =
        "<pre><code>" +
        escapeHtml(text) +
        "</code></pre>";
    }

    // 高亮
    if (window.hljs) {
      document.querySelectorAll("pre code").forEach(block => {
        hljs.highlightElement(block);
      });
    }

  } catch (err) {
    contentEl.innerHTML = "<h2>❌ Load failed</h2>";
    console.error(err);
  }
}

load();