#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m,x[1000005],y[1000005],w[1000005],xx[1000005],yy[1000005],ww[1000005],lix[1000005],liy[1000005];
vector<pair<int,int> >p[1000005],pp[1000005];
struct TREE{
	ll ma[4000005],tag[4000005];
	void update(int p,ll t){ma[p]+=t,tag[p]+=t;}
	void pushdown(int p){update(p*2,tag[p]),update(p*2+1,tag[p]),tag[p]=0;}
	void build(int p,int l,int r){
		if(l==r){ma[p]=-(l!=0)*1e18;return;}
		int mid=(l+r)>>1;build(p*2,l,mid),build(p*2+1,mid+1,r),ma[p]=max(ma[p*2],ma[p*2+1]);
	}
	void change(int p,int l,int r,int L,int R,ll k){
		if(r<L||l>R) return;
		if(L<=l&&r<=R){update(p,k);return;}
		int mid=(l+r)>>1;pushdown(p),change(p*2,l,mid,L,R,k),change(p*2+1,mid+1,r,L,R,k),ma[p]=max(ma[p*2],ma[p*2+1]);
	}
	void change2(int p,int l,int r,int x,ll k){
		if(r<x||l>x) return;
		if(l==r){ma[p]=max(ma[p],k);return;}
		int mid=(l+r)>>1;pushdown(p),change2(p*2,l,mid,x,k),change2(p*2+1,mid+1,r,x,k),ma[p]=max(ma[p*2],ma[p*2+1]);
	}
	ll query(int p,int l,int r,int L,int R){
		if(r<L||l>R) return -1e18;
		if(L<=l&&r<=R) return ma[p];
		int mid=(l+r)>>1;pushdown(p);return max(query(p*2,l,mid,L,R),query(p*2+1,mid+1,r,L,R));
	}
}tr;
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>x[i]>>y[i]>>w[i],lix[i]=x[i],liy[i]=y[i];
	for(int i=1;i<=m;i++) cin>>xx[i]>>yy[i]>>ww[i];
	sort(lix+1,lix+n+1),sort(liy+1,liy+n+1);
	for(int i=1;i<=n;i++) x[i]=lower_bound(lix+1,lix+n+1,x[i])-lix,y[i]=lower_bound(liy+1,liy+n+1,y[i])-liy;
	for(int i=1;i<=m;i++) xx[i]=lower_bound(lix+1,lix+n+1,xx[i])-lix,yy[i]=lower_bound(liy+1,liy+n+1,yy[i])-liy;
	for(int i=1;i<=n;i++) p[y[i]].emplace_back(x[i],w[i]);
	for(int i=1;i<=m;i++) pp[yy[i]].emplace_back(xx[i],ww[i]);
	tr.build(1,0,n);
	for(int i=n;i>=1;i--){
		sort(p[i].begin(),p[i].end(),[&](pair<int,int>u,pair<int,int>v){return u.first>v.first;});
		for(auto [x,w]:p[i]) tr.change2(1,0,n,x,tr.query(1,0,n,0,x)-w);
		for(auto [x,w]:pp[i]) tr.change(1,0,n,x,n,w);
	}
	cout<<tr.ma[1]<<"\n";
	return 0;
}