#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=998244353;
int n,x,y;
bitset<100005>dp[2][2];
set<ll>st;
void solve(){
	cin>>n>>x>>y;
	int now=0;
	dp[0][0].reset(),dp[0][1].reset(),dp[0][0][0]=1;
	for(int i=1;i<=n;i++){
		char g;cin>>g;
		dp[now^1][0].reset(),dp[now^1][1].reset();
		if(g!='1') dp[now^1][0]|=dp[now][0],dp[now^1][1]|=dp[now][1]<<1;
		if(g!='0') dp[now^1][0]|=dp[now][1],dp[now^1][1]|=dp[now][0]<<1;
		now^=1;
	}
	st.clear();
	for(int i=0;i<=n;i++) if(dp[now][0][i]||dp[now][1][i]){
		int t=n-2*i;t=abs(t+(t<0));
		st.insert(1ll*i*y+1ll*t*(t+1)/2*x);
	}
	ll res=0;
	for(auto x:st) res=(res+x)%mod;
	cout<<res<<"\n";
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}