// 获取 URL 参数
function getQuery(name) {
  const url = new URL(window.location.href);
  return url.searchParams.get(name);
}

const problemName = getQuery("name");
document.getElementById("title").textContent = problemName;

// 修复链接 + 拦截点击
function processLinks(container, base) {
  const links = container.querySelectorAll("a");

  links.forEach(a => {
    let href = a.getAttribute("href");
    if (!href) return;

    // 忽略外链 / 锚点
    if (href.startsWith("http") || href.startsWith("#")) return;

    // 去掉 ./ 前缀
    if (href.startsWith("./")) {
      href = href.slice(2);
    }

    const fullPath = `${base}/${href}`;

    // 👉 如果是 markdown：拦截点击
    if (href.endsWith(".md")) {
      a.href = "#";

      a.onclick = async (e) => {
        e.preventDefault();
        loadMarkdown(fullPath);
      };
    } else {
      // 👉 其他文件：正常跳转（如 code.cpp）
      a.href = fullPath;
    }
  });
}

// 加载 markdown 并渲染
async function loadMarkdown(path) {
  const container = document.getElementById("content");

  try {
    const res = await fetch(path);
    if (!res.ok) {
      container.innerHTML = "<p>❌ File not found</p>";
      return;
    }

    const text = await res.text();

    container.innerHTML = marked.parse(text);

    // ⚠️ 递归处理新内容里的链接
    const base = path.substring(0, path.lastIndexOf("/"));
    processLinks(container, base);

    // 滚动到顶部（体验更好）
    window.scrollTo(0, 0);

  } catch (e) {
    container.innerHTML = "<p>❌ Load failed</p>";
    console.error(e);
  }
}

// 初始加载 index.md
async function init() {
  const base = `problems/${problemName}`;
  const path = `${base}/index.md`;

  document.getElementById("title").textContent = problemName;

  await loadMarkdown(path);
}

init();