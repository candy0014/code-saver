#include <bits/stdc++.h>
using namespace std;
int n,m,du[200005],fa[200005],sz[200005],cnt;
int st[2000005],tot;
void init(){
	for(int i=1;i<=n;i++) fa[i]=i,sz[i]=1;
	tot=0,cnt=0;
}
int Find(int u){return fa[u]==u?u:Find(fa[u]);}
bool merge(int u,int v){
	u=Find(u),v=Find(v);
	if(u==v) return 0;
	if(sz[u]>sz[v]) swap(u,v);
	cnt-=(sz[u]>1)+(sz[v]>1);
	st[++tot]=u,sz[v]+=sz[u],fa[u]=v,cnt++;
	return 1;
}
void apart(){
	int u=st[tot--],v=fa[u];
	sz[v]-=sz[u],fa[u]=u,cnt--,cnt+=(sz[u]>1)+(sz[v]>1);
}
vector<pair<int,int> >e[200005],ee;
int res[200005],rt,ban,la[200005],tag[200005],ans[200005];
int vis[200005];
void solve(int u){
	init();
	for(int i=1;i<=m;i++) vis[i]=1;
	for(auto [v,id]:e[u]) if(du[v]&1) vis[id]=0;
	for(int i=1;i<=m;i++) if(vis[i]) merge(ee[i].first,ee[i].second);
	if(tag[u]==1){
		if(!cnt||(cnt==1&&sz[Find(u)]>1)) ans[u]=0;
		else{
			ans[u]=-1;
			for(auto [v,id]:e[u]) if((du[v]&1)&&merge(u,v)){
				if(cnt<=1) ans[u]=v;
				apart();
				if(ans[u]!=-1) break;
			}
		}
	}
	if(tag[u]==2){
		if(cnt>=2||(cnt==1&&Find(ans[u])!=Find(u))) ans[u]=-1;
	}
}
vector<int>ans1,ans2;
void dfs(int u){
	while(e[u].size()){
		int v=e[u].back().first,id=e[u].back().second;e[u].pop_back();
		if(res[id]) continue;
		res[id]=1,dfs(v);
	}
	ans1.emplace_back(u);
}
set<pair<int,int> >mp;
void solve(){
	cin>>n>>m;
	if(!m){cout<<"0\n\n0\n\n";return;}
	for(int i=1;i<=n;i++) e[i].clear(),du[i]=0,tag[i]=0;
	ee.clear();ee.emplace_back(0,0);
	init();
	mp.clear();
	for(int i=1,u,v;i<=m;i++){
		res[i]=1;
		cin>>u>>v,e[u].emplace_back(v,i),e[v].emplace_back(u,i);
		ee.emplace_back(u,v);
		merge(u,v);
		mp.insert(make_pair(min(u,v),max(u,v)));
		du[u]++,du[v]++;
	}
	if(cnt!=1){cout<<"0\n";return;}
	for(int i=1;i<=n;i++) if(sz[i]>1) rt=i,ban=0;
	int c=0,g=0;
	for(int i=1;i<=n;i++) if(du[i]&1) c++,g^=i;
	if(c==2){
		rt=0;
		for(int i=1;i<=n;i++) if(du[i]&1){
			if(!rt) rt=i;
			else ban=i;
		}
	}
	if(c>2){
		init();
		int flag=0;
		for(int u=1;u<=n;u++){
			int t=0,tg=g;
			if(du[u]&1) t++,tg^=u;
			for(auto [v,id]:e[u]) if(du[v]&1) t++,tg^=v;
			tag[u]=0;
			if(t==c) tag[u]=1;
			else if(t+1==c) tag[u]=2,ans[u]=tg;
			else continue;
			solve(u);
			if(ans[u]!=-1){
				if(tag[u]==1) rt=u,ban=ans[u];
				else rt=u,ban=0;
				flag=1;break;
			}
		}
		if(!flag){cout<<"0\n";return;}
	}
	ans2.clear();
	for(auto [v,id]:e[rt]) if((du[v]&1)&&v!=ban) res[id]=0,ans2.emplace_back(v),ans2.emplace_back(rt);
	for(int i=1;i<=n;i++) e[i].clear();
	for(int i=1;i<=m;i++) if(res[i]){
		e[ee[i].first].emplace_back(ee[i].second,i),e[ee[i].second].emplace_back(ee[i].first,i),res[i]=0;
	}
	ans1.clear(),dfs(rt);
	cout<<ans1.size()+ans2.size()+1<<"\n";
	for(auto x:ans1) cout<<x<<" ";
	cout<<-1<<" ";
	for(auto x:ans2) cout<<x<<" ";cout<<"\n";
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca=1;while(Ca--)solve();
	return 0;
}