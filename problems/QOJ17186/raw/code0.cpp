#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,ca;
ll a[500005],dp[1000005],f[1000005],res[105],sum;
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>ca;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1,[&](int u,int v){return u>v;});
	for(int i=1;i<=n;i++) dp[i]=dp[i-1]+a[i],sum+=a[i];
	for(int i=n+1;i<=n+n;i++) dp[i]=dp[n];
	ll V=1;
	while(V<=n) V*=2;
	V=(V*2-n)/(2-1);
	for(int i=0;i<=100;i++){
		int c=V%2;
		res[i]=dp[0];
		for(int j=0;j<=2*n;j++) dp[j]=dp[min(2ll*n,1ll*j*2+c)];
		for(int j=2*n;j>=1;j--) dp[j]-=dp[j-1];
		int tot=0;
		for(int j=1,k=1;tot<=n*2;){
			if(k>n||(j<=2*n&&dp[j]>a[k])) f[++tot]=dp[j++];
			else f[++tot]=a[k++];
		}
		for(int j=1;j<=n*2;j++) dp[j]=dp[j-1]+f[j];
		V/=2;
		if(!V) V=1;
	}
	while(ca--){
		int d;cin>>d,d=min(d,100);
		cout<<sum*d-res[d]<<"\n";
	}
	return 0;
}