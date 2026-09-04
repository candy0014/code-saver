#include <bits/stdc++.h>
using namespace std;
int n,l[5005],r[5005],cnt,lin[5005];
bitset<5005>e[5005],vis;
int dfs(int u){
	while(1){
		int v=(e[u]&vis)._Find_first();
		if(v>=n) break;
		vis[v]=0;
		if(lin[v]==-1||dfs(lin[v])){lin[v]=u;return 1;}
	}
	return 0;
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=0;i<n;i++) cin>>l[i]>>r[i],lin[i]=-1;
	for(int i=0;i<n;i++) for(int j=0;j<n;j++) if(l[i]<l[j]&&l[j]<r[i]&&r[i]<r[j]) e[i][j]=1;
	for(int i=0;i<n;i++) vis.set(),cnt+=dfs(i);
	cout<<n*2-cnt<<"\n";
	return 0;
}