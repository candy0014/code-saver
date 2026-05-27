#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int V=1e6+1;
int n,m;
struct EDGE{int u,v,w;};
vector<EDGE>e,p0,p1;
int res[2000005],fa[100005],sz[100005],st[200005],tot;
int Find(int u){return fa[u]==u?u:Find(fa[u]);}
bool merge(int u,int v){
	u=Find(u),v=Find(v);
	if(u==v) return 0;
	if(sz[u]>sz[v]) swap(u,v);
	st[++tot]=u,fa[u]=v,sz[v]+=sz[u];
	return 1;
}
void apart(){
	int u=st[tot--],v=fa[u];
	sz[v]-=sz[u],fa[u]=u;
}
int calc(int x,vector<EDGE>&p0,vector<EDGE>&p1,vector<EDGE>&p00,vector<EDGE>&p01,vector<EDGE>&p10,vector<EDGE>&p11){
	int i=0,j=0,cnt=0;
	while(i<(int)p0.size()||j<(int)p1.size()){
		EDGE e;
		int op;
		if(j==p1.size()||((i<p0.size()&&p0[i].w<=p1[j].w-x))) e=p0[i],op=0,i++;
		else e=p1[j],op=1,j++;
		if(merge(e.u,e.v)) cnt+=op,(op==0?p01:p11).emplace_back(e);
		else (op==0?p00:p10).emplace_back(e);
	}
	return cnt;
}
vector<int>g;
void solve(int l,int r,int now,vector<EDGE>&p0,vector<EDGE>&p1){
	if(l>r) return;
	if(!p0.size()&&!p1.size()) return;
	int mid=(l+r)/2,tmp=tot;
	vector<EDGE>p00,p01,p10,p11;
	res[mid+V]=calc(mid,p0,p1,p00,p01,p10,p11)+now;
	g.emplace_back(mid);
	while(tot>tmp) apart();
	for(auto x:p01) merge(x.u,x.v);
	solve(l,mid-1,now,p00,p11);
	while(tot>tmp) apart();
	for(auto x:p11) merge(x.u,x.v);
	solve(mid+1,r,now+p11.size(),p01,p10);
}
ll ans[2000005];
mt19937 rd(time(0));
void solve(){
	cin>>n>>m,tot=0;
	for(int i=1;i<=n;i++) fa[i]=i,sz[i]=1;
	p0.clear(),p1.clear(),e.clear();
	for(int i=1,u,v,w;i<=m;i++){
		char g;cin>>u>>v>>w>>g;
		e.emplace_back(EDGE{u,v,w-(g!='R')*V});
		(g=='R'?p1:p0).emplace_back(EDGE{u,v,w});
	}
	sort(p0.begin(),p0.end(),[&](EDGE u,EDGE v){return u.w<v.w;});
	sort(p1.begin(),p1.end(),[&](EDGE u,EDGE v){return u.w<v.w;});
	sort(e.begin(),e.end(),[&](EDGE u,EDGE v){return u.w<v.w;});
	ll sum=0;
	for(int i=0;i<(int)e.size();i++) if(merge(e[i].u,e[i].v)) sum+=e[i].w+(e[i].w<=0)*V;
	for(int i=1;i<=n;i++) fa[i]=i,sz[i]=1;
	g.clear(),solve(-V,V,0,p0,p1);
	for(int i=0;i<n;i++) ans[i]=-1;
	sort(g.begin(),g.end());
	ans[res[g[0]+V]]=sum;
	for(int i=1;i<(int)g.size();i++){
		for(int j=res[g[i-1]+V]+1;j<=res[g[i]+V];j++) ans[j]=ans[j-1]+g[i]-1;
	}
	for(int i=0;i<n;i++) cout<<ans[i]<<" \n"[i==n-1];
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}