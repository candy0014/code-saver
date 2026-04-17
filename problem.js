// 获取 URL 参数
function getQuery(name) {
  const url = new URL(window.location.href);
  return url.searchParams.get(name);
}

const problemName = getQuery("name");
document.getElementById("title").textContent = problemName;

// 修复 Markdown 中的相对链接
function fixLinks(container, base) {
  const links = container.querySelectorAll("a");

  links.forEach(a => {
    let href = a.getAttribute("href");
    if (!href) return;

    // 忽略绝对链接 / 锚点
    if (href.startsWith("http") || href.startsWith("#")) return;

    // 处理 ./ 或 普通文件名
    if (href.startsWith("./")) {
      href = href.slice(2);
    }

    a.href = `${base}/${href}`;
  });
}

// 加载 index.md
async function load() {
  const base = `problems/${problemName}`;
  const path = `${base}/index.md`;

  try {
    const res = await fetch(path);
    if (!res.ok) {
      document.getElementById("content").innerHTML = "<p>❌ index.md not found</p>";
      return;
    }

    const text = await res.text();

    const container = document.getElementById("content");
    container.innerHTML = marked.parse(text);

    // 修复链接（重要）
    fixLinks(container, base);

  } catch (e) {
    document.getElementById("content").innerHTML = "<p>❌ Load failed</p>";
    console.error(e);
  }
}

load();