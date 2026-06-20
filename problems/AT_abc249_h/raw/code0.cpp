#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=998244353,inv2=(mod+1)/2;
ll ksm(ll u,ll v=mod-2){ll tmp=1;u%=mod;while(v) tmp=tmp*((v&1)?u:1)%mod,u=u*u%mod,v>>=1;return tmp;}
int n,cnt[3005],s[3005],C[3005][3005],c[3005],pw[3005],ipw[3005];
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n,pw[0]=ipw[0]=1;
	for(int i=1,u;i<=n;i++) cin>>u,cnt[u]++,pw[i]=pw[i-1]*2%mod,ipw[i]=ipw[i-1]*inv2%mod;
	for(int i=0;i<=n;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	}
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) s[i]=(s[i]+C[cnt[j]][i]);
	c[1]=2*ksm(n)%mod;
	for(int i=1;i<n;i++) c[i+1]=1ll*c[i]*(1-ipw[i])%mod*n%mod*pw[i+1]%mod*ksm(n-i)%mod;
	ll sum=0,last=0;
	for(int i=1;i<=n;i++) sum=(sum+1ll*s[i]*c[i])%mod,last=(last+1ll*C[n][i]*c[i])%mod;
	cout<<((last-sum)%mod+mod)%mod;
	return 0;
}