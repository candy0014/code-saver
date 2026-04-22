#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,dp[400005];
ll a[400005],b[400005],m;
void solve(){
	cin>>n,m=0;
	for(int i=1;i<=n;i++) cin>>a[i],dp[i]=1e9;
	for(ll i=n,mi=2e18;i>=1;i--) if(a[i]<mi) mi=a[i],b[++m]=a[i];
	reverse(b+1,b+m+1);
	for(int i=1,pos2=0,pos3=0;i<=m;i++){
		while(pos2<m&&b[pos2+1]<=b[i]*2) pos2++;
		while(pos3<m&&b[pos3+1]<=b[i]*3) pos3++;
		dp[i]=min(dp[i],dp[i-1]+1),dp[pos2]=min(dp[pos2],dp[i-1]+2),dp[pos3]=min(dp[pos3],dp[i-1]+3);
	}
	cout<<dp[m]<<"\n";
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}