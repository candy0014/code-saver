#include <bits/stdc++.h>
using namespace std;
int n,a[300005],b[300005];
struct TREE{
	int cnt[1200005],mi[1200005];
	int getmi(int u,int v){return a[u]<a[v]?u:v;}
	void build(int p,int l,int r){
		if(l==r){mi[p]=l,cnt[p]=1;return;}
		int mid=(l+r)>>1;build(p*2,l,mid),build(p*2+1,mid+1,r),mi[p]=getmi(mi[p*2],mi[p*2+1]),cnt[p]=cnt[p*2]+cnt[p*2+1];
	}
	void change(int p,int l,int r,int x){
		if(r<x||l>x) return;
		if(l==r){a[l]=1e9,cnt[p]=0;return;}
		int mid=(l+r)>>1;change(p*2,l,mid,x),change(p*2+1,mid+1,r,x),mi[p]=getmi(mi[p*2],mi[p*2+1]),cnt[p]=cnt[p*2]+cnt[p*2+1];
	}
	int querymi(int p,int l,int r,int L,int R){
		if(r<L||l>R||L>R) return 0;
		if(L<=l&&r<=R) return mi[p];
		int mid=(l+r)>>1;return getmi(querymi(p*2,l,mid,L,R),querymi(p*2+1,mid+1,r,L,R));
	}
	int querycnt(int p,int l,int r,int L,int R){
		if(r<L||l>R) return 0;
		if(L<=l&&r<=R) return cnt[p];
		int mid=(l+r)>>1;return querycnt(p*2,l,mid,L,R)+querycnt(p*2+1,mid+1,r,L,R);
	}
}tr;
void solve(){
	a[0]=1e9+1;
	cin>>n;
	for(int i=1,u;i<=n;i++) cin>>u,a[u]=i;
	tr.build(1,1,n);
	for(int i=1;i<=n;i++){
		int now=n+1;
		while(1){
			int x=tr.querymi(1,1,n,1,now-1),y=tr.querycnt(1,1,n,1,x);
			if(y&1){b[a[x]]=i,tr.change(1,1,n,x);break;}
			now=x;
		}
	}
	for(int i=1;i<=n;i++) cout<<b[i]<<" \n"[i==n];
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}