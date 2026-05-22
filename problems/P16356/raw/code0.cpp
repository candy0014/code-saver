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
int n,lim,a[300005];
ll dp[300005],res;
vector<int>e[300005];
void dfs1(int u,int rt,int fa=0,int de=0){
	if(u!=rt) dp[u]=max(dp[u],dp[rt]+a[rt]%a[u]);
	if(u!=rt&&a[u]*2>a[rt]) return;
	if(de==lim) return;
	for(auto v:e[u]) if(v!=fa) dfs1(v,rt,u,de+1);
}
void dfs(int u,int fa=0){
	res=max(res,dp[u]),dfs1(u,u,fa);
	for(auto v:e[u]) if(v!=fa) dfs(v,u);
}
void solve(int Ca){
	cin>>n>>lim;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1,u,v;i<n;i++) cin>>u>>v,e[u].emplace_back(v),e[v].emplace_back(u);
	dfs(1);
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
//	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}