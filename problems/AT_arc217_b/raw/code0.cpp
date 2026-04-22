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
int jie[500005],inv[500005];
int n,m,a[500005],pw[500005];
void solve(int Ca){
	cin>>n>>m;
	int al=jie[n-m],res=0,cnt=m,ma=0;
	for(int i=1;i<=m;i++){
		cin>>a[i],ma=max(ma,a[i]);
		if(a[i]==ma) res=(res+1ll*al*pw[a[i]-1])%mod;
	}
	for(int i=ma+1;i<=n;i++) res=(res+1ll*al*inv[n-i+1]%mod*pw[i-1])%mod;
	res=(1ll*al*(pw[n]-1)%mod-res+mod)%mod;
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
	jie[0]=pw[0]=inv[1]=1;
	for(int i=1;i<=500000;i++) jie[i]=1ll*jie[i-1]*i%mod,pw[i]=pw[i-1]*2%mod;
	for(int i=2;i<=500000;i++) inv[i]=mod-1ll*mod/i*inv[mod%i]%mod;
	int Ca=1;
	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}