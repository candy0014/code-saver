#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,mod,C[5005][5005],pw[25000005],res[5005];
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>mod,pw[0]=1;
	for(int i=1;i<=n*n;i++) pw[i]=pw[i-1]*2%mod;
	for(int i=0;i<=n;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	}
	res[2]=1;
	for(int i=3;i<=n;i++){
		res[i]=pw[i*(i-1)/2-1];
		for(int j=2;j<i;j++) res[i]=(res[i]-1ll*C[i-2][j-2]*res[j]%mod*pw[(i-j)*(i-j-1)/2+(i-j)]%mod+mod)%mod;
	}
	cout<<res[n]<<"\n";
	return 0;
}