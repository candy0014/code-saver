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
int n,du[200005],to[200005];
vector<int>e[200005];
int ma[200005];
void dfs(int u,int fa){
	ma[u]=0;
	for(auto v:e[u]) if(v!=fa){
		dfs(v,u);
		if(u==n&&ma[v]==n-1) continue;
		ma[u]=max(ma[u],ma[v]);
	}
	if(ma[u]<u) to[u]=ma[u]+1,ma[u]=u;
	else to[u]=0;
}
int dp[200005],sum[200005];
void solve(int Ca){
	cin>>n;
	for(int i=1;i<=n;i++) e[i].clear(),du[i]=0;
	for(int i=1,u,v;i<n;i++) cin>>u>>v,e[u].emplace_back(v),e[v].emplace_back(u),du[u]++,du[v]++;
	if(du[n]==1){cout<<"1\n";return;}
	int t=0;
	for(int i=1;i<=n;i++) if(du[i]==1) t=i;
	dfs(n,0);
	for(int i=1;i<=n;i++) sum[i]=dp[i]=0;
	dp[t]=1,sum[t]=1;
	for(int i=t+1;i<=n;i++){
		if(to[i]) dp[i]=(sum[i-1]-sum[to[i]-1]+mod)%mod;
		sum[i]=(sum[i-1]+dp[i])%mod;
	}
	cout<<dp[n]<<"\n";
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