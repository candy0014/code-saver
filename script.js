const user = "candy0014";
const repo = "code-saver";

const api = `https://api.github.com/repos/${user}/${repo}/contents/problems`;

async function loadList() {
  const res = await fetch(api);
  const data = await res.json();

  const list = document.getElementById("list");

  data.forEach(item => {
    if (item.type === "dir") {
      const li = document.createElement("li");

      const a = document.createElement("a");
      a.href = `problem.html?name=${item.name}`;
      a.textContent = item.name;

      li.appendChild(a);
      list.appendChild(li);
    }
  });
}

loadList();