#include <bits/stdc++.h>
using namespace std;
int n,mod,m;
int p[500005],inv[500005],f[505][505],g[505][505],C[505][505];
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>mod,m=n*n+n,inv[1]=1,p[n]=1;
	for(int i=0;i<=n;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	}
	for(int i=2;i<=m;i++) inv[i]=mod-1ll*mod/i*inv[mod%i]%mod;
	for(int i=n+1;i<=m;i++) p[i]=1ll*p[i-1]*i%mod*inv[i-n]%mod;
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) f[i][j]=p[i*j+n-1];
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++){
		g[i][j]=0;
		for(int k=1;k<=j;k++) g[i][j]=(g[i][j]+(((j-k)&1)?-1ll:1ll)*f[i][k]*C[j][k])%mod;
	}
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++){
		f[i][j]=0;
		for(int k=1;k<=i;k++) f[i][j]=(f[i][j]+(((i-k)&1)?-1ll:1ll)*g[k][j]*C[i][k])%mod;
	}
	for(int i=0;i<n;i++) for(int j=0;j<n;j++){
		g[i][j]=0;
		for(int k=j;k<n;k++) g[i][j]=(g[i][j]+(((k-j)&1)?-1ll:1ll)*f[n-i][n-k]*C[k][j])%mod;
	}
	for(int i=0;i<n;i++) for(int j=0;j<n;j++){
		f[i][j]=0;
		for(int k=i;k<n;k++) f[i][j]=(f[i][j]+(((k-i)&1)?-1ll:1ll)*g[k][j]*C[k][i])%mod;
	}
	for(int i=0;i<n;i++) for(int j=0;j<n;j++) cout<<(f[i][j]+mod)%mod<<" \n"[j==n-1];
	return 0;
}