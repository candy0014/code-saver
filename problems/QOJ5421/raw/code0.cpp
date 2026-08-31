#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,k;
mt19937 rd(time(0));
vector<ll>ans;
struct TREE{
	int rt[200005],tot;
	int ls[2000005],rs[2000005],pri[2000005],sz[2000005];
	ll val[2000005];
	ll tag1[2000005],tag2[2000005];
	void init(){
		tot=0;
		for(int i=1;i<=n;i++){
			++tot;
			rt[i]=i,ls[i]=rs[i]=0,pri[i]=rd(),sz[i]=1,val[i]=0,tag1[i]=tag2[i]=0;
		}
	}
	void pushup(int p){sz[p]=sz[ls[p]]+1+sz[rs[p]];}
	void update(int p,ll t1,ll t2){
		if(!p) return;
		tag1[p]+=t1,tag2[p]+=t2;
		val[p]+=t1+t2*(sz[ls[p]]+1);
	}
	void pushdown(int p){
		update(ls[p],tag1[p],tag2[p]);
		update(rs[p],tag1[p]+(sz[ls[p]]+1)*tag2[p],tag2[p]);
		tag1[p]=tag2[p]=0;
	}
	void split(int p,int &x,int &y,ll v){
		if(!p){x=y=0;return;}
		pushdown(p);
		if(val[p]>=v) x=p,split(rs[p],rs[x],y,v);
		else y=p,split(ls[p],x,ls[y],v);
		pushup(p);
	}
	int merge(int x,int y){
		if(!x||!y) return x|y;
		pushdown(x),pushdown(y);
		if(pri[x]<pri[y]){rs[x]=merge(rs[x],y),pushup(x);return x;}
		else{ls[y]=merge(x,ls[y]),pushup(y);return y;}
	}
	int getsz(int u){return sz[rt[u]];}
	void insert(int p,int u){
		if(!p) return;
		int x,y;
		pushdown(p);
		insert(ls[p],u),insert(rs[p],u);
		ls[p]=rs[p]=0,sz[p]=1;
		split(rt[u],x,y,val[p]),rt[u]=merge(merge(x,p),y);
	}
	void change(int u,ll t1,ll t2){
		update(rt[u],t1,t2);
	}
	void print(int p){
		if(!p) return;
		pushdown(p);
		print(ls[p]);
		ans.emplace_back(val[p]);
		print(rs[p]);
	}
}tr;
vector<pair<int,int> >e[200005];
int val[200005],sz[200005];
void dfs(int u,int fa){
	sz[u]=1;
	for(auto [v,w]:e[u]) if(v!=fa){
		val[v]=w,dfs(v,u),sz[u]+=sz[v];
	}
	for(auto [v,w]:e[u]) if(v!=fa){
		if(tr.getsz(u)<tr.getsz(v)) swap(tr.rt[u],tr.rt[v]);
		tr.insert(tr.rt[v],u);
	}
	if(u!=1) tr.change(u,1ll*(k+1)*val[u],-2*val[u]);
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>k;
	ans.clear();
	for(int i=1;i<=n;i++) e[i].clear();
	for(int i=1,u,v,w;i<n;i++) cin>>u>>v>>w,e[u].emplace_back(v,w),e[v].emplace_back(u,w);
	tr.init();
	ans.emplace_back(0);
	dfs(1,0);
	tr.print(tr.rt[1]);
	for(int i=1;i<=n;i++) ans[i]+=ans[i-1];
	cout<<ans[k]<<"\n";
	return 0;
}