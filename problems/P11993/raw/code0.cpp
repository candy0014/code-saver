#include <bits/stdc++.h>
using namespace std;
int n,de[2000005];
vector<int>e[2000005];
int L[2000005],R[2000005],num,id[2000005];
void dfs(int u){
	L[u]=++num,id[num]=u;
	for(auto v:e[u]) dfs(v);
	R[u]=num;
}
int ls[50000005],rs[50000005],sum[50000005];
int rt[2000005],cnt;
int insert(int p,int l,int r,int x,int k){
	if(!p) p=++cnt;
	sum[p]+=k; 
	if(l==r) return p;
	int mid=(l+r)>>1;
	if(x<=mid) ls[p]=insert(ls[p],l,mid,x,k);
	else rs[p]=insert(rs[p],mid+1,r,x,k);
	return p;
}
int query(int p,int l,int r,int L,int R){
	if(!p||r<L||l>R) return 0;
	if(L<=l&&r<=R) return sum[p];
	int mid=(l+r)>>1;return query(ls[p],l,mid,L,R)+query(rs[p],mid+1,r,L,R);
}
int merge(int p,int q){
	if(!p||!q) return p+q;
	sum[p]+=sum[q],ls[p]=merge(ls[p],ls[q]),rs[p]=merge(rs[p],rs[q]);
	return p;
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=2,u;i<=n;i++) cin>>u,e[u].emplace_back(i),de[i]=de[u]+1;
	dfs(1);
	for(int i=1,x;i<=n;i++) cin>>x,rt[de[i]]=insert(rt[de[i]],1,n,L[i],x);
	int ca;cin>>ca;while(ca--){
		int op,x,y;
		cin>>op>>x;
		if(op==1) cin>>y,rt[y]=merge(rt[y],rt[x]),rt[x]=0;
		if(op==2) cin>>y,rt[de[x]]=insert(rt[de[x]],1,n,L[x],y);
		if(op==3) cout<<query(rt[de[x]],1,n,L[x],R[x])<<"\n";
	}
	return 0;
}