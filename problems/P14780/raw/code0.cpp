#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
int dp[3005][3005][2],sz[3005];
int n;
vector<int>e[3005];
int f[2][3005][2];
int res[3005];
void add(int &u,ll v){u=(u+v)%mod;}
void dfs(int u,int fa){
	for(auto v:e[u]) if(v!=fa) dfs(v,u);
	sz[u]=1;
	memset(f,0,sizeof(f));
	f[0][0][0]=1;
	int now=0;
	for(auto v:e[u]) if(v!=fa){
		memset(f[now^1],0,sizeof(f[now^1]));
		for(int i=0;i<=sz[u];i++) for(int j=0;j<=sz[v];j++){
			add(f[now^1][i+j][0],1ll*f[now][i][0]*dp[v][j][0]);
			add(f[now^1][i+j][1],1ll*f[now][i][1]*dp[v][j][0]+1ll*f[now][i][0]*dp[v][j][1]);
		}
		sz[u]+=sz[v],now^=1;
	}
	for(int i=0;i<=sz[u];i++) dp[u][i][0]=f[now][i][0],dp[u][i][1]=f[now][i][1];
	for(int i=0;i<sz[u];i++) add(dp[u][i+1][1],dp[u][i][0]);
	add(dp[u][1][0],1);
	if(u!=1) for(int i=1;i<=sz[u];i++) add(res[i+1],dp[u][i][1]);
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1,u,v;i<n;i++) cin>>u>>v,e[u].emplace_back(v),e[v].emplace_back(u);
	dfs(1,0);
	for(int i=1;i<=n;i++) add(res[i],dp[1][i][1]);
	for(int i=1;i<=n;i++) cout<<res[i]<<" \n"[i==n];
	return 0;
}