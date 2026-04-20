#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
int mod;
const ll inf=2e9;
const int N=2e5+5;
const int M=2e5+5;
const int V=2e6+5;
int n,dp[5005],f[5005],res[5005];
int C[5005][5005],pw[25000005];
void solve(int Ca){
	cin>>mod>>n,n%=(mod-1);
	if(!n) n=mod-1;
	for(int i=0;i<=n;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	}
	pw[0]=1;
	for(int i=1;i<=n*n;i++) pw[i]=(pw[i-1]+pw[i-1])%mod;
	res[0]=1;
	for(int i=1;i<=n;i++){
		int tmp=0;
		for(int j=1;j<=i;j++) tmp=(tmp+1ll*C[i-1][j-1]*pw[j*(i-j)])%mod;
		for(int j=1;j<i;j++) tmp=(tmp-1ll*C[i-1][j-1]*dp[j]%mod*f[i-j])%mod;
		tmp=(tmp+mod)%mod;
		dp[i]=tmp;
		for(int j=1;j<i;j++) f[i]=(f[i]+2ll*C[i-1][j-1]*dp[j]%mod*f[i-j])%mod;
		f[i]=(f[i]+2ll*dp[i])%mod;
		for(int j=1;j<=i;j++) res[i]=(res[i]+1ll*C[i-1][j-1]*dp[j]%mod*res[i-j])%mod;
	}
	cout<<res[n]<<"\n";
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