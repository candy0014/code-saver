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
int n,cnt[5005],a[5005],b[5005],val[5005][5005],A[5005][5005];
int dp[5005][5005];
void solve(int Ca){
	cin>>n;
	for(int i=0;i<=n;i++){
		A[i][0]=1;
		for(int j=1;j<=i;j++) A[i][j]=1ll*A[i][j-1]*(i-j+1)%mod;
	}
	for(int i=1,u;i<=n;i++) cin>>u,cnt[min(u,n+1)]++;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	for(int i=1;i<=n;i++){
		val[i][i-1]=1;
		for(int j=i;j<=n;j++) val[i][j]=1ll*val[i][j-1]*(1ll*a[j]*(j+1)%mod+b[j])%mod;
	}
	dp[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=i;j<=i+cnt[i]&&j<=n;j++){
			int tmp=1ll*val[i][j-1]*(1ll*a[j]*i%mod+b[j])%mod;
			for(int k=0;k<n;k++) if(dp[i-1][k]){
				int t=1ll*dp[i-1][k]*tmp%mod;
				dp[j][k+1]=(dp[j][k+1]+1ll*t*A[cnt[i]][j-i]%mod*(k+1))%mod;
				dp[j][k]=(dp[j][k]-1ll*t*A[cnt[i]][j-i+1]%mod+mod)%mod;
			}
		}
		for(int k=0;k<n;k++) if(dp[i-1][k]){
			dp[n][k]=(dp[n][k]+1ll*dp[i-1][k]*val[i][n]%mod*A[cnt[i]][n-i+1])%mod;
		}
	}
	int res=0;
	for(int k=0;k<=n;k++) res=(res+dp[n][k])%mod;
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
	
	int Ca=1;
//	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}