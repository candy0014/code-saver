#include <bits/stdc++.h>
using namespace std;
int n,ca,d,a[300005],ans[300005];
vector<pair<int,int> >as[300005];
int mi[1200005],ma[1200005];
int tag1[1200005],tag2[1200005];
void update(int p,int t1,int t2){
	if(t1!=-1) tag1[p]=t1,tag2[p]=0,mi[p]=ma[p]=t1;
	tag2[p]+=t2,mi[p]+=t2,ma[p]+=t2;
}
void pushdown(int p){
	update(p*2,tag1[p],tag2[p]),update(p*2+1,tag1[p],tag2[p]);
	tag1[p]=-1,tag2[p]=0;
}
void pushup(int p){mi[p]=mi[p*2],ma[p]=ma[p*2+1];}
int query(int p,int l,int r,int x){
	if(l==r) return mi[p];
	int mid=(l+r)>>1;pushdown(p);
	if(x<=mid) return query(p*2,l,mid,x);
	return query(p*2+1,mid+1,r,x);
}
void change(int p,int l,int r,int L,int R,int d){
	if(r<L||l>R||L>R) return;
	if(L<=l&&r<=R){
		if(mi[p]>=2*d){update(p,-1,-d);return;}
		if(mi[p]>=d&&ma[p]<2*d){update(p,d-1,0);return;}
		if(ma[p]<d) return;
	}
	int mid=(l+r)>>1;pushdown(p),change(p*2,l,mid,L,R,d),change(p*2+1,mid+1,r,L,R,d),pushup(p);
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>ca>>d;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1,l,r;i<=ca;i++) cin>>l>>r,as[r].emplace_back(l,i);
	for(int i=1;i<=n*4;i++) tag1[i]=-1,mi[i]=ma[i]=d;
	for(int i=1;i<=n;i++){
		change(1,1,n,1,i,a[i]);
		for(auto x:as[i]) ans[x.second]=query(1,1,n,x.first);
	}
	for(int i=1;i<=ca;i++) cout<<ans[i]<<"\n";
	return 0;
}