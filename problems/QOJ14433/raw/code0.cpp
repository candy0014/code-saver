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
int n,m,k;
vector<int>s[405];
ll cnt[405];
void solve(int Ca){
	cin>>n>>m>>k;
	for(int i=1;i<=k;i++){
		for(int j=1,u;j<=n;j++) cin>>u,s[j].emplace_back(u);
	}
	for(int i=1;i<=n;i++){
		s[i].emplace_back(0);
		sort(s[i].begin(),s[i].end());
		for(int j=1;j<=k;j++) cnt[j-1]+=s[i][j]-s[i][j-1];
	}
	ll ans=0;
	for(int i=0;i<=k;i++){
		ll t=min(1ll*m,cnt[i]);
		ans+=t*i,m-=t;
	}
	cout<<ans<<"\n";
}
int main(){
	#ifdef ONLINE_JUDGE
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	#endif
	#ifndef ONLINE_JUDGE
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	#endif
	
	int Ca=1;
//	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}