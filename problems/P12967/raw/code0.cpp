#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
ull ha[500005],li[500005];
int n,m;
vector<int>e[500005];
ull H(ull x){return x*x*x*998244353+1000000007;}
ull F(ull x){return H(x&((1ull<<31)-1))+H(x>>31);}
int sz[500005];
ull szz[500005];
void dfs(int u,int fa){
	ha[u]=1,sz[u]=1;
	for(auto v:e[u]) if(v!=fa) dfs(v,u),ha[u]+=F(ha[v]),sz[u]+=sz[v],szz[u]+=szz[v];
	szz[u]+=sz[u];
}
int cnt[500005],res[500005],sum[500005],tot,vis[500005],tim,fl;
void dfs3(int u,int fa,int de){
	if(fl) return;
	if(vis[ha[u]]!=tim) vis[ha[u]]=tim,sum[ha[u]]=0;
	sum[ha[u]]+=de;
	if(sum[ha[u]]>cnt[ha[u]]){fl=1;return;}
	for(auto v:e[u]) if(v!=fa) dfs3(v,u,de+1);
}
void dfs2(int u,int fa){
	if(res[ha[u]]!=-1) return;
	int flag=0;
	for(auto v:e[u]) if(v!=fa){
		dfs2(v,u);
	}
	if(!flag&&n-szz[u]==m){
		tim++,fl=0;
		dfs3(u,fa,1);
		if(!fl) res[ha[u]]=1;
	}
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1,u,v;i<n;i++) cin>>u>>v,e[u].emplace_back(v),e[v].emplace_back(u);
	dfs(1,0);
	for(int i=1;i<=n;i++) li[i]=ha[i];
	sort(li+1,li+n+1);tot=unique(li+1,li+n+1)-li-1;
	for(int i=1;i<=n;i++) ha[i]=lower_bound(li+1,li+tot+1,ha[i])-li,cnt[ha[i]]++;
	for(int i=1;i<=tot;i++) res[i]=-1;
	dfs2(1,0);
	int ans=0;
	for(int i=1;i<=tot;i++) ans+=(res[i]==1);
	cout<<ans<<"\n";
	return 0;
}
