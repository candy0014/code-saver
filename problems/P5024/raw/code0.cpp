#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll V=1e12;
int n,ca;
ll val[1000005];
vector<int>e[1000005];
struct node{
	int ls,rs,sz,op,fa;
	ll a[2][2];
	node(ll v=0){
		ls=rs=op=fa=0,sz=1;
		a[0][0]=1e17,a[0][1]=0,a[1][0]=a[1][1]=v;
	}
}tr[2000005];
int cnt;
int newnode(int v){
	tr[++cnt]=node(v);
	return cnt;
}
int sz[1000005],son[1000005],fat[1000005];
void dfs1(int u,int fa){
	sz[u]=1,fat[u]=fa;
	for(auto v:e[u]) if(v!=fa){
		dfs1(v,u),sz[u]+=sz[v];
		if(sz[v]>sz[son[u]]) son[u]=v;
	}
}
void pushup(int p){
	node &res=tr[p],&ls=tr[tr[p].ls],&rs=tr[tr[p].rs];
	res.sz=ls.sz+rs.sz;
	if(!tr[p].op) for(int i:{0,1}) for(int j:{0,1}) res.a[i][j]=ls.a[i][j]+min(rs.a[0][j],rs.a[1][j]);
	else for(int i:{0,1}) for(int j:{0,1}) res.a[i][j]=min(rs.a[i][0]+ls.a[0][j],rs.a[i][1]+ls.a[1][j]);
}
int build(vector<int>&t,vector<int>&sum,int l,int r,int op){
	if(l+1==r) return t[l];
	int mid=lower_bound(sum.begin()+l+1,sum.begin()+r,((!l?0:sum[l-1])+sum[r-1])>>1)-sum.begin();
	if(mid==r) mid--;
	int p=++cnt;
	tr[p].op=op,tr[p].ls=build(t,sum,l,mid,op),tr[p].rs=build(t,sum,mid,r,op);
	tr[tr[p].ls].fa=tr[tr[p].rs].fa=p;
	pushup(p);
	return p;
}
int build(vector<int>&p,int op){
	vector<int>sum(p.size());
	sum[0]=tr[p[0]].sz;
	for(int i=1;i<(int)p.size();i++) sum[i]=sum[i-1]+tr[p[i]].sz;
	return build(p,sum,0,p.size(),op);
}
int mp[1000005];
int dfs2(int u){
	vector<int>p;p.emplace_back(mp[u]=newnode(val[u]));
	while(son[u]){
		vector<int>q;q.emplace_back(mp[son[u]]=newnode(val[son[u]]));
		for(auto v:e[u]) if(v!=fat[u]&&v!=son[u]) q.emplace_back(dfs2(v));
		p.emplace_back(build(q,0));
		u=son[u];
	}
	return build(p,1);
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	string ID;
	cin>>n>>ca>>ID;
	for(int i=1;i<=n;i++) cin>>val[i];
	for(int i=1,u,v;i<n;i++) cin>>u>>v,e[u].emplace_back(v),e[v].emplace_back(u);
	dfs1(1,0);
	int rt=dfs2(1);
	int lastans=0;
	while(ca--){
		int u,x,v,y,t;
		cin>>u>>x>>v>>y;
		if(x==0) val[u]+=V;
		else val[u]-=V;
		if(y==0) val[v]+=V*10;
		else val[v]-=V*10;
		tr[mp[u]].a[1][0]=tr[mp[u]].a[1][1]=val[u];
		t=mp[u];while(tr[t].fa) t=tr[t].fa,pushup(t);
		tr[mp[v]].a[1][0]=tr[mp[v]].a[1][1]=val[v];
		t=mp[v];while(tr[t].fa) t=tr[t].fa,pushup(t);
		ll res=min(tr[rt].a[0][1],tr[rt].a[1][1]);
		if(x==0) val[u]-=V;
		else val[u]+=V,res+=V;
		if(y==0) val[v]-=V*10;
		else val[v]+=V*10,res+=V*10;
		tr[mp[u]].a[1][0]=tr[mp[u]].a[1][1]=val[u];
		t=mp[u];while(tr[t].fa) t=tr[t].fa,pushup(t);
		tr[mp[v]].a[1][0]=tr[mp[v]].a[1][1]=val[v];
		t=mp[v];while(tr[t].fa) t=tr[t].fa,pushup(t);
		if(abs(res)>V/10) res=-1;
		cout<<res<<"\n";
	}
	return 0;
}