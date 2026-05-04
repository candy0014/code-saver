#include <bits/stdc++.h>
using namespace std;
int n,m,a[1005],b[1005],an,bn,vis[1005],li[1005];
vector<int>e[1005];
bool dfs(int u,int tim){
	if(vis[u]==tim) return 0;
	vis[u]=tim;
	for(auto v:e[u]) if(!li[v]||dfs(li[v],tim)){li[v]=u;return 1;}
	return 0;
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1,u;i<=n;i++){
		cin>>u;
		if(u*2+1>m){cout<<"-1\n";return 0;}
		if(u*3ll>m) a[++an]=u;
		else b[++bn]=u;
	}
	for(int i=1;i<=an;i++) for(int j=1;j<=bn;j++) if(a[i]%b[j]==0&&2ll*a[i]+b[j]<=m) e[i].emplace_back(j);
	for(int i=1;i<=an;i++) if(!dfs(i,i)){cout<<"-1\n";return 0;}
	cout<<n-an<<"\n";
	for(int i=1;i<=bn;i++){
		if(li[i]) cout<<a[li[i]]*2+b[i]<<" "<<a[li[i]]+b[i]<<"\n";
		else cout<<b[i]*3<<" "<<b[i]*2<<"\n";
	}
	return 0;
}