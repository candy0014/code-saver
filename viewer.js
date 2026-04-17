// 获取当前文件路径
function getCurrentFile() {
  let path = window.location.pathname;

  // 去掉 repo 前缀（GitHub Pages 子路径）
  // 例如 /code-saver/problems/P15142/sol.md
  const base = "/code-saver/";
  if (path.startsWith(base)) {
    path = path.slice(base.length);
  }

  // 如果是目录（结尾 / 或 index.html）
  if (path.endsWith("/") || path.endsWith("index.html")) {
    return "index.md";
  }

  // 如果是 .md 文件
  if (path.endsWith(".md")) {
    return path.split("/").pop();
  }

  return "index.md";
}

// 获取当前 problem 名
function getProblemName() {
  const parts = window.location.pathname.split("/");

  // 找到 problems 后面的目录名
  const idx = parts.indexOf("problems");
  if (idx !== -1 && parts.length > idx + 1) {
    return parts[idx + 1];
  }

  return "Unknown";
}

// 修复 Markdown 内的链接
function fixLinks(container) {
  const links = container.querySelectorAll("a");

  links.forEach(a => {
    let href = a.getAttribute("href");
    if (!href) return;

    // 外链 / 锚点不处理
    if (href.startsWith("http") || href.startsWith("#")) return;

    // 去掉 ./
    if (href.startsWith("./")) {
      href = href.slice(2);
    }

    // 👉 如果是 md 文件，改成真实路径跳转
    if (href.endsWith(".md")) {
      a.href = href; // 浏览器自动拼当前目录
    }
  });
}

// 加载并渲染 Markdown
async function load() {
  const file = getCurrentFile();
  const problem = getProblemName();

  document.getElementById("title").textContent = problem;

  try {
    const res = await fetch(file);
    if (!res.ok) {
      document.getElementById("content").innerHTML = "<p>❌ File not found</p>";
      return;
    }

    const text = await res.text();

    const container = document.getElementById("content");
    container.innerHTML = marked.parse(text);

    fixLinks(container);

    // 可选：代码高亮
    if (window.hljs) {
      document.querySelectorAll("pre code").forEach(block => {
        hljs.highlightElement(block);
      });
    }

  } catch (e) {
    document.getElementById("content").innerHTML = "<p>❌ Load failed</p>";
    console.error(e);
  }
}

load();