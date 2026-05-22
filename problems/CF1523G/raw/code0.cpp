#include <bits/stdc++.h>
using namespace std;
struct TREE{
	int ls[20000005],rs[20000005],mi[20000005],cnt;
	void change(int &p,int l,int r,int x,int k){
		if(r<x||l>x) return;
		if(!p) p=++cnt,mi[p]=k;
		else mi[p]=min(mi[p],k);
		if(l==r) return;
		int mid=(l+r)>>1;change(ls[p],l,mid,x,k),change(rs[p],mid+1,r,x,k);
	}
	int query(int p,int l,int r,int L,int R){
		if(!p||r<L||l>R) return 1e9;
		if(L<=l&&r<=R) return mi[p];
		int mid=(l+r)>>1;return min(query(ls[p],l,mid,L,R),query(rs[p],mid+1,r,L,R));
	}
}tr;
int rt[50005],n,m,_l[100005],_r[100005];
void insert(int l,int r,int k){while(r<=n)tr.change(rt[r],1,n,l,k),r+=(r&(-r));}
int query(int l,int r){int t=1e9;while(r)t=min(t,tr.query(rt[r],1,n,l,n)),r-=(r&(-r));return t;}
vector<int>p[50005];
int res[50005];
int calc(int l,int r){
	if(l>r) return 0;
	int x=query(l,r);
	if(x>m) return 0;
	return calc(l,_l[x]-1)+calc(_r[x]+1,r)+_r[x]-_l[x]+1;
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++) cin>>_l[i]>>_r[i],p[_r[i]-_l[i]+1].emplace_back(i);
	for(int i=n;i>=1;i--){
		for(auto x:p[i]) insert(_l[x],_r[x],x);
		res[i]=calc(1,n);
	}
	for(int i=1;i<=n;i++) cout<<res[i]<<"\n";
	return 0;
}