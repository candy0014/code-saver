function getQuery(name) {
  const url = new URL(window.location.href);
  return url.searchParams.get(name);
}

const problemName = getQuery("name");

document.getElementById("title").textContent = problemName;

async function load() {
  const base = `problems/${problemName}`;

  const prob = await fetch(`${base}/index.md`).then(r => r.text());
  const sol = await fetch(`${base}/sol.md`).then(r => r.text());
  const code = await fetch(`${base}/code.cpp`).then(r => r.text());

  document.getElementById("problem").innerHTML = marked.parse(prob);
  document.getElementById("solution").innerHTML = marked.parse(sol);

  const codeBlock = document.getElementById("code");
  codeBlock.textContent = code;
  hljs.highlightElement(codeBlock);
}

load();