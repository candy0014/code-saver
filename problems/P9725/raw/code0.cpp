#include <bits/stdc++.h>
using namespace std;
int n;
vector<int>e[100005];
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++) e[i].clear();
	for(int i=1,u,v;i<n;i++) cin>>u>>v,e[u].emplace_back(v),e[v].emplace_back(u);
	for(int i=1;i<=n;i++) if(e[i].size()==n-1){cout<<"-1\n";return;}
	int al=0,ma=0;
	for(int i=1;i<=n;i++){
		int cnt=0;
		for(auto v:e[i]) cnt+=e[v].size()==1;
		ma=max(ma,cnt),al+=cnt;
	}
	cout<<max(ma,(al+1)/2)<<"\n";
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}