#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
ll ksm(ll u,ll v=mod-2){ll tmp=1;u%=mod;while(v) tmp=tmp*((v&1)?u:1)%mod,u=u*u%mod,v>>=1;return tmp;}
int n,m,sz[2505];
vector<pair<int,int> >e[2505];
int C[2505][2505],f[2505][2505],sf[2505][2505],g[2005],res;
void dfs(int u,int fa){
	sz[u]=1;
	for(auto [v,w]:e[u]) if(v!=fa) dfs(v,u),sz[u]+=sz[v],res=(res+1ll*g[sz[v]]*w)%mod;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=0;i<=n;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	}
	for(int i=1;i<n;i++) for(int j=0;j<=m;j++) f[i][j]=1ll*C[m][j]*ksm(i,j)%mod*ksm(n-i,m-j)%mod,sf[i][j]=((j?sf[i][j-1]:0)+f[i][j])%mod;
	for(int i=1;i<n;i++){
		for(int a=0;a<=m;a++) g[i]=(g[i]+2ll*f[i][a]*a%mod*sf[i][m-a])%mod;
		for(int a=0;a<m;a++) g[i]=(g[i]+2ll*f[n-i][a]*a%mod*sf[n-i][m-1-a])%mod;
	}
	for(int i=1,u,v,w;i<n;i++) cin>>u>>v>>w,e[u].emplace_back(v,w),e[v].emplace_back(u,w);
	dfs(1,0);
	cout<<res<<"\n";
	return 0;
}