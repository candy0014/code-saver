#include <bits/stdc++.h>
using namespace std;
const int lim=300;
int n,m,ca,co[100005],cnt[100005],tag[100005],vis[100005],cc[100005];
vector<int>e[100005],p;
int de[100005][350],dfn[100005],num,mi[100005][20],fat[100005];
int getmi(int u,int v){return dfn[u]<dfn[v]?u:v;}
void dfs(int u,int fa){
	for(int i=0;i<=m;i++) de[u][i]=de[fa][i];
	de[u][0]++;
	if(tag[co[u]]) de[u][tag[co[u]]]++;
	mi[dfn[u]=++num][0]=fat[u]=fa;
	for(int v:e[u]) if(v!=fa) dfs(v,u);
	if(u==1) for(int j=1;j<20;j++) for(int i=1;i+(1<<j)-1<=n;i++) mi[i][j]=getmi(mi[i][j-1],mi[i+(1<<(j-1))][j-1]);
}
int LCA(int u,int v){
	if(u==v) return u;
	if((u=dfn[u])>(v=dfn[v])) swap(u,v);
	int t=__lg(v-u++);
	return getmi(mi[u][t],mi[v-(1<<t)+1][t]);
}
vector<int>res;
void insert(int c,int t){
	if(vis[c]!=ca) vis[c]=ca,cc[c]=0;
	cc[c]++;
	if(cc[c]==t) res.emplace_back(c);
}
void solve(){
	cin>>n>>ca,p.clear(),num=0;
	for(int i=1;i<=n;i++) e[i].clear(),cnt[i]=tag[i]=0,vis[i]=-2;
	for(int i=1;i<=n;i++) cin>>co[i],cnt[co[i]]++;
	for(int i=1,u,v;i<n;i++) cin>>u>>v,e[u].emplace_back(v),e[v].emplace_back(u);
	for(int i=1;i<=n;i++) if(cnt[i]>=lim) p.emplace_back(i),tag[i]=p.size();
	m=p.size(),dfs(1,0);
	while(ca--){
		int u,v,k;cin>>u>>v>>k;
		int lca=LCA(u,v),_lca=fat[lca],len=de[u][0]+de[v][0]-de[lca][0]-de[_lca][0],c=len/k+1;
		if(c>=lim){
			int flag=0;
			for(int i=1;i<=m;i++) if(de[u][i]+de[v][i]-de[lca][i]-de[_lca][i]>=c) cout<<p[i-1]<<" ",flag=1;
			if(!flag) cout<<"-1";
			cout<<"\n";
		}
		else{
			res.clear();
			if(de[u][0]<de[v][0]) swap(u,v);
			while(de[u][0]>de[v][0]) insert(co[u],c),u=fat[u];
			while(u!=v) insert(co[u],c),insert(co[v],c),u=fat[u],v=fat[v];
			insert(co[u],c);
			sort(res.begin(),res.end());
			if(!res.size()) cout<<"-1\n";
			else{
				for(auto x:res) cout<<x<<" ";
				cout<<"\n";
			}
		}
	}
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}