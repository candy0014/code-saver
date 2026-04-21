#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m,fa[200005],cnt[400005],de[200005],sz[200005],son[200005];
vector<int>e[200005];
ll res;
void dfs(int u){
	de[u]=de[fa[u]]+1,sz[u]=1;
	for(auto v:e[u]){
		dfs(v),res+=1ll*sz[u]*sz[v]*de[u],sz[u]+=sz[v];
		if(sz[v]>sz[son[u]]) son[u]=v;
	}
}
ll cc;
void dfs2(int u){
	cc+=cnt[de[u]];
	for(auto v:e[u]) dfs2(v);
}
void dfs3(int u){
	cnt[de[u]]++;
	for(auto v:e[u]) dfs3(v);
}
void dfs1(int u){
	for(auto v:e[u]) if(v!=son[u]){
		dfs1(v);
		for(int i=de[v];i<=de[v]+sz[v];i++) cnt[i]=0;
	}
	if(son[u]){
		dfs1(son[u]);
		cc=0;
		for(auto v:e[u]) if(v!=son[u]){
			dfs2(v),dfs3(v);
		}
		res+=1ll*cc*de[u];
	}
	cnt[de[u]]++;
}
void solve(){
	cin>>n>>m,res=0;
	for(int i=1;i<=n;i++) e[i].clear(),cnt[i]=0,son[i]=0;
	for(int i=1;i<n;i++) fa[i]=i+1;
	fa[n]=0;
	for(int i=1,u,v;i<=m;i++) cin>>u>>v,fa[u]=max(fa[u],v);
	for(int i=1;i<n;i++) e[fa[i]].emplace_back(i);
	dfs(n),dfs1(n);
	res=-res;
	for(int i=n,sum=0;i>=1;i--) sum+=cnt[i],res+=1ll*cnt[i]*(sum-1)*i;
	cout<<res<<"\n";
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}