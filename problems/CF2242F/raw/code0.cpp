#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
mt19937_64 rd(time(0));
int n;
ll a[100005],sum[100005],res[100005];
struct TREE{
	ll val[100005],tag[100005],mi[100005];
	int ls[100005],rs[100005];
	ull pri[100005];
	void pushup(int p){
		if(ls[p]) mi[p]=mi[ls[p]];
		else mi[p]=val[p];
	}
	void update(int p,ll t){if(p)val[p]+=t,tag[p]+=t,mi[p]+=t;}
	void pushdown(int p){update(ls[p],tag[p]),update(rs[p],tag[p]),tag[p]=0;}
	void split(int p,ll k,int &x,int &y){
		if(!p){x=y=0;return;}
		pushdown(p);
		if(val[p]<=k) x=p,split(rs[p],k,rs[x],y),pushup(x);
		else y=p,split(ls[p],k,x,ls[y]),pushup(y);
	}
	int merge(int x,int y){
		if(!x||!y) return x+y;
		pushdown(x),pushdown(y);
		if(pri[x]>pri[y]){rs[x]=merge(rs[x],y),pushup(x);return x;}
		ls[y]=merge(x,ls[y]),pushup(y);return y;
	}
	int join(int x,int y){
		if(!x||!y) return x+y;
		ll tx=mi[x],ty=mi[y];
		int t=0;
		if(tx<=ty) split(x,ty,t,x);
		else split(y,tx,t,y);
		return merge(t,join(x,y));
	}
	void getans(int p){
		if(!p) return;
		pushdown(p),getans(ls[p]),getans(rs[p]);
	}
}tr;
int rt;
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],sum[i]=sum[i-1]+a[i],tr.val[i]=sum[i-1],tr.pri[i]=rd();
	for(int i=1;i<=n;i++) rt=tr.join(rt,i);
	for(int i=1;i<=n;i++){
		int x,y;
		tr.split(rt,a[i]-1,x,y);
		tr.update(x,a[i]),tr.update(y,-a[i]);
		rt=tr.join(x,y);
	}
	tr.getans(rt);
	for(int i=n;i>=1;i--) cout<<tr.val[i]<<" \n"[i==1];
	return 0;
}