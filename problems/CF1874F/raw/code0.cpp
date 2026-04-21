#include <bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int n,r[205],f[205][205],dp[205][205],jie[205];
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n,jie[0]=1;
	for(int i=1;i<=n;i++) cin>>r[i],jie[i]=1ll*jie[i-1]*i%mod;
	if(r[1]==n){cout<<"0\n";return 0;}
	for(int i=n;i>=1;i--){
		f[i-1][0]=1;
		for(int j=i;j<=n;j++){
			for(int k=0;k<=j-i+1;k++){
				if(k) f[j][k]=f[j-1][k-1];
				else f[j][k]=0;
				for(int p=i+1;p<=j;p++) if(r[p]>=j) f[j][k]=(f[j][k]-1ll*f[p-1][k]*dp[p][j])%mod;
				dp[i][j]=(dp[i][j]+1ll*f[j][k]*jie[k])%mod;
			}
			if(r[i]>=j) f[j][0]=(f[j][0]-dp[i][j])%mod;
		}
	}
	cout<<(dp[1][n]+mod)%mod<<"\n";
	return 0;
}