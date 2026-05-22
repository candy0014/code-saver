#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
int n,dp[1205][605],C[1205][1205],tag[1205],f[605];
void add(int &u,ll v){u=(u+v)%mod;}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1,u;i<=n;i++) cin>>u,tag[u]=1;
	for(int i=0;i<=2*n;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	}
	f[0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<i;j++) add(f[i],1ll*f[j]*f[i-j-1]%mod*C[i-1][j]%mod*(i-j+1));
	}
	dp[n*2+1][0]=1;
	for(int i=n*2,c0=0,c1=0;i>=1;i--){
		for(int j=0;j<=c1;j++){
			int x=dp[i+1][j];
			if(!x) continue;
			if(!tag[i]) add(dp[i][j],1ll*x*(j-c0));
			else{
				add(dp[i][j],x);
				for(int k=j+1;k<=c1+1;k++){
					add(dp[i][k],1ll*x*C[c1-j][k-j-1]%mod*(k-j+1)%mod*f[k-j-1]);
				}
			}
		}
		(tag[i]?c1:c0)++;
	}
	int res=dp[1][n];
	for(int i=1;i<=n;i++) res=1ll*res*(mod+1)/2%mod;
	cout<<res<<"\n";
	return 0;
}