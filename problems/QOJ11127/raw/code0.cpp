#include <bits/stdc++.h>
using namespace std;
int n,mod,dp[505][505][2],f[505][505][2],s1[505][505],s2[505][505];
void add(int &u,int v){u+=v,u-=(u>=mod)*mod;}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>mod;
	dp[1][1][1]=1;
	for(int i=1;i<n;i++){
		memset(f,0,sizeof(f)),memset(s1,0,sizeof(s1)),memset(s2,0,sizeof(s2));
		for(int j=1;j<=i;j++){
			for(int k=1;k<=i;k++){
				int x=dp[j][k][0],y=dp[j][k][1];
				int z=(x+y)%mod;
				if(!x&&!y) continue;
				add(s1[j-1][k],z);
				add(f[j][k][0],x);
				add(f[j][k][1],y);
				add(f[j+1][k+1][1],x);
				add(s2[j+2][k],x);
				add(s2[j+1][k],y);
			}
		}
		for(int j=i-1;j>=1;j--) for(int k=1;k<=i;k++) add(s1[j][k],s1[j+1][k]);
		for(int j=1;j<=i;j++) for(int k=1;k<=i;k++) add(s2[j][k],s2[j-1][k+1]);
		for(int j=1;j<=i+1;j++) for(int k=1;k<=i+1;k++)
			dp[j][k][0]=(f[j][k][0]+s1[j][k])%mod,dp[j][k][1]=(f[j][k][1]+s2[j][k])%mod;
	}
	int res=0;
	for(int j=1;j<=n;j++) for(int k=1;k<=n;k++) add(res,dp[j][k][0]),add(res,dp[j][k][1]);
	cout<<res<<"\n";
	return 0;
}