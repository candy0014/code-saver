#include <bits/stdc++.h>
using namespace std;
typedef unsigned int uint;
int n,fat[300005];
vector<int>e[300005];
int de[300005],sz[300005],son[300005],dfn[300005],num,top[300005],bot[300005],_dfn[300005];
void dfs1(int u){
	de[u]=de[fat[u]]+1,sz[u]=1;
	for(auto v:e[u]){
		dfs1(v);
		sz[u]+=sz[v];
		if(sz[v]>sz[son[u]]) son[u]=v;
	}
}
void dfs2(int u,int la){
	dfn[u]=++num,top[u]=la,bot[la]=u,_dfn[num]=u;
	if(son[u]) dfs2(son[u],la);
	for(auto v:e[u]) if(v!=son[u]) dfs2(v,v);
}
int cnt[300005][22],bi[300005],val[300005];
int ans;
int get(int u){
	int x=(1<<22)-1-bi[u];
	return __lg(x&(-x));
}
int get2(int u){
	int x=(1<<22)-1-bi[u];
	x&=x-1;
	return __lg(x&(-x));
}
int rt[300005],tot;
struct node{
	int x,vx,sx,vy,sy;
}s[1200005];
struct TREE{
	int ls[1200005],rs[1200005];
	node merge(node ls,node rs){
		node res;
		res.x=rs.x;
		if(rs.vx==ls.x) res.vx=ls.vx,res.sx=rs.sx+ls.sx;
		else res.vx=ls.vy,res.sx=rs.sx+ls.sy;
		if(rs.vy==ls.x) res.vy=ls.vx,res.sy=rs.sy+ls.sx;
		else res.vy=ls.vy,res.sy=rs.sy+ls.sy;
		return res;
	}
	void pushup(int p){
		s[p]=merge(s[ls[p]],s[rs[p]]);
	}
	void build(int p,int l,int r){
		if(l==r){
			s[p].x=s[p].vx=s[p].vy=21;
			return;
		}
		ls[p]=++tot,rs[p]=++tot;
		int mid=(l+r)>>1;build(ls[p],l,mid),build(rs[p],mid+1,r),pushup(p);
	}
	void change(int p,int l,int r,int x){
		if(r<x||l>x) return;
		if(l==r){
			s[p].x=s[p].vy=s[p].sy=get(_dfn[l]),s[p].vx=s[p].sx=get2(_dfn[l]);
			return;
		}
		int mid=(l+r)>>1;change(ls[p],l,mid,x),change(rs[p],mid+1,r,x),pushup(p);
	}
	node query(int p,int l,int r,int L,int R){
		if(L>r) return node{21,21,0,21,0};
		if(L<=l&&r<=R) return s[p];
		int mid=(l+r)>>1;
		if(R<=mid) return query(ls[p],l,mid,L,R);
		if(L>mid) return query(rs[p],mid+1,r,L,R);
		return merge(query(ls[p],l,mid,L,R),query(rs[p],mid+1,r,L,R));
	}
}tr;
void update(int u,int v){
	if(u==1) return;
	cnt[fat[u]][val[u]]--;
	if(!cnt[fat[u]][val[u]]) bi[fat[u]]^=(1<<val[u]);
	val[u]=v;
	if(!cnt[fat[u]][v]) bi[fat[u]]^=(1<<v);
	cnt[fat[u]][v]++;
}
void solve(int u){
	int U=u;
	int la=0;
	if(u!=top[u]){
		node tmp=tr.query(rt[top[u]],dfn[top[u]],dfn[bot[u]],dfn[top[u]],dfn[u]-1);
		la=tmp.vy;
		if(tmp.x==0) ans-=tmp.sy,ans+=tmp.sx,la=tmp.vx;
	}
	else la=0;
	tr.change(rt[top[u]],dfn[top[u]],dfn[bot[u]],dfn[u]);
	update(top[u],la),u=fat[top[u]];
	while(u){
		int t=top[u];
		node tmp=tr.query(rt[top[u]],dfn[top[u]],dfn[bot[u]],dfn[u]+1,dfn[bot[u]]);
		node pre=tr.query(rt[top[u]],dfn[top[u]],dfn[bot[u]],dfn[top[u]],dfn[u]);
		if(tmp.vy==pre.x) ans-=pre.sx;
		else ans-=pre.sy;
		tr.change(rt[top[u]],dfn[top[u]],dfn[bot[u]],dfn[u]);
		pre=tr.query(rt[top[u]],dfn[top[u]],dfn[bot[u]],dfn[top[u]],dfn[u]);
		if(tmp.vy==pre.x) ans+=pre.sx;
		else ans+=pre.sy;
		update(top[u],(tmp.vy==pre.x)?pre.vx:pre.vy),u=fat[top[u]];
	}
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n,n++;
	for(int i=2;i<=n;i++) cin>>fat[i],e[fat[i]].emplace_back(i);
	dfs1(1),dfs2(1,1);
	for(int i=1;i<=n;i++) if(top[i]!=i) bot[i]=bot[top[i]];
	for(int i=1;i<=n;i++) if(top[i]==i){
		val[i]=21;
		cnt[fat[i]][val[i]]++,bi[fat[i]]|=(1<<val[i]);
	}
	for(int i=1;i<=n;i++) if(i==top[i]) rt[i]=++tot,tr.build(rt[i],dfn[i],dfn[bot[i]]);
	for(int i=1;i<=n;i++){
		solve(i);
		if(i!=1) cout<<ans<<"\n";
	}
	return 0;
}