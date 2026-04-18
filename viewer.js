// ==========================
// 获取参数（从路径解析）
// ==========================
function getParams() {
  const parts = location.pathname.split("/").filter(x => x);
  const idx = parts.indexOf("problems");

  let problem = null;
  if (idx !== -1 && parts.length > idx + 1) {
    problem = parts[idx + 1];
  }

  const p = new URLSearchParams(location.search);
  let file = p.get("file") || "index.md";

  return { problem, file };
}

// ==========================
// HTML 转义（用于代码）
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
  const backEl = document.getElementById("back");

  console.log("Problem:", problem);
  console.log("File:", file);

  if (titleEl) titleEl.textContent = problem;

  // ==========================
  // 自动适配 base（关键）
  // ==========================
  const basePath = location.pathname.includes("/code-saver/")
    ? "/code-saver/"
    : "/";

  if (baseEl) {
    baseEl.href = location.pathname.replace(/\/[^/]*$/, "/");
  }

  if (backEl) {
    backEl.href = basePath;
  }

  try {
    const url =
      basePath + "problems/" + problem + "/raw/" + file;

    console.log("Fetching:", url);

    const res = await fetch(url);

    if (!res.ok) {
      contentEl.innerHTML = "<h2>❌ File not found</h2>";
      return;
    }

    const text = await res.text();
    console.log("Loaded length:", text.length);

    if (!text.trim()) {
      contentEl.innerHTML = "<h2>⚠️ Empty file</h2>";
      return;
    }

    // ======================
    // Markdown 渲染
    // ======================
    if (ext === "md") {
      contentEl.innerHTML = marked.parse(text);
    }
    // ======================
    // 代码文件
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
    console.error(err);
    contentEl.innerHTML = "<h2>❌ Load failed</h2>";
  }
}

load();