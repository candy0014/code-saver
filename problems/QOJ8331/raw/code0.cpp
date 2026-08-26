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
int n,m;
vector<int>e[200005];
set<int>ee[200005];
int p[200005],q[200005],fat[200005][20],de[200005];
void dfs(int u,int fa){
	fat[u][0]=fa,de[u]=de[fa]+1;
	for(int i=1;i<20;i++) fat[u][i]=fat[fat[u][i-1]][i-1];
	if(u<=m) p[u]=u;
	for(auto v:e[u]) if(v!=fa) dfs(v,u),p[u]=p[v];
}
int get(int u,int k){
	for(int i=0;i<20;i++) if((k>>i)&1) u=fat[u][i];
	return u; 
}
int dp[200005];
void dfs2(int u,int fa){
	if(u<=m){dp[u]=1;return;}
	dp[u]=0;
	for(auto v:e[u]) if(v!=fa) dfs2(v,u);
	int t=q[u];
	for(auto v:e[u]) if(v!=fa&&!dp[v]) return;
	for(auto v:e[u]) if(v!=fa){
		int g=q[v];
		if(g!=t&&ee[t].find(g)==ee[t].end()) return;
	}
	dp[u]=1;
}
void solve(int Ca){
	cin>>n>>m;
	for(int i=1;i<=n;i++) e[i].clear(),ee[i].clear();
	for(int i=1,u,v;i<n;i++) cin>>u>>v,e[u].emplace_back(v),e[v].emplace_back(u),ee[u].insert(v),ee[v].insert(u);
	dfs(n,0);
	for(int i=1;i<n;i++) ee[i].erase(fat[i][0]);
	for(int i=1;i<=n;i++){
		int u=p[i]%m+1;
		if(de[u]<=de[i]) q[i]=u;
		else q[i]=get(u,de[u]-de[i]);
	}
	dfs2(n,0);
	if(dp[n]) cout<<"Doddle\n";
	else cout<<"Tie\n";
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