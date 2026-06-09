#include <bits/stdc++.h>
using namespace std;
int k,n;
vector<pair<int,int> >e[2005];
int vis[4000005];
vector<int>ans;
vector<int>res[2005];
void dfs(int u){
	while(!e[u].empty()){
		pair<int,int>t=e[u].back();e[u].pop_back();
		if(vis[t.second]) continue;
		vis[t.second]=1;
		dfs(t.first);
	}
	ans.emplace_back(u);
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>k,n=k*2+1;
	int tot=0;
	for(int i=1;i<=n;i++) for(int j=i+1;j<=n;j++){
		tot++;
		e[i].emplace_back(j,tot);
		e[j].emplace_back(i,tot);
	}
	dfs(1);
	for(int i=0;i<(int)ans.size()-1;i++) res[ans[i]].emplace_back(ans[i+1]);
	cout<<n<<"\n";
	for(int i=1;i<=n;i++) for(int j=0;j<k;j++) cout<<res[i][j]<<" \n"[j==k-1];
	return 0;
}