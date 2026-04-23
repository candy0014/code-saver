#include <bits/stdc++.h>
using namespace std;
int ask(int x,int k){cout<<"? "<<x<<" "<<k<<endl,cin>>x;return x;}
int n,fat[30005],L[30005],R[30005],num,de[30005],mad;
vector<int>e[30005];
void dfs(int u){
	L[u]=++num,de[u]=de[fat[u]]+1,mad=max(mad,de[u]);
	for(auto v:e[u]) dfs(v);
	R[u]=num;
}
int tag[30005],sz[30005];
void solve(){
	cin>>n,mad=0;
	for(int i=1;i<=n;i++) e[i].clear();
	for(int i=2;i<=n;i++) cin>>fat[i],e[fat[i]].emplace_back(i);
	dfs(1);
	int l=1,r=mad,mid,res=0;
	while(l<=r){
		mid=(l+r)>>1;
		if(ask(1,mid-1)) res=mid,r=mid-1;
		else l=mid+1;
	}
	for(int i=1;i<=n;i++) tag[i]=(de[i]==res);
	while(1){
		for(int i=1;i<=n;i++) sz[i]=0;
		for(int i=n;i>=1;i--) sz[i]+=tag[i],sz[fat[i]]+=sz[i];
		if(sz[1]==1) break;
		int ma=0,mak=0;
		for(int i=1;i<=n;i++) if(sz[i]*2<=sz[1]&&sz[i]>ma) ma=sz[i],mak=i;
		int tmp=ask(mak,res-de[mak]);
		for(int i=1;i<=n;i++) if(tag[i]) tag[i]=((L[mak]<=L[i]&&L[i]<=R[mak])==tmp);
	}
	for(int i=1;i<=n;i++) if(tag[i]) cout<<"! "<<i<<endl;
}
int main(){
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}