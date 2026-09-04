const $ = s => document.querySelector(s);
const $$ = s => [...document.querySelectorAll(s)];
let problems = [], current = null, currentFile = null, dirty = false;

async function api(path, options={}) {
  const opt = {...options, headers:{'Content-Type':'application/json', ...(options.headers||{})}};
  const r = await fetch(path, opt);
  let data = {};
  try { data = await r.json(); } catch (_) {}
  if (!r.ok) throw new Error(data.error || `${r.status} ${r.statusText}`);
  return data;
}
function toast(msg, error=false){const t=$('#toast');t.textContent=msg;t.className='toast show'+(error?' error':'');clearTimeout(toast.timer);toast.timer=setTimeout(()=>t.className='toast',2600)}
function esc(s){return String(s??'').replace(/[&<>"]/g,c=>({'&':'&amp;','<':'&lt;','>':'&gt;','"':'&quot;'}[c]))}
function bytes(n){if(n<1024)return n+' B';if(n<1024*1024)return (n/1024).toFixed(1)+' KB';return (n/1024/1024).toFixed(1)+' MB'}
function markDirty(v=true){dirty=v;$('#saveBtn').textContent=v?'保存 •':'保存'}

async function loadProblems(selectId=null){
  const x=await api('/api/problems'); problems=x.problems; renderProblemList();
  if(selectId) await selectProblem(selectId);
}
function renderProblemList(){
  const q=$('#search').value.trim().toLowerCase();

  // A search for a problem should also find every problem that references it
  // from any >link group (#Link/#Same/#Easy/#Hard/custom groups, etc.).
  // If the query matches a custom display title, resolve that title back to
  // the target problem ID so references written as the ID are found as well.
  const matchedTargetIds = !q ? [] : problems
    .filter(p => [p.id, p.title].join(' ').toLowerCase().includes(q))
    .map(p => p.id.toLowerCase());

  const list=problems.filter(p=>{
    if(!q) return true;
    const own=[p.id,p.title,...(p.tags||[])].join(' ').toLowerCase();
    const linkSearch=(p.link_search||'').toLowerCase();
    const targets=(p.link_targets||[]).map(x=>String(x).trim().toLowerCase());
    const referencesMatchedProblem=matchedTargetIds.some(id=>targets.includes(id));
    return own.includes(q) || linkSearch.includes(q) || referencesMatchedProblem;
  });
  $('#problemCount').textContent=`${list.length} / ${problems.length} 道题`;
  $('#problemList').innerHTML=list.map(p=>`<div class="problem-item ${current?.id===p.id?'active':''}" data-id="${esc(p.id)}"><div class="name">${esc(p.title)}</div><div class="meta"><span>${esc(p.id)}</span>${p.difficulty?`<span>${esc(p.difficulty)}</span>`:''}<span>${esc((p.tags||[]).slice(0,2).join(' · '))}</span></div></div>`).join('');
  $$('.problem-item').forEach(el=>el.onclick=()=>selectProblem(el.dataset.id));
}
async function selectProblem(id){
  if(dirty && !confirm('当前结构化修改尚未保存，确定切换题目？')) return;
  current=await api('/api/problems/'+encodeURIComponent(id)); currentFile=null; dirty=false;
  $('#emptyState').classList.add('hidden'); $('#editor').classList.remove('hidden');
  renderAll(); renderProblemList();
}
function renderAll(){
  const d=current.data;
  $('#problemHeading').textContent=d.title||current.id;
  $('#problemSubheading').textContent=d.title?current.id:'使用目录名作为展示名称';
  $('#problemId').value=current.id; $('#title').value=d.title||''; $('#difficulty').value=d.difficulty||'';
  $('#previewLink').href='/code-saver/problems/'+encodeURIComponent(current.id)+'/';
  renderTags(); renderFrom(); renderLinks(); renderSubs(); renderFiles(); $('#rawConf').value=current.raw_conf;
  markDirty(false);
}
function syncBasic(){current.data.title=$('#title').value;current.data.difficulty=$('#difficulty').value}
function renderTags(){
  $('#tags').innerHTML=current.data.tags.map((t,i)=>`<span class="chip">${esc(t)}<button data-i="${i}">×</button></span>`).join('');
  $$('#tags button').forEach(b=>b.onclick=()=>{current.data.tags.splice(+b.dataset.i,1);renderTags();markDirty()});
}
function addTag(){const i=$('#tagInput'),v=i.value.trim();if(v&&!current.data.tags.includes(v)){current.data.tags.push(v);renderTags();markDirty()}i.value=''}
function renderFrom(){
  const box=$('#fromList'); box.innerHTML=current.data.from.map((x,i)=>`<div class="pair-row"><input data-k="name" data-i="${i}" value="${esc(x.name)}" placeholder="来源名称"><input data-k="url" data-i="${i}" value="${esc(x.url)}" placeholder="URL（可选）"><button class="icon-btn" data-del="${i}">×</button></div>`).join('') || '<div class="hint">暂无来源。</div>';
  box.querySelectorAll('input').forEach(inp=>inp.oninput=()=>{current.data.from[+inp.dataset.i][inp.dataset.k]=inp.value;markDirty()});box.querySelectorAll('[data-del]').forEach(b=>b.onclick=()=>{current.data.from.splice(+b.dataset.del,1);renderFrom();markDirty()})
}
function renderLinks(){
  const box=$('#linkGroups'); box.innerHTML=current.data.links.map((g,gi)=>`<div class="group-card"><div class="group-head"><input class="group-name" data-gname="${gi}" value="${esc(g.name)}" placeholder="分组名称"><span></span><button class="icon-btn" data-gdel="${gi}">删除分组</button></div><div class="group-items">${g.items.map((x,ii)=>`<div class="link-row"><input data-g="${gi}" data-i="${ii}" data-k="name" value="${esc(x.name)}" placeholder="显示名 / 题号"><input data-g="${gi}" data-i="${ii}" data-k="url" value="${esc(x.url)}" placeholder="URL；留空可由生成器自动识别"><button class="icon-btn" data-ldel="${gi}:${ii}">×</button></div>`).join('')}</div><div class="group-foot"><button class="tiny" data-ladd="${gi}">＋ 添加链接</button></div></div>`).join('');
  box.querySelectorAll('[data-gname]').forEach(x=>x.oninput=()=>{current.data.links[+x.dataset.gname].name=x.value;markDirty()});
  box.querySelectorAll('input[data-g]').forEach(x=>x.oninput=()=>{current.data.links[+x.dataset.g].items[+x.dataset.i][x.dataset.k]=x.value;markDirty()});
  box.querySelectorAll('[data-gdel]').forEach(b=>b.onclick=()=>{current.data.links.splice(+b.dataset.gdel,1);renderLinks();markDirty()});
  box.querySelectorAll('[data-ldel]').forEach(b=>b.onclick=()=>{let[g,i]=b.dataset.ldel.split(':').map(Number);current.data.links[g].items.splice(i,1);renderLinks();markDirty()});
  box.querySelectorAll('[data-ladd]').forEach(b=>b.onclick=()=>{current.data.links[+b.dataset.ladd].items.push({name:'',url:''});renderLinks();markDirty()});
}
function renderSubs(){
  const box=$('#subList'); box.innerHTML=current.data.submissions.map((s,i)=>`<div class="sub-row"><label class="radio-wrap"><input type="radio" name="primarySub" data-primary="${i}" ${s.primary?'checked':''}><br>主记录</label><input data-s="${i}" data-k="time" value="${esc(s.time)}" placeholder="YYYY-MM-DD HH:MM:SS"><input data-s="${i}" data-k="name" value="${esc(s.name)}" placeholder="名称"><input data-s="${i}" data-k="url" value="${esc(s.url)}" placeholder="Submission URL"><button class="icon-btn" data-sdel="${i}">×</button></div>`).join('') || '<div class="hint">暂无提交记录。</div>';
  box.querySelectorAll('input[data-s]').forEach(x=>x.oninput=()=>{current.data.submissions[+x.dataset.s][x.dataset.k]=x.value;markDirty()});
  box.querySelectorAll('[data-primary]').forEach(r=>r.onchange=()=>{current.data.submissions.forEach((s,j)=>s.primary=j===+r.dataset.primary);markDirty()});
  box.querySelectorAll('[data-sdel]').forEach(b=>b.onclick=()=>{current.data.submissions.splice(+b.dataset.sdel,1);renderSubs();markDirty()});
}
function renderFiles(){
  $('#fileList').innerHTML=current.files.map(f=>`<div class="file-item ${currentFile===f.name?'active':''}" data-file="${esc(f.name)}"><span>${esc(f.name)}${f.generated?' <small>generated</small>':''}</span><span class="file-size">${bytes(f.size)}</span></div>`).join('');
  $$('.file-item').forEach(x=>x.onclick=()=>openFile(x.dataset.file));
}
async function openFile(name){
  if(name==='problem.conf'){activateTab('conf');return}
  if(name==='index.md') { currentFile=null; $('#fileName').textContent='index.md'; $('#fileMeta').textContent='生成文件，只读'; $('#fileEditor').disabled=true; $('#fileEditor').value='此文件由 ./code0 自动生成。请修改 problem.conf 后重新生成。'; $('#saveFileBtn').classList.add('hidden'); $('#deleteFileBtn').classList.add('hidden'); renderFiles(); return; }
  const x=await api(`/api/problems/${encodeURIComponent(current.id)}/files/${encodeURIComponent(name)}`);currentFile=name;$('#fileName').textContent=name;$('#fileMeta').textContent='Ctrl+S 保存';$('#fileEditor').disabled=false;$('#fileEditor').value=x.content;$('#saveFileBtn').classList.remove('hidden');$('#deleteFileBtn').classList.remove('hidden');renderFiles();
}
async function saveStructured(){syncBasic();try{await api('/api/problems/'+encodeURIComponent(current.id),{method:'PUT',body:JSON.stringify({data:current.data})});toast('已保存并重新生成');await refreshCurrent()}catch(e){toast(e.message,true)}}
async function refreshCurrent(){const id=current.id;current=await api('/api/problems/'+encodeURIComponent(id));renderAll();renderProblemList()}
async function saveRaw(){try{await api(`/api/problems/${encodeURIComponent(current.id)}/conf`,{method:'PUT',body:JSON.stringify({content:$('#rawConf').value})});toast('Raw problem.conf 已保存');await refreshCurrent()}catch(e){toast(e.message,true)}}
async function saveFile(){if(!currentFile)return;try{await api(`/api/problems/${encodeURIComponent(current.id)}/files/${encodeURIComponent(currentFile)}`,{method:'PUT',body:JSON.stringify({content:$('#fileEditor').value})});toast(currentFile+' 已保存');await refreshFilesOnly()}catch(e){toast(e.message,true)}}
async function refreshFilesOnly(){let x=await api('/api/problems/'+encodeURIComponent(current.id));current.files=x.files;current.raw_conf=x.raw_conf;current.data=x.data;renderFiles()}
function activateTab(name){$$('.tabs button').forEach(b=>b.classList.toggle('active',b.dataset.tab===name));$$('.tab-panel').forEach(p=>p.classList.toggle('active',p.dataset.panel===name))}

function modal(html, okText='确定') {return new Promise(resolve=>{const d=$('#modal'),form=$('#modalForm');$('#modalBody').innerHTML=html;$('#modalOk').textContent=okText;d.showModal();form.onsubmit=e=>{const value=e.submitter?.value;resolve(value==='default');};d.oncancel=()=>resolve(false)})}
async function newProblem(){
  const ok=await modal(`<h2>新建题目</h2><div class="modal-grid"><label>题目 ID<input class="modal-input" id="mId" placeholder="QOJ12345" autofocus></label><label>展示名称（可选）<input class="modal-input" id="mTitle"></label><label>主链接题号<input class="modal-input" id="mLink" placeholder="留空则与 ID 相同"></label><label>难度<input class="modal-input" id="mDiff" type="number"></label><label>标签（空格或逗号分隔）<input class="modal-input" id="mTags"></label><label><input id="mSol" type="checkbox"> 同时创建 sol.md</label></div>`,'创建'); if(!ok)return;
  try{const id=$('#mId').value.trim();const x=await api('/api/problems',{method:'POST',body:JSON.stringify({id,title:$('#mTitle').value,link:$('#mLink').value,difficulty:$('#mDiff').value,tags:$('#mTags').value.split(/[，,\s]+/).filter(Boolean),create_solution:$('#mSol').checked})});toast('题目 '+id+' 已创建');await loadProblems(x.id)}catch(e){toast(e.message,true)}
}
async function renameProblem(){const ok=await modal(`<h2>重命名题目目录</h2><p class="hint">这会改变 problems/&lt;ID&gt;/ 路径。problem.conf 内链接不会自动改写。</p><input class="modal-input" id="mRename" value="${esc(current.id)}" autofocus>`,'重命名');if(!ok)return;try{const old=current.id,x=await api(`/api/problems/${encodeURIComponent(old)}/rename`,{method:'POST',body:JSON.stringify({new_id:$('#mRename').value})});toast(`${old} → ${x.id}`);await loadProblems(x.id)}catch(e){toast(e.message,true)}}
async function newFile(){
  const ok=await modal(`<h2>新建文件</h2><div class="modal-grid"><label>文件名<input class="modal-input" id="mFile" placeholder="code1.cpp" autofocus></label><label>类型<select class="modal-input" id="mKind"><option value="code">代码（自动加入 #Code）</option><option value="solution">题解（自动加入 #Solution）</option><option value="other">普通文件</option></select></label><label>显示名称<input class="modal-input" id="mLabel" placeholder="code / brute / solution"></label></div>`,'创建');if(!ok)return;try{current=await api(`/api/problems/${encodeURIComponent(current.id)}/files/create`,{method:'POST',body:JSON.stringify({name:$('#mFile').value,kind:$('#mKind').value,label:$('#mLabel').value})});toast('文件已创建');renderAll();await openFile($('#mFile').value)}catch(e){toast(e.message,true)}}
async function deleteFile(){if(!currentFile||!confirm(`确定删除 ${currentFile}？同时会移除指向它的 #Code/#Solution 链接。`))return;try{current=await api(`/api/problems/${encodeURIComponent(current.id)}/files/${encodeURIComponent(currentFile)}`,{method:'DELETE'});toast(currentFile+' 已删除');currentFile=null;$('#fileEditor').value='';$('#fileEditor').disabled=true;$('#saveFileBtn').classList.add('hidden');$('#deleteFileBtn').classList.add('hidden');renderAll();activateTab('files')}catch(e){toast(e.message,true)}}
async function showGit(){try{const x=await api('/api/git/diff');$('#gitOutput').textContent=(x.status?'STATUS\n'+x.status+'\n':'')+(x.diff||'没有 tracked diff。');$('#gitModal').showModal()}catch(e){toast(e.message,true)}}
async function commitGit(){try{const x=await api('/api/git/commit',{method:'POST',body:JSON.stringify({message:$('#commitMessage').value})});toast('Git commit 完成');$('#gitModal').close();$('#commitMessage').value=''}catch(e){toast(e.message,true)}}

$('#search').oninput=renderProblemList;$('#newProblemBtn').onclick=newProblem;$('#renameBtn').onclick=renameProblem;$('#saveBtn').onclick=saveStructured;$('#saveConfBtn').onclick=saveRaw;$('#addTagBtn').onclick=addTag;$('#tagInput').onkeydown=e=>{if(e.key==='Enter'){e.preventDefault();addTag()}};$('#title').oninput=()=>markDirty();$('#difficulty').oninput=()=>markDirty();
$('#addFromBtn').onclick=()=>{current.data.from.push({name:'',url:''});renderFrom();markDirty()};$('#addGroupBtn').onclick=()=>{current.data.links.push({name:'Group',items:[]});renderLinks();markDirty()};$('#addSubBtn').onclick=()=>{current.data.submissions.push({primary:false,time:new Date().toISOString().slice(0,19).replace('T',' '),name:current.id,url:''});renderSubs();markDirty()};
$('#tabs').onclick=e=>{const b=e.target.closest('button[data-tab]');if(b)activateTab(b.dataset.tab)};$('#newFileBtn').onclick=newFile;$('#saveFileBtn').onclick=saveFile;$('#deleteFileBtn').onclick=deleteFile;$('#rebuildBtn').onclick=async()=>{try{await api('/api/rebuild',{method:'POST',body:'{}'});toast('重新生成完成')}catch(e){toast(e.message,true)}};$('#gitBtn').onclick=showGit;$('#commitBtn').onclick=commitGit;
$('#fileEditor').addEventListener('keydown',e=>{if((e.ctrlKey||e.metaKey)&&e.key.toLowerCase()==='s'){e.preventDefault();saveFile()}if(e.key==='Tab'){e.preventDefault();const t=e.target,s=t.selectionStart,n=t.selectionEnd;t.setRangeText('    ',s,n,'end')}});$('#rawConf').addEventListener('keydown',e=>{if((e.ctrlKey||e.metaKey)&&e.key.toLowerCase()==='s'){e.preventDefault();saveRaw()}if(e.key==='Tab'){e.preventDefault();const t=e.target,s=t.selectionStart,n=t.selectionEnd;t.setRangeText('    ',s,n,'end')}});
window.addEventListener('keydown',e=>{if((e.ctrlKey||e.metaKey)&&e.key.toLowerCase()==='s'&&!['fileEditor','rawConf'].includes(e.target.id)){e.preventDefault();saveStructured()}});window.addEventListener('beforeunload',e=>{if(dirty){e.preventDefault();e.returnValue=''}});
loadProblems().catch(e=>toast(e.message,true));
