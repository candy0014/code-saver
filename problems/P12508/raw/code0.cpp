#include <bits/stdc++.h>
using namespace std;
const int inf=1e9;
int n,ca,a[300005];
int nex[300005],to[300005],st[300005],tot;
int res[300005],suf[300005];
int h[300005];
int ma[300005][20];
int getma(int u,int v){return (h[u]>=h[v])?u:v;}
int get(int u,int v){
	if(to[v]<nex[u]) return to[v];
	return inf;
}
int query(int l,int r){
	int t=__lg(r-l+1);
	return getma(ma[l][t],ma[r-(1<<t)+1][t]);
}
vector<pair<int,int> >as[300005];
struct TREE{
	int tag[1200005],tagd[1200005];
	pair<int,int> tim[1200005];
	void update(int p,int l,int r,int t,int td){
		int tmp=query(t,t+(r-l+1)-1);
		tag[p]=t,tagd[p]=td,tim[p]=make_pair(h[tmp]+td,-(l+(tmp-t)));
	}
	void pushdown(int p,int l,int r){
		if(!tag[p]) return;
		int mid=(l+r)>>1;
		update(p*2,l,mid,tag[p],tagd[p]);
		update(p*2+1,mid+1,r,tag[p]+(mid-l+1),tagd[p]);
		tag[p]=tagd[p]=0;
	}
	void pushup(int p){
		tim[p]=max(tim[p*2],tim[p*2+1]);
	}
	void change(int p,int l,int r,int L,int R,int t,int td){
		if(r<L||l>R) return;
		if(L<=l&&r<=R){update(p,l,r,t,td);return;}
		int mid=(l+r)>>1;pushdown(p,l,r);
		change(p*2,l,mid,L,R,t,td),change(p*2+1,mid+1,r,L,R,t+(mid-l+1),td),pushup(p);
	}
	pair<int,int> gettim(int p,int l,int r,int L,int R){
		if(r<L||l>R||L>R) return make_pair(-inf,0);
		if(L<=l&&r<=R) return tim[p];
		int mid=(l+r)>>1;pushdown(p,l,r);
		return max(gettim(p*2,l,mid,L,R),gettim(p*2+1,mid+1,r,L,R));
	}
	int getval(int p,int l,int r,int x){
		if(l==r) return tag[p];
		int mid=(l+r)>>1;pushdown(p,l,r);
		if(x<=mid) return getval(p*2,l,mid,x);
		return getval(p*2+1,mid+1,r,x);
	}
	void _change(int p,int l,int r,int x,int t){
		if(l==r){
			tim[p]=make_pair(t,-x);
			return;
		}
		int mid=(l+r)>>1;pushdown(p,l,r);
		if(x<=mid) _change(p*2,l,mid,x,t);
		else _change(p*2+1,mid+1,r,x,t);
		pushup(p);
	}
}tr;
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>ca;
	for(int i=1;i<=n;i++) cin>>a[i];
	st[0]=n+1;
	for(int i=n;i>=1;i--){
		while(tot&&a[st[tot]]<a[i]) tot--;
		nex[i]=st[tot],st[++tot]=i,suf[i]=max(suf[i+1],a[i]);
	}
	st[tot=0]=n+1;
	for(int i=n;i>=1;i--){
		while(tot&&a[st[tot]]>a[i]) tot--;
		to[i]=st[tot],st[++tot]=i;
	}
	for(int i=1;i<=n;i++) h[i]=-inf,ma[i][0]=i;
	for(int i=2;i<n;i++) h[i]=n+i+1-get(i-1,i);
	for(int j=1;j<20;j++) for(int i=1;i+(1<<j)-1<=n;i++) ma[i][j]=getma(ma[i][j-1],ma[i+(1<<(j-1))][j-1]);
	tr.change(1,1,n,1,n,1,0);
	for(int i=1,k,t;i<=ca;i++){
		cin>>k>>t;
		if(k==1) res[i]=n;
		else as[k].emplace_back(t,i);
	}
	for(int i=n;i>=1;i--){
		for(auto [t,id]:as[i]){
			if(t<i) res[id]=a[tr.getval(1,1,n,t)];
			else res[id]=suf[min(n,nex[tr.getval(1,1,n,i-1)])];
		}
		pair<int,int>tim=tr.gettim(1,1,n,2,i-2);
		if(tim.first!=i) continue;
		int pos=-tim.second,poss=tr.getval(1,1,n,pos-1);
		int tt=n-(i-pos-1);
		tr.change(1,1,n,pos,i-2,tt-pos+1,pos-tt);
		tr._change(1,1,n,pos,n+pos+1-get(poss,tt));
	}
	for(int i=1;i<=ca;i++) cout<<res[i]<<"\n";
	return 0;
}