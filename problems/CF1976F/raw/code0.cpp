#include <bits/stdc++.h>
using namespace std;
int n;
vector<int>e[300005];
int res[300005],de[300005],mad[300005],son[300005];
void dfs(int u,int fa){
	de[u]=de[fa]+1,mad[u]=1,son[u]=0;
	for(auto v:e[u]) if(v!=fa){
		dfs(v,u),mad[u]=max(mad[u],mad[v]+1);
		if(mad[v]>mad[son[u]]) son[u]=v;
	}
}
vector<int>p;
void dfs2(int u,int fa,int top){
	int flag=0;
	if(son[u]) dfs2(son[u],u,top),flag=1;
	for(auto v:e[u]) if(v!=fa&&v!=son[u]) dfs2(v,u,v),flag=1;
	if(!flag) p.emplace_back(de[u]-de[top]+1);
}
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++) e[i].clear();
	for(int i=1,u,v;i<n;i++) cin>>u>>v,e[u].emplace_back(v),e[v].emplace_back(u);
	p.clear(),dfs(1,0),dfs2(1,0,1);
	sort(p.begin(),p.end(),[&](int u,int v){return u>v;});
	while(p.size()<n*2) p.emplace_back(0);
	for(int i=1,res=0;i<n;i++){
		res+=p[i*2-2];
		if(i!=1) res+=p[i*2-3];
		cout<<n-res<<" \n"[i==n-1];
	}
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}