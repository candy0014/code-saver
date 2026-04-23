#include <bits/stdc++.h>
using namespace std;
struct MAT{
	int a[2][2];
	MAT(int op=0){
		a[0][1]=a[1][0]=-1e9;
		a[0][0]=a[1][1]=op?0:-1e9;
	}
	MAT operator*(const MAT &rs)const{
		MAT res;
		for(int i:{0,1}) for(int j:{0,1}) for(int k:{0,1}) res.a[i][j]=max(res.a[i][j],a[i][k]+rs.a[k][j]);
		return res;
	}
}base[1000005],sum[1000005];
int n,ca;
int val[1000005];
vector<int>e[1000005];
int fat[1000005],sz[1000005],son[1000005];
void dfs1(int u,int fa){
	fat[u]=fa,sz[u]=1;
	for(auto v:e[u]) if(v!=fa){
		dfs1(v,u),sz[u]+=sz[v];
		if(sz[son[u]]<sz[v]) son[u]=v;
	}
}
int dfn[1000005],_dfn[1000005],num,top[1000005],f[1000005],ls[1000005],rs[1000005];
int st[1000005],tt,pre[1000005];
void pushup(int p){
	MAT res(1);
	if(ls[p]) res=sum[ls[p]];
	res=res*base[p];
	if(rs[p]) res=res*sum[rs[p]];
	sum[p]=res;
}
int build(int l,int r){
	if(l>r) return 0;
	int _l=l,_r=r,mid,res=l;
	while(_l<=_r){
		mid=(_l+_r)>>1;
		if(pre[mid]-pre[l-1]<pre[r]-pre[mid]) _l=mid+1;
		else _r=mid-1,res=mid;
	}
	int u=st[res];
	ls[u]=build(l,res-1),rs[u]=build(res+1,r);
	f[ls[u]]=f[rs[u]]=u;
	pushup(u);
	return u;
}
int dfs2(int u){
	dfn[u]=++num,_dfn[num]=u;
	int v=u;
	while(v){
		top[v]=u;
		for(auto w:e[v]) if(w!=son[v]&&w!=fat[v]){
			int t=dfs2(w);
			f[t]=v;
			int dp0=max(sum[t].a[0][0],sum[t].a[0][1]),dp1=max(sum[t].a[1][0],sum[t].a[1][1]);
			dp1=max(dp0,dp1),base[v].a[0][0]+=dp1,base[v].a[0][1]+=dp1,base[v].a[1][0]+=dp0;
		}
		v=son[v];
	}
	tt=0,v=u;
	while(v) st[++tt]=v,pre[tt]=pre[tt-1]+sz[v]-sz[son[v]],v=son[v];
	return build(1,tt);
}
void change(int u,int x){
	base[u].a[1][0]+=x,val[u]+=x;
	while(u){
		if(f[u]&&top[u]!=top[f[u]]){
			int dp0=max(sum[u].a[0][0],sum[u].a[0][1]),dp1=max(sum[u].a[1][0],sum[u].a[1][1]);
			dp1=max(dp0,dp1),base[f[u]].a[0][0]-=dp1,base[f[u]].a[0][1]-=dp1,base[f[u]].a[1][0]-=dp0;
		}
		pushup(u);
		if(f[u]&&top[u]!=top[f[u]]){
			int dp0=max(sum[u].a[0][0],sum[u].a[0][1]),dp1=max(sum[u].a[1][0],sum[u].a[1][1]);
			dp1=max(dp0,dp1),base[f[u]].a[0][0]+=dp1,base[f[u]].a[0][1]+=dp1,base[f[u]].a[1][0]+=dp0;
		}
		u=f[u];
	}
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>ca;
	for(int i=1;i<=n;i++) cin>>val[i];
	for(int i=1,u,v;i<n;i++) cin>>u>>v,e[u].emplace_back(v),e[v].emplace_back(u);
	for(int i=1;i<=n;i++) base[i].a[0][0]=base[i].a[0][1]=0,base[i].a[1][0]=val[i];
	dfs1(1,0);
	int rt=dfs2(1);
	int lastans=0;
	while(ca--){
		int u,x;cin>>u>>x,u^=lastans,x-=val[u];
		change(u,x);
		cout<<(lastans=max({sum[rt].a[0][0],sum[rt].a[0][1],sum[rt].a[1][0],sum[rt].a[1][1]}))<<"\n";
	}
	return 0;
}