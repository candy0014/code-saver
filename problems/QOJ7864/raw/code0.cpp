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
ll ksm(ll u,ll v=mod-2){ll tmp=1;u%=mod;while(v) tmp=tmp*((v&1)?u:1)%mod,u=u*u%mod,v>>=1;return tmp;}
int n,fa[100005],de[100005];
vector<int>dp[100005],e[100005];
int f[100005];
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
void solve(int Ca){
	init();
	cin>>n,de[1]=1;
	for(int i=2;i<=n;i++) cin>>fa[i],de[i]=de[fa[i]]+1,e[fa[i]].emplace_back(i);
	for(int i=n;i>=1;i--){
		dp[i].resize(de[i]+1);
		f[0]=1;
		for(int j=1;j<=de[i]+2;j++) f[j]=0;
		for(auto v:e[i]){
			for(int j=de[i]+1;j>=0;j--) for(int k=0;k<=j;k++){
				if(k==0) f[j]=1ll*f[j]*dp[v][k]%mod;
				else f[j]=(f[j]+1ll*f[j-k]*dp[v][k])%mod;
			}
		}
		for(int j=0;j<=de[i];j++){
			for(int k=0;k<=j+1;k++){
				dp[i][j]=(dp[i][j]+1ll*f[j-k+1]*inv[k])%mod;
			}
		}
	}
	cout<<1ll*dp[1][0]*jie[n]%mod<<"\n";
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
//	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}