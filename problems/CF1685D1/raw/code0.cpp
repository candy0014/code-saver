#include <bits/stdc++.h>
using namespace std;
int n,a[205],b[205],vis[205],cnt,tag[205],viss[205];
void dfs(int u){
	cout<<u<<" ",tag[vis[u]]=1,viss[u]=1;
	if(u<n&&!tag[vis[u+1]]) dfs(b[u+1]);
	if(!viss[b[u]]) dfs(b[u]);
}
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],b[a[i]]=i;
	cnt=0;
	for(int i=1;i<=n;i++) vis[i]=viss[i]=tag[i]=0;
	for(int i=1;i<=n;i++) if(!vis[i]){
		++cnt;
		int u=a[i];vis[i]=cnt;
		while(u!=i) vis[u]=cnt,u=a[u];
	}
	dfs(1),cout<<"\n";
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}