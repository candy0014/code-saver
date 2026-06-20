#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,s,cnt[200005];
vector<pair<int,int> >dp[400005];
void merge(int x,int y,int k){
	x+=n,y+=n;
	for(auto [l,r]:dp[y]) dp[x].emplace_back(l+k,r+k);
	sort(dp[x].begin(),dp[x].end());
	if(!dp[x].size()) return;
	pair<int,int> la=dp[x][0];
	vector<pair<int,int> >res;
	for(int i=1;i<(int)dp[x].size();i++){
		if(dp[x][i].first>la.second) res.emplace_back(la),la=dp[x][i];
		else la.second=max(la.second,dp[x][i].second);
	}
	res.emplace_back(la),dp[x].swap(res);
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>s;
	for(int i=1,u;i<=n;i++) cin>>u,cnt[u]++;
	dp[n].emplace_back(0,cnt[1]);
	for(int i=0;i<=s;i++) if(i!=1){
		int x=cnt[i];
		for(int j=1;x>0;x-=j,j<<=1){
			int t=min(j,x);
			if(i) for(int k=s-t*(i-1);k>=-n;k--) merge(k+t*(i-1),k,t);
			else for(int k=-n+t;k<=s;k++) merge(k-t,k,t);
		}
	}
	ll res=0;
	for(int i=-n;i<=s;i++) for(auto [l,r]:dp[i+n]) res+=r-l+1;
	cout<<res<<"\n";
	return 0;
}