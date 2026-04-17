// ==========================
// 获取当前要加载的文件
// ==========================
function getCurrentFile() {
  const params = new URLSearchParams(window.location.search);
  return params.get("file") || "index.md";
}

// ==========================
// 获取题目名称（用于标题）
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
  const links = container.querySelectorAll("a");

  links.forEach(a => {
    let href = a.getAttribute("href");
    if (!href) return;

    // 外链 / 锚点 / mail 不处理
    if (
      href.startsWith("http") ||
      href.startsWith("#") ||
      href.startsWith("mailto:")
    ) return;

    // 去掉 "./"
    if (href.startsWith("./")) {
      href = href.slice(2);
    }

    // 👉 关键：保持 .md 真实路径
    if (href.endsWith(".md")) {
      a.href = href;
    }
  });
}

// ==========================
// Markdown 渲染主流程
// ==========================
async function load() {
  const file = getCurrentFile();
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

    // 渲染 Markdown
    contentEl.innerHTML = marked.parse(text);

    // 修复链接
    fixLinks(contentEl);

    // 代码高亮
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

// ==========================
// 启动
// ==========================
load();