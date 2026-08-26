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
int n;
int a[1000005];
vector<pair<int,int> >pre[1000005],suf[1000005];
void solve(int Ca){
	cin>>n;
	for(int i=0;i<n;i++) cin>>a[i],a[i+n]=a[i];
	for(int i=0;i<n+n;i++){
		pre[i].clear();
		pre[i].emplace_back(i,a[i]);
		if(i>=1){
			for(auto [pos,val]:pre[i-1]) if(a[i]+val/2!=pre[i].back().second) pre[i].emplace_back(pos,a[i]+val/2);
		}
	}
	for(int i=n+n-1;i>=0;i--){
		suf[i].clear();
		suf[i].emplace_back(i,a[i]);
		if(i<n+n-1){
			for(auto [pos,val]:suf[i+1]) if(a[i]+val/2!=suf[i].back().second) suf[i].emplace_back(pos,a[i]+val/2);
		}
	}
	for(int i=0;i<n;i++){
		ll ans=a[i];
		for(int j=0,k=pre[i+n].size()-1;j<suf[i].size();j++){
			while(k>=0&&suf[i][j].first>=pre[i+n][k].first) k--;
			if(k<0) break;
			ans=max(ans,1ll*suf[i][j].second-a[i]+pre[i+n][k].second);
		}
		cout<<ans<<" \n"[i==n-1];
	}
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