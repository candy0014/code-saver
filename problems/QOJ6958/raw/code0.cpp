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
vector<pair<int,int> >e[1000005];
vector<int> ee[1000005];
int fat[1000005][21],de[1000005];
int n;
int szz[1000005];
void dfs(int u){
	de[u]=de[fat[u][0]]+1,szz[u]=1;
	for(int i=1;i<=20;i++) fat[u][i]=fat[fat[u][i-1]][i-1];
	for(auto [v,w]:e[u]) dfs(v),szz[u]+=szz[v];
}
int sz[1000005];
void dfs2(int u){
	sz[u]=1;
	for(auto v:ee[u]) dfs2(v),sz[u]+=sz[v];
}
int LCA(int u,int v){
	if(de[u]<de[v]) swap(u,v);
	for(int i=20;i>=0;i--) if(de[fat[u][i]]>=de[v]) u=fat[u][i];
	if(u==v) return u;
	for(int i=20;i>=0;i--) if(fat[u][i]!=fat[v][i]) u=fat[u][i],v=fat[v][i];
	return fat[u][0];
}
ll sum[1000005];
void add(int u,int v,ll w){
	int lca=LCA(u,v);
	sum[u]+=w,sum[v]+=w,sum[lca]-=2*w;
}
void dfs3(int u){
	for(auto [v,w]:e[u]) dfs3(v),sum[u]+=sum[v];
}
void solve(int Ca){
	cin>>n;
	for(int i=1;i<=n;i++) e[i].clear(),ee[i].clear(),sum[i]=0;
	for(int i=2;i<=n;i++) cin>>fat[i][0];
	for(int i=2,w;i<=n;i++) cin>>w,e[fat[i][0]].emplace_back(i,w);
	for(int i=2,u;i<=n;i++) cin>>u,ee[u].emplace_back(i);
	dfs(1),dfs2(1);
	for(int i=1;i<=n;i++) for(auto v:ee[i]) add(i,v,1ll*sz[v]*(n-sz[v]));
	dfs3(1);
	int res=0;
	for(int i=1;i<=n;i++) for(auto [v,w]:e[i]) if(sum[v]!=1ll*szz[v]*(n-szz[v])&&w) res++;
	cout<<res<<"\n";
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
	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}