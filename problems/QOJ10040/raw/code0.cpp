#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
ll a[100005],b[100005];
vector<pair<int,ll> >e[100005];
ll de[100005];
int dfn[100005],st[20][100005],num;
int getmi(int u,int v){return dfn[u]<dfn[v]?u:v;}
void init(int u,int fa){
	st[0][dfn[u]=++num]=fa;
	for(auto [v,w]:e[u]) if(v!=fa) de[v]=de[u]+w,init(v,u);
	if(u==1) for(int j=1;j<20;j++) for(int i=1;i+(1<<j)-1<=n;i++) st[j][i]=getmi(st[j-1][i],st[j-1][i+(1<<(j-1))]);
}
int LCA(int u,int v){
	if(u==v) return u;
	if((u=dfn[u])>(v=dfn[v])) swap(u,v);
	int t=__lg(v-u++);
	return getmi(st[t][u],st[t][v-(1<<t)+1]);
}
ll dis(int u,int v){return de[u]+de[v]-de[LCA(u,v)]*2;}
int vis[100005];
vector<int>ee[100005];
int mi,rt,sz[100005];
void dfs1(int u,int fa,int SZ){
	sz[u]=1;
	int ma=0;
	for(auto [v,w]:e[u]) if(v!=fa&&!vis[v]) dfs1(v,u,SZ),sz[u]+=sz[v],ma=max(ma,sz[v]);
	ma=max(ma,SZ-sz[u]);
	if(ma<mi) mi=ma,rt=u;
}
int fat[100005];
int dfs(int u,int SZ,int fa){
	mi=1e9,dfs1(u,0,SZ),u=rt,vis[u]=1,dfs1(u,0,SZ),fat[u]=fa;
	for(auto [v,w]:e[u]) if(!vis[v]) ee[u].emplace_back(dfs(v,sz[v],u));
	return u;
}
int id[100005];
struct node{
	vector<pair<ll,ll> >p;
	map<ll,ll>mp;
	ll F(int id,ll x){
		return p[id].first*x+p[id].second;
	}
	void insert(ll K,ll B){
		p.emplace_back(K,B);
		int now=p.size()-1;
		while(mp.size()){
			auto [x,id]=*prev(mp.end());
			if(F(id,x)>=F(now,x)){mp.erase(prev(mp.end()));continue;}
			if(p[id].first!=p[now].first){
				ll X=(p[now].second-p[id].second-1)/(p[id].first-p[now].first)+1;
				if(X<=1e12) mp[X]=now;
			}
			break;
		}
		if(!mp.size()) mp[0]=now;
	}
	ll get(ll x){
		if(!mp.size()) return 2e18;
		auto it=mp.upper_bound(x);
		it--;
		return F((*it).second,x);
	}
}p[100005];
ll res[100005],ans[100005];
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	for(int i=1,u,v,w;i<n;i++) cin>>u>>v>>w,e[u].emplace_back(v,w),e[v].emplace_back(u,w);
	init(1,0),dfs(1,n,0);
	for(int i=1;i<=n;i++) id[i]=i;
	sort(id+1,id+n+1,[&](int u,int v){return b[u]>b[v];});
	for(int i=1;i<=n;i++){
		int u=id[i],t=u;
		if(b[u]>=b[1]&&u!=1) continue;
		ll mi=2e18;
		if(u==1) mi=0;
		else{
			while(t){
				mi=min(mi,p[t].get(dis(t,u)));
				t=fat[t];
			}
		}
		res[i]=mi;
		t=u;
		while(t){
			p[t].insert(b[u],mi+a[u]+b[u]*dis(t,u));
			t=fat[t];
		}
	}
	for(int i=2;i<=n;i++){
		int t=i;
		ll mi=2e18;
		while(t){
			mi=min(mi,p[t].get(dis(t,i)));
			t=fat[t];
		}
		cout<<mi<<" \n"[i==n];
	}
	return 0;
}
