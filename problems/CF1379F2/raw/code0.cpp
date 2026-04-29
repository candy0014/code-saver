#include <bits/stdc++.h>
using namespace std;
int n,m,ca;
set<int>st[2][200005];
int mi[800005],ma[800005],h[800005],cnt;
void build(int p,int l,int r){
	ma[p]=0,mi[p]=m+1;
	if(l==r) return;
	int mid=(l+r)>>1;build(p*2,l,mid),build(p*2+1,mid+1,r);
}
void pushup(int p){
	cnt-=h[p],mi[p]=min(mi[p*2],mi[p*2+1]),ma[p]=max(ma[p*2],ma[p*2+1]),h[p]=(ma[p*2+1]>=mi[p*2]),cnt+=h[p];
}
void change(int p,int l,int r,int x,int t1,int t2){
	if(r<x||l>x) return;
	if(l==r){cnt-=h[p],(t1==0?mi[p]:ma[p])=t2,h[p]=(ma[p]>=mi[p]),cnt+=h[p];return;}
	int mid=(l+r)>>1;change(p*2,l,mid,x,t1,t2),change(p*2+1,mid+1,r,x,t1,t2),pushup(p);
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>ca;
	for(int i=1;i<=n;i++) st[0][i].insert(m+1),st[1][i].insert(0);
	build(1,1,n);
	while(ca--){
		int x,y;
		cin>>x>>y,x++,y++;
		if(st[x&1][x/2].find(y/2)!=st[x&1][x/2].end()) st[x&1][x/2].erase(y/2);
		else st[x&1][x/2].insert(y/2);
		if(x&1) change(1,1,n,x/2,1,*st[x&1][x/2].rbegin());
		else change(1,1,n,x/2,0,*st[x&1][x/2].begin());
		if(cnt) cout<<"NO\n";
		else cout<<"YES\n";
	}
	return 0;
}