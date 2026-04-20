#include <bits/stdc++.h>
using namespace std;
int n,m;
vector<int>e[300005];
double dis[300005];
int vis[300005];
priority_queue<pair<double,int> >q;
int du[300005];
double sum[300005];
double calc(int d,int du,double sum){return 1.0*d/du+sum/du;}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1,u,v;i<=m;i++) cin>>u>>v,e[u].emplace_back(v),e[v].emplace_back(u);
	for(int i=1;i<n;i++) dis[i]=1e18;
	q.push(make_pair(0,n));
	while(!q.empty()){
		int u=q.top().second;q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(auto v:e[u]){
			du[v]++,sum[v]+=dis[u];
			double tmp=calc(e[v].size(),du[v],sum[v]);
			if(tmp<dis[v]) dis[v]=tmp,q.push(make_pair(-dis[v],v));
		}
	}
	cout<<fixed<<setprecision(10)<<dis[1]<<"\n";
	return 0;
}