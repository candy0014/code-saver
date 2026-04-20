#include <bits/stdc++.h>
using namespace std;
const int V=20002;
int n,a[1005],b[1005],dp[1005][20005];
void Max(int &u,int v){u=max(u,v);}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>b[1],b[1]--,a[0]=V;
	for(int i=2;i<=n;i++) cin>>a[i-1]>>b[i];
	memset(dp,-0x3f3f3f3f,sizeof(dp));
	dp[0][0]=0;
	for(int i=0;i<n;i++){
		int ma=-0x3f3f3f3f;
		for(int j=0;j<a[i];j++) ma=max(ma,dp[i][j]);
		for(int j=0;j<b[i+1];j++) dp[i+1][j]=ma+j;
		for(int j=0;j<a[i];j++) Max(dp[i+1][b[i+1]+j],dp[i][j]+b[i+1]);
		for(int j=a[i];j<a[i]+b[i+1];j++) Max(dp[i+1][j-a[i]],dp[i][j]);
		for(int j=a[i]+b[i+1];j<=V;j++) Max(dp[i+1][j],dp[i][j]);
	}
	int res=0;
	for(int i=0;i<=V;i++) res=max(res,dp[n][i]);
	cout<<res<<"\n";
	return 0;
}