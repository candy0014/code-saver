#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
const ll mod=1e9+7;
const ll inf=2e9;
const int N=2e5+5;
const int M=2e5+5;
const int V=2e6+5;
int n;
ll a[300005],dp[300005],sum[64][2];
void add(ll &u,ll v){u=(u+v)%mod;}
void solve(int Ca){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],a[i]^=a[i-1];
	dp[0]=1;
	for(int i=0;i<=62;i++) sum[i][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=62;j++) dp[i]=(dp[i]+(1ll<<j)%mod*sum[j][((a[i]>>j)&1)^1])%mod;
		for(int j=0;j<=62;j++) add(sum[j][(a[i]>>j)&1],dp[i]);
	}
	cout<<dp[n]<<"\n";
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