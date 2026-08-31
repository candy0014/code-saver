#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
ll ksm(ll u,ll v=mod-2){ll tmp=1;u%=mod;while(v) tmp=tmp*((v&1)?u:1)%mod,u=u*u%mod,v>>=1;return tmp;}
int n,m;
int x[505],v[505];
vector<pair<int,int> >p;
int dp[505],now[505],f[505];
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>x[i],x[i]=-x[i];
	for(int i=1;i<=m;i++) cin>>v[i];
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) p.emplace_back(i,j);
	sort(p.begin(),p.end(),[&](pair<int,int>a,pair<int,int>b){
		int x1=x[a.first],v1=v[a.second];
		int x2=x[b.first],v2=v[b.second];
		return 1ll*x1*v2<1ll*x2*v1;
	});
	dp[0]=ksm(n,m);
	int res=0;
	for(auto [a,b]:p){
		int tmp=ksm(n-now[b]);
		f[0]=1ll*dp[0]*tmp%mod;
		for(int i=1;i<=m;i++) f[i]=(dp[i]-1ll*f[i-1]*now[b]%mod+mod)%mod*tmp%mod;
		for(int i=0;i<=m;i++) dp[i]=f[i];
		res=(res+1ll*x[a]*ksm(v[b])%mod*dp[m/2])%mod;
		now[b]++;
		f[0]=1ll*dp[0]*(n-now[b])%mod;
		for(int i=1;i<=m;i++) f[i]=(1ll*dp[i-1]*now[b]+1ll*dp[i]*(n-now[b]))%mod;
		for(int i=0;i<=m;i++) dp[i]=f[i];
	}
	cout<<1ll*res*ksm(ksm(n,m))%mod<<"\n";
	return 0;
}