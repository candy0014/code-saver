// ==========================
// 获取参数
// ==========================
function getParams() {
  const p = new URLSearchParams(location.search);
  return {
    problem: p.get("problem") || "",
    file: p.get("file") || "index.md"
  };
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

  // 设置标题
  if (titleEl) titleEl.textContent = problem;

  // ==========================
  // ✅ 设置 base（核心）
  // ==========================
  baseEl.href = "/code-saver/" + problem + "/";

  try {
    const res = await fetch(
      "problems/" + problem + "/raw/" + file
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