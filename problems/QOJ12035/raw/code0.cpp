#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
const ll mod=998244353;
const ll inf=2e9;
const int N=2e5+5;
const int M=2e5+5;
const int V=2e6+5;
int n,m,al,sz[105],rt;
vector<int>e[105];
void dfs(int u,int fa){
	sz[u]=(e[u].size()==1);
	int ma=0;
	for(auto v:e[u]) if(v!=fa) dfs(v,u),sz[u]+=sz[v],ma=max(ma,sz[v]);
	ma=max(ma,al-sz[u]);
	if(ma<=(al+1)/2) rt=u;
}
vector<int>p;
int fat[105],vis[105][105],ans[105][105];
void dfs2(int u,int fa){
	if(e[u].size()==1) p.emplace_back(u);
	for(auto v:e[u]) if(v!=fa) dfs2(v,u);
}
void dfs3(int u,int fa){
	fat[u]=fa;
	for(auto v:e[u]) if(v!=fa) dfs3(v,u);
}
void dfs4(int u,int fa,int co,int num){
	ans[u][num]=co;
	for(auto v:e[u]) if(v!=fa&&!ans[v][num]) dfs4(v,u,co,num);
}
void work(int u,int v,int num){
	dfs3(u,0);
	int cnt=1;
	while(v){
		if(!vis[v][fat[v]]){
			vis[v][fat[v]]=vis[fat[v]][v]=1;
			dfs4(v,fat[v],cnt,num),cnt++;
		}
		v=fat[v];
	}
}
void solve(int Ca){
	cin>>n;
	for(int i=1,u,v;i<n;i++) cin>>u>>v,e[u].emplace_back(v),e[v].emplace_back(u);
	for(int i=1;i<=n;i++) al+=(e[i].size()==1);
	dfs(1,0),dfs2(rt,0);
	m=(al+1)/2;
	for(int i=0;i<m;i++){
		int j=(i+m)%p.size();
		work(p[i],p[j],i);
	}
	cout<<m<<"\n";
	for(int i=1;i<=n;i++) for(int j=0;j<m;j++) cout<<ans[i][j]<<" \n"[j==m-1];
}
int main(){
	#ifdef ONLINE_JUDGE
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	#endif
	#ifndef ONLINE_JUDGE
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	
	int Ca=1;
//	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}