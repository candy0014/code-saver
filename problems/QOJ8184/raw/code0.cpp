#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=998244353,N=1000005;
ll ksm(ll u,ll v=mod-2){ll tmp=1;u%=mod;while(v) tmp=tmp*((v&1)?u:1)%mod,u=u*u%mod,v>>=1;return tmp;}
ll jie[N],inv[N];
void init(int n=N-3){
	jie[0]=1;
	for(int i=1;i<=n;i++) jie[i]=1ll*jie[i-1]*i%mod;
	inv[n]=ksm(jie[n],mod-2);
	for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
ll A(ll u,ll v){
	if(v<0||v>u) return 0;
	return 1ll*jie[u]*inv[u-v]%mod;
}
ll C(ll u,ll v){
	if(v<0||v>u) return 0;
	return 1ll*jie[u]*inv[v]%mod*inv[u-v]%mod;
}
int val[505];
int iv[505];
ll calc(ll n,ll m,ll x){
	if(n<-1) return 0;
	if(m<0) return (n+1)%x==0;
	if(n<0) return 0;
	int t=n%x;
	ll g=n/x,res=0;
	for(int i=0;i<=m+1;i++) val[i]=(C(t+i*x,m)+(i?val[i-1]:0))%mod;
	if(g<=m+1) return val[g];
	for(int i=0;i<=m+1;i++){
		ll tmp=1;
		for(int j=0;j<=m+1;j++) if(i!=j) tmp=1ll*tmp*(g%mod-j+mod)%mod*iv[abs(i-j)]%mod;
		if((m+1-i)&1) tmp=mod-tmp;
		res=(res+1ll*val[i]*tmp)%mod;
	}
	return res;
}
ll n,m;
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	init();
	cin>>n>>m;
	iv[1]=1;
	for(int i=2;i<=m+2;i++) iv[i]=mod-1ll*mod/i*iv[mod%i]%mod;
	int res=0;
	for(int i=1;i<=m;i++){
		int tmp=1ll*C(m,i)*calc(n-i-1,m-i-1,i)%mod;
		if(i%2==0) tmp=mod-tmp;
		res=(res+tmp)%mod;
	}
	cout<<res<<"\n";
	return 0;
}