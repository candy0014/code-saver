#include <bits/stdc++.h>
using namespace std;
int n,m,k;
vector<pair<int,int> >p[1005],q[1005];
int s[1005][1005],vis[1005][1005];
array<int,3>pre[1005][1005];
string str;
vector<array<int,3> >res;
vector<pair<int,int> >g;
void dfs(int u,int v){
	g.emplace_back(u,v);
	for(auto [x,id]:p[u]){
		if(v+x<=m&&!vis[u][v+x]) vis[u][v+x]=1,pre[u][v+x]={id,u,v},dfs(u,v+x);
		if(v-x>=0&&!vis[u][v-x]) vis[u][v-x]=1,pre[u][v-x]={id,u,v},dfs(u,v-x);
	}
	for(auto [x,id]:q[v]){
		if(u+x<=n&&!vis[u+x][v]) vis[u+x][v]=1,pre[u+x][v]={id,u,v},dfs(u+x,v);
		if(u-x>=0&&!vis[u-x][v]) vis[u-x][v]=1,pre[u-x][v]={id,u,v},dfs(u-x,v);
	}
}
void solve(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++) p[i].clear();
	for(int i=1;i<=m;i++) q[i].clear();
	for(int i=0;i<=n+1;i++) for(int j=0;j<=m+1;j++) vis[i][j]=s[i][j]=0;
	for(int i=1;i<=n;i++){
		cin>>str;
		for(int j=0;j<m;j++) s[i][j+1]=str[j]-'0';
	}
	for(int i=0;i<=n;i++) for(int j=0;j<=m;j++) s[i][j]^=s[i][j+1]^s[i+1][j]^s[i+1][j+1];
	for(int i=1,u,v;i<=k;i++) cin>>u>>v,p[u].emplace_back(v,i),q[v].emplace_back(u,i);
	res.clear();
	g.clear();
	for(int i=0;i<=n;i++) for(int j=0;j<=m;j++) if(!vis[i][j]) dfs(i,j);
	for(int i=g.size()-1;i>=0;i--){
		int x=g[i].first,y=g[i].second;
		if(!x||!y||!s[x][y]) continue;
		if(!s[x][y]) continue;
		int id=pre[x][y][0],xx=pre[x][y][1],yy=pre[x][y][2];
		s[x][y]^=1,s[xx][yy]^=1;
		if(x==xx) res.push_back({id,1,min(y,yy)+1});
		else res.push_back({id,min(x,xx)+1,1});
	}
	cout<<res.size()<<"\n";
	for(auto x:res){
		for(int i=0;i<3;i++) cout<<x[i]<<" ";
		cout<<"\n";
	}
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}