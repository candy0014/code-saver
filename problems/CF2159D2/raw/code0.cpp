#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
ll a[400005];
int dp[125][400005];
int st[400005],top;
ll val[400005];
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	top=0;
	for(int j=0;j<=120;j++) dp[j][0]=1;
	ll res=0;
	for(int i=1;i<=n;i++){
		while(top&&a[i]<=val[top]) top--;
		st[++top]=i,val[top]=a[i];
		dp[0][i]=i+1;
		for(int j=1;j<=120;j++) dp[j][i]=1e9;
		for(int j=1;j<=3;j++){
			int it=lower_bound(val+1,val+top+1,(a[i]+j-1)/j)-val-1;
			for(int k=j;k<=120;k++) dp[k][i]=min(dp[k][i],dp[k-j][st[it]]);
		}
		for(int k=1;k<=120;k++) res+=1ll*k*(dp[k-1][i]-dp[k][i]);
	}
	cout<<res<<"\n";
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}