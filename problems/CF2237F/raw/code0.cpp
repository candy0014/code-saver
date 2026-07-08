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
int n,m,a[500005],dp[1000005];
void solve(int Ca){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	int tmp=n;
	for(int i=1;i<=m;i++) dp[tmp+i]=-1e9;
	dp[tmp+1]=(a[1]==1);
	int ma=dp[tmp+1],maxx=-1e9;
	for(int i=2;i<=n;i++){
		tmp--;
		dp[tmp+1]=ma;
		dp[tmp+a[i]]=max(dp[tmp+a[i]],maxx)+1;
		dp[tmp+m]=max(dp[tmp+m],maxx);
		ma=max({ma,dp[tmp+a[i]],dp[tmp+m]}),maxx=max(maxx,dp[tmp+m]);
	}
	cout<<n-dp[tmp+m]<<"\n";
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
	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}