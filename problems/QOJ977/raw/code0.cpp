#include <bits/stdc++.h>
using namespace std;
int n,m,mod,inv[9000005],dp[3005][3005];
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>mod,inv[1]=1;
	for(int i=2;i<=n*m;i++) inv[i]=mod-1ll*mod/i*inv[mod%i]%mod;
	for(int i=n;i>=1;i--) for(int j=m;j>=1;j--){
		if(i==n&&j==m) dp[i][j]=1;
		else dp[i][j]=(1ll*i*inv[n*m-i*j]%mod*dp[i][j+1]+1ll*j*inv[n*m-i*j]%mod*dp[i+1][j])%mod;
	}
	int res=dp[1][1];
	for(int i=1;i<=n;i++) res=1ll*res*i%mod;
	for(int i=1;i<=m;i++) res=1ll*res*i%mod;
	for(int i=1;i<n*m;i++) res=1ll*res*i%mod;
	cout<<res<<"\n";
	return 0;
}