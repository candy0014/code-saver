#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,head[200005],tot=1,tag[600005];
struct EDGE{int nex,to;ll w;}e[600005];
void add(int u,int v,ll w){e[++tot].nex=head[u],e[tot].to=v,e[tot].w=w,head[u]=tot;}
int build(vector<pair<int,ll> >&p,int l,int r,int rt){
	if(l==r) return p[l].first;
	int mid=(l+r)>>1,u;
	if(rt>0) u=rt;
	else u=++n;
	int ls=build(p,l,mid,-1),rs=build(p,mid+1,r,-1);
	if(l==mid) add(u,ls,p[l].second),add(ls,u,p[l].second);
	else add(u,ls,0),add(ls,u,0);
	if(r==mid+1) add(u,rs,p[r].second),add(rs,u,p[r].second);
	else add(u,rs,0),add(rs,u,0);
	return u;
}
void dfs1(int u,int fa){
	vector<pair<int,ll> >son;
	for(int i=head[u];i;i=e[i].nex){
		int v=e[i].to;
		ll w=e[i].w;
		if(v==fa) continue;
		dfs1(v,u),son.emplace_back(v,w);
	}
	if(son.size()>=3){
		for(int i=head[u];i;i=e[i].nex) if(e[i].to!=fa) tag[i]=tag[i^1]=-1;
		build(son,0,(int)son.size()-1,u);
	}
}
vector<int>p;
vector<ll>di;
int ca;
pair<int,int> ask[500005];
ll res[500005];
int sz[200005];
int mi,mik;
void dfs3(int u,int fa,int fae,int SZ){
	sz[u]=1;
	for(int i=head[u];i;i=e[i].nex) if(tag[i]==0){
		int v=e[i].to;
		if(v==fa) continue;
		dfs3(v,u,i,SZ),sz[u]+=sz[v];
	}
	int tmp=max(sz[u],SZ-sz[u]);
	if(tmp<mi) mi=tmp,mik=fae;
}
int vis[200005],tim;
void dfs4(int u,int fa){
	sz[u]=1,vis[u]=tim;
	for(int i=head[u];i;i=e[i].nex) if(tag[i]==0){
		int v=e[i].to;
		if(v==fa) continue;
		dfs4(v,u),sz[u]+=sz[v];
	}
}
vector<int>as[600005];
vector<int>ord;
int id[200005];
int sn[800005][2];
int dfs2(int u,int SZ,vector<int>ass){
	if(SZ==1) return u+tot;
	mi=1e9,dfs3(u,0,0,SZ);
	int rt=mik;
	tag[rt]=tag[rt^1]=1;
	tim++,dfs4(e[rt].to,0);
	vector<int>ls,rs;
	as[rt]=ass;
	for(auto x:ass){
		int u=ask[x].first,v=ask[x].second;
		if(vis[u]==tim&&vis[v]==tim) ls.emplace_back(x);
		else if(vis[u]!=tim&&vis[v]!=tim) rs.emplace_back(x);
	}
	int _sz=sz[e[rt].to];
	sn[rt][0]=dfs2(e[rt].to,_sz,ls),sn[rt][1]=dfs2(e[rt^1].to,SZ-_sz,rs);
	ord.emplace_back(rt);
	return rt;
}
vector<pair<int,ll> >ee[200005];
set<int>le[800005];
ll dis[200005];
priority_queue<pair<ll,int> >q;
vector<int>gg;
void dij(int rt){
	for(auto u:gg) dis[u]=1e18;gg.clear();
	tim++,q.push(make_pair(0,rt)),dis[rt]=0;
	while(!q.empty()){
		int u=q.top().second;q.pop();
		if(vis[u]==tim) continue;
		vis[u]=tim,gg.emplace_back(u);
		for(auto [v,w]:ee[u]){
			if(dis[v]>dis[u]+w) dis[v]=dis[u]+w,q.push(make_pair(-dis[v],v));
		}
	}
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) id[i]=-1;
	for(ll i=2,u,w;i<=n;i++) cin>>u>>w,add(u,i,w),add(i,u,w);
	for(int i=2;i<=n;i++) if(!e[head[i]].nex) id[i]=p.size(),p.emplace_back(i);
	di.resize(p.size());
	for(int i=0;i<(int)p.size();i++) cin>>di[i];
	dfs1(1,0);
	for(int i=1;i<=n;i++) dis[i]=1e18;
	for(auto x:p) le[x+tot].insert(id[x]);
	cin>>ca;
	vector<int>ar;
	for(int i=1;i<=ca;i++) cin>>ask[i].first>>ask[i].second,ar.emplace_back(i),res[i]=1e18;
	dfs2(1,n,ar);
	for(auto x:ord){
		ee[e[x].to].emplace_back(e[x^1].to,e[x].w);
		ee[e[x^1].to].emplace_back(e[x].to,e[x].w);
		// cout<<e[x].to<<" "<<e[x^1].to<<" "<<e[x].w<<"\n";
		int ls=sn[x][0],rs=sn[x][1];
		swap(le[x],le[ls]);
		vector<int>g;g.emplace_back(e[x].to);
		for(auto y:le[rs]){
			int z=(y+1)%p.size(),flag=0;
			if(le[x].find(z)!=le[x].end()){
				ee[p[y]].emplace_back(p[z],di[y]);
				ee[p[z]].emplace_back(p[y],di[y]);
				// cout<<"? "<<p[y]<<" "<<p[z]<<" "<<di[y]<<"\n";
				flag=1;
			}
			z=(y-1+p.size())%p.size();
			if(le[x].find(z)!=le[x].end()){
				ee[p[y]].emplace_back(p[z],di[z]);
				ee[p[z]].emplace_back(p[y],di[z]);
				// cout<<"? "<<p[y]<<" "<<p[z]<<" "<<di[z]<<"\n";
				flag=1;
			}
			if(flag) g.emplace_back(p[y]);
		}
		for(auto y:le[rs]) le[x].insert(y);
		if(as[x].size()){
			// cout<<"!\n";
			for(auto y:g){
				dij(y);
				for(auto z:as[x]) res[z]=min(res[z],dis[ask[z].first]+dis[ask[z].second]);
			}
		}
		// cout<<"\n";
	}
	for(int i=1;i<=ca;i++) cout<<res[i]<<"\n";
	return 0;
}