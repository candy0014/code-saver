#include <bits/stdc++.h>
using namespace std;
int n,m;
vector<int>e[200005];
vector<pair<int,int> >g;
int vis[200005],fat[200005],de[200005];
void dfs(int u,int fa){
	vis[u]=1,fat[u]=fa,de[u]=de[fa]+1;
	for(auto v:e[u]){
		if(!vis[v]) dfs(v,u);
		else if(v!=fa&&u<v) g.emplace_back(u,v);
	}
}
int LCA(int u,int v){
	if(de[u]<de[v]) swap(u,v);
	while(de[u]>de[v]) u=fat[u];
	while(u!=v) u=fat[u],v=fat[v];
	return u;
}
vector<int>res[3];
void add(int u,int v,int id){
	if(u==v) return;
	int op=0;
	if(de[u]<de[v]) swap(u,v),op=1;
	vector<int>tmp;
	while(u!=v) tmp.emplace_back(u),u=fat[u];
	if(op) reverse(tmp.begin(),tmp.end()),tmp.pop_back(),res[id].emplace_back(v);
	for(auto x:tmp) res[id].emplace_back(x);
}
void print(int x,int y){
	int a=g[x].first,b=g[x].second;
	int c=g[y].first,d=g[y].second;
	if(de[a]>de[b]) swap(a,b);
	if(de[c]>de[d]) swap(c,d);
	int s=(de[a]>de[c])?a:c,t=LCA(b,d);
	add(s,t,0);
	add(s,a,1),res[1].emplace_back(a),add(b,t,1);
	add(s,c,2),res[2].emplace_back(c),add(d,t,2);
	cout<<"YES\n";
	for(int i=0;i<3;i++){
		cout<<res[i].size()+1<<" ";
		for(auto x:res[i]) cout<<x<<" ";
		cout<<t<<"\n";
	}
}
int id[200005];
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1,u,v;i<=m;i++) cin>>u>>v,e[u].emplace_back(v),e[v].emplace_back(u);
	for(int i=1;i<=n;i++) if(!vis[i]) dfs(i,0);
	memset(id,-1,sizeof(id));
	for(int i=0;i<(int)g.size();i++){
		int u=g[i].first,v=g[i].second;
		if(de[u]<de[v]) swap(u,v);
		while(u!=v){
			if(id[u]==-1) id[u]=i;
			else{print(id[u],i);return 0;}
			u=fat[u];
		}
	}
	cout<<"NO\n";
	return 0;
}