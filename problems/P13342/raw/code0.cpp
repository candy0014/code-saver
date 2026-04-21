#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m,tot,ca;
struct node{int u,v,w;}ee[200005];
int son[200005][2];
ll al,val[200005],res[500005];
int dfn[200005],num;
int fa[200005],sz[200005];
int Find(int u){return fa[u]==u?u:(fa[u]=Find(fa[u]));}
set<int>st;
int rt;
vector<pair<int,int> >ch[200005],as[200005];
void dfs2(int u){
	if(u<=n){
		auto it=st.lower_bound(u);
		if(it!=st.end()) ch[u].emplace_back(*it,rt);//,cout<<u<<" "<<(*it)<<" "<<rt<<"!\n";
		if(it!=st.begin()) it--,ch[*it].emplace_back(u,rt);//,cout<<(*it)<<" "<<u<<" "<<rt<<"!\n";
		return;
	}
	dfs2(son[u][0]),dfs2(son[u][1]);
}
void dfs3(int u){
	if(u<=n){
		st.insert(u);
		return;
	}
	dfs3(son[u][0]),dfs3(son[u][1]);
}
void dfs(int u){
	if(u<=n){
		st.insert(u);
		return;
	}
	dfs(son[u][0]);
	st.clear();
	dfs(son[u][1]);
	rt=u,dfs2(son[u][0]);
	dfs3(son[u][0]);
}
struct TREE{
    ll sum[200005];
    void add(int x,ll k){while(x<=n)sum[x]+=k,x+=(x&(-x));}
    ll query(int x){ll t=0;while(x)t+=sum[x],x-=(x&(-x));return t;}
}tr;
int la[200005];
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>ca,tot=n;
	for(int i=1;i<=m;i++) cin>>ee[i].u>>ee[i].v>>ee[i].w,ee[i].u++,ee[i].v++;
	sort(ee+1,ee+m+1,[&](node u,node v){return u.w<v.w;});
	for(int i=1;i<=n*2;i++) fa[i]=i,sz[i]=(i<=n);
	for(int i=1;i<=m;i++){
		int u=Find(ee[i].u),v=Find(ee[i].v);
		if(u!=v){
			if(sz[u]>sz[v]) swap(u,v);
			++tot,son[tot][0]=u,son[tot][1]=v;
			val[tot]=ee[i].w,al+=ee[i].w;
			fa[u]=fa[v]=tot,sz[tot]=sz[u]+sz[v];
		}
	}
	// cout<<al<<"\n";
	// for(int i=n+1;i<=tot;i++) cout<<son[i][0]<<" "<<son[i][1]<<" "<<val[i]<<"\n";
	dfs(tot);
	for(int i=1,l,r;i<=ca;i++) cin>>l>>r,l++,r++,as[l].emplace_back(r,i);
	for(int i=1;i<=tot;i++) la[i]=n+1;
	for(int i=n;i>=1;i--){
		for(auto x:ch[i]){
			if(x.first<la[x.second]) tr.add(x.first,val[x.second]),tr.add(la[x.second],-val[x.second]),la[x.second]=x.first;
		}
		for(auto x:as[i]){
			res[x.second]=tr.query(x.first);
		}
	}
	for(int i=1;i<=ca;i++) cout<<al-res[i]<<"\n";
	return 0;
}