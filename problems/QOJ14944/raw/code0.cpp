#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=998244353;
ll ksm(ll u,ll v=mod-2){ll tmp=1;u%=mod;while(v) tmp=tmp*((v&1)?u:1)%mod,u=u*u%mod,v>>=1;return tmp;}
int n,m,a[200005],vis[10005],pre[200005],dp[200005];
vector<int>p;
void solve(){
	cin>>n>>m;
	for(int i=1;i<=n+n;i++) vis[i]=0;
	for(int i=1;i<=m;i++) cin>>a[i],pre[i]=vis[a[i]],vis[a[i]]=i;
	for(int i=0;i<=m;i++) dp[i]=0;
	p.clear();
	for(int i=m;i>=1;i--){
		dp[i-1]=max(dp[i-1],dp[i]+1);
		if(pre[i]) dp[pre[i]]=max(dp[pre[i]],dp[i]+n+1);
		else p.emplace_back(dp[i]+1);
	}
	int L=dp[0],R=0;
	for(auto x:p) L=max(L,x),R=max(R,n+x);
	sort(p.begin(),p.end(),[&](int u,int v){return u>v;});
	int m=p.size(),la=0,ans=0;
	for(int i=L;i<=R;i++){
		int res=1;
		for(int j=0;j<m;j++) res=1ll*res*(min(n+n,i-p[j]+n)-j)%mod;
		for(int j=m;j<n+n;j++) res=1ll*res*(n+n-j)%mod;
		ans=(ans+1ll*i*(res-la))%mod,la=res;
	}
	int tmp=1;
	for(int i=1;i<=n+n;i++) tmp=1ll*tmp*i%mod;
	cout<<(1ll*ans*ksm(tmp)%mod+mod)%mod<<"\n";
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}
