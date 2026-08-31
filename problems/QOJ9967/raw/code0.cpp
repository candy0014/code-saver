#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
const ll mod=1e9+7;
const ll inf=2e9;
const int N=2e5+5;
const int M=2e5+5;
const int V=2e6+5;
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
int n,k;
int a[2005],cnt[1000005];
void solve(int Ca){
	init();
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i],cnt[a[i]]++;
	sort(a+1,a+n+1);
	int c0=0,c1=0;
	ll res=0;
	for(int i=1;i<=k;i++) c0+=a[i]==a[k],res-=a[i];
	for(int i=n-k+1;i<=n;i++) c1+=a[i]==a[n-k+1],res+=a[i];
	cout<<res<<" ";
	if(a[k]!=a[n-k+1]){
		cout<<1ll*C(cnt[a[k]],c0)*C(cnt[a[n-k+1]],c1)%mod<<"\n";
	}
	else if(a[1]!=a[n]){
		cout<<1ll*C(cnt[a[k]],c0)*C(cnt[a[k]]-c0,c1)%mod<<"\n";
	}
	else{
		cout<<1ll*C(n,k)*C(n-k,k)%mod*ksm(2)%mod<<"\n";
	}
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
	// cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}