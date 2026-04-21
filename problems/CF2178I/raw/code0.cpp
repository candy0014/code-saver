#include <bits/stdc++.h>
using namespace std;
const int mod=998244353;
int n,k,x[35],y[35],co[35],e[35];
vector<int>ee[35],p[2];
int cnt[2],id[35];
int dp[32768],f[32768];
void dfs(int u){
	cnt[co[u]]++;
	for(auto v:ee[u]) if(co[v]==-1) co[v]=co[u]^1,dfs(v);
}
vector<int>g;
void solve(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>x[i]>>y[i];
	for(int i=1;i<=n;i++) co[i]=-1,e[i]=0,ee[i].clear();
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])==k) ee[i].emplace_back(j);
	for(int i=1;i<=n;i++) if(co[i]==-1) co[i]=0,dfs(i);
	if(cnt[0]>cnt[1]){
		swap(cnt[0],cnt[1]);
		for(int i=1;i<=n;i++) co[i]^=1;
	}
	p[0].clear(),p[1].clear(),cnt[0]=cnt[1]=0;
	for(int i=1;i<=n;i++) id[i]=cnt[co[i]]++,p[co[i]].emplace_back(i);
	for(int i=1;i<=n;i++) for(auto v:ee[i]) e[i]|=(1<<id[v]);
	int res=0;
	for(int i=0;i<(1<<cnt[0]);i++){
		int tmp=((1<<cnt[0])-1)^i;
		g.clear();
		for(int k=tmp;k;k=(k-1)&tmp) dp[k]=0,g.emplace_back(k);
		dp[0]=1,g.emplace_back(0),reverse(g.begin(),g.end());
		for(int j=0;j<cnt[1];j++){
			int u=p[1][j],tt=__builtin_popcount(i&e[u])+1;
			for(auto k:g) f[k]=1ll*dp[k]*tt%mod;
			for(int k=0;k<cnt[0];k++) if(((tmp&e[u])>>k)&1){
				for(auto h:g) if((h>>k)&1) dp[h]=(dp[h]+dp[h^(1<<k)])%mod;
			}
			for(auto k:g) dp[k]=(dp[k]+f[k])%mod;
		}
		for(auto k:g) res=(res+dp[k])%mod;
	}
	cout<<(res-1+mod)%mod<<"\n";
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}