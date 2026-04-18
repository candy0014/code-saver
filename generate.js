const fs = require("fs");

const dir = "./problems";

// 读取 problems 文件夹
const list = fs.readdirSync(dir, { withFileTypes: true })
  .filter(d => d.isDirectory() && /^P\d+/.test(d.name))
  .map(d => d.name)
  .sort();

// 写入 index.json
fs.writeFileSync(
  "./problems/index.json",
  JSON.stringify(list, null, 2)
);

console.log("✅ index.json generated:");
console.log(list);