#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
const ll mod=998244353;
const ll inf=2e9;
const int N=2e5+5;
const int M=2e5+5;
const int V=2e6+5;
int n,ca,m,vis[500005],g[500005];
int query(int u,int v){
	if(u>v) swap(u,v);
	if(u==v) return 0;
	if(vis[v-u]) return vis[v-u];
	int tmp=max(v-1,n-u);
	if(tmp>=g[v-u]) return 2;
	return 3;
}
void solve(int Ca){
	cin>>n>>ca,m=sqrt(n)+1;
	for(int i=1;i<=n;i++) vis[i]=0,g[i]=1e9;
	for(int i=1;i<=m;i++) vis[i*i]=1;
	for(int i=1;i<=m;i++) for(int j=1;j<=m;j++) if(!vis[i*i+j*j]) vis[i*i+j*j]=2;
	for(int i=1;i<=m;i++) for(int j=1;j<i;j++) g[i*i-j*j]=min(g[i*i-j*j],i*i);
	while(ca--){
		int u,v;
		cin>>u>>v;
		int res=query(u,v);
		if(res!=3){cout<<res<<"\n";continue;}
		res=4;
		for(int i=1;u-i*i>=1;i++) res=min(res,query(u-i*i,v)+1);
		for(int i=1;u+i*i<=n;i++) res=min(res,query(u+i*i,v)+1);
		cout<<res<<"\n";
	}
}
int main(){
	#ifdef ONLINE_JUDGE
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	#endif
	#ifndef ONLINE_JUDGE
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	
	int Ca=1;
	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}