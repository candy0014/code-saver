#include <bits/stdc++.h>
using namespace std;
int ca,n;
int ls[2000005],rs[2000005],tag[2000005],son[2000005][4],vis[2000005],tot,now;
void insert(int x){
	if(!son[now][x]) son[now][x]=++tot;
	now=son[now][x];
}
bool dfs(int u){
	if(vis[u]) return 0;
	for(int i=0;i<4;i++) if(!son[u][i]||dfs(son[u][i])) return 1;
	return 0;
}
void solve(){
	cin>>ca;
	for(int i=0;i<=tot;i++){
		vis[i]=0;
		for(int j=0;j<4;j++) son[i][j]=0;
	}
	tot=0;
	while(ca--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>ls[i]>>rs[i],tag[i]=!ls[i]&&!rs[i];
		int u=1,flag=1;now=0;
		while(ls[u]||rs[u]){
			if(!ls[u]) insert(0),u=rs[u];
			else if(!rs[u]) insert(1),u=ls[u];
			else if(!tag[ls[u]]&&!tag[rs[u]]){flag=0;break;}
			else if(!tag[ls[u]]) insert(2),u=ls[u];
			else if(!tag[rs[u]]) insert(3),u=rs[u];
			else{
				int tmp=now;
				insert(2),vis[now]=1,now=tmp,insert(3);
				break;
			}
		}
		if(flag) vis[now]=1;
	}
	if(dfs(0)) cout<<"No\n";
	else cout<<"Almost Complete\n";
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}