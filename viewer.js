// ==========================
// 参数解析
// ==========================
function getParams() {
  const p = new URLSearchParams(location.search);
  const file = p.get("file") || "index.md";

  let parts = location.pathname.split("/").filter(x => x);

  const last = parts[parts.length - 1];
  if (last && last.includes(".html")) parts.pop();

  const basePath = "/" + parts.join("/");

  return { basePath, file };
}

// ==========================
// HTML escape
// ==========================
function escapeHtml(str) {
  return str
    .replace(/&/g, "&amp;")
    .replace(/</g, "&lt;")
    .replace(/>/g, "&gt;");
}

// ==========================
// extension
// ==========================
function getExt(file) {
  const i = file.lastIndexOf(".");
  return i === -1 ? "" : file.slice(i + 1).toLowerCase();
}

// ==========================
// KaTeX render
// ==========================
function renderMath(el) {
  if (!window.renderMathInElement) {
    console.error("KaTeX auto-render not loaded");
    return;
  }

  window.renderMathInElement(el, {
    delimiters: [
      { left: "$$", right: "$$", display: true },
      { left: "\\(", right: "\\)", display: false },
      { left: "$", right: "$", display: false }
    ],
    throwOnError: false
  });
}

// ==========================
// main
// ==========================
async function load() {
  const { basePath, file } = getParams();
  const ext = getExt(file);

  const contentEl = document.getElementById("content");
  const titleEl = document.getElementById("title");
  const backEl = document.getElementById("back");
  console.log("basePath:", basePath);
  console.log("file:", file);

  if (titleEl) {
    titleEl.textContent = file;
  }
  
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
    const url = basePath + "/raw/" + file;
    console.log("fetch:", url);

    const res = await fetch(url);
    if (!res.ok) {
      contentEl.innerHTML = "<h2>File not found</h2>";
      return;
    }

    const text = await res.text();

    // ==========================
    // Markdown / text
    // ==========================
    if (ext === "md") {
      contentEl.innerHTML = marked.parse(text, {
        breaks: true
      });
    } else {
      contentEl.innerHTML =
        "<pre><code>" + escapeHtml(text) + "</code></pre>";
    }

    // ==========================
    // highlight
    // ==========================
    if (window.hljs) {
      document.querySelectorAll("pre code")
        .forEach(b => hljs.highlightElement(b));
    }

    // ==========================
    // KaTeX
    // ==========================
    renderMath(contentEl);

  } catch (e) {
    console.error(e);
    contentEl.innerHTML = "<h2>Load failed</h2>";
  }
}

// ==========================
// boot (关键：等待 defer scripts)
// ==========================
window.addEventListener("load", () => {
  setTimeout(load, 50);
});