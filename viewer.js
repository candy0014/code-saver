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
// HTML 转义（防止代码被解析）
// ==========================
function escapeHtml(str) {
  return str
    .replace(/&/g, "&amp;")
    .replace(/</g, "&lt;")
    .replace(/>/g, "&gt;");
}

// ==========================
// 修复 Markdown 内链接
// ==========================
function fixLinks(container, problem) {
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

    if (href.match(/\.(md|cpp|txt|py)$/)) {
      const name = href.split(".")[0];
      a.href = "/code-saver/" + problem + "/" + name;
    }
  });
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

  if (titleEl) titleEl.textContent = problem;

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

      fixLinks(contentEl, problem);

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