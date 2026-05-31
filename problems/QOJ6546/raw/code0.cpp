#include <bits/stdc++.h>
using namespace std;
int n,ca;
vector<int>e[100005];
int tag[200005],lin[200005],h[200005];
int vis[200005],tim;
int ans;
bool dfs(int u){
	if(vis[u]==tim) return 0;
	vis[u]=tim;
	for(auto v:e[u]) if(!lin[v]||dfs(lin[v])){lin[v]=u;return 1;}
	return 0;
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>ca;
	while(ca--){
		int m;
		cin>>m;
		for(int i=1,u,v;i<=m;i++){
			cin>>u>>v;
			if(tag[u]||tag[v+n]) continue;
			e[u].emplace_back(v);
		}
		while(1){
			int flag=0;
			tim++;
			for(int i=1;i<=n;i++) if(!h[i]&&dfs(i)) h[i]=1,ans++,flag=1;
			if(!flag) break;
		}
		// for(int i=1;i<=n;i++) if(!h[i]) tim++,h[i]=dfs(i),ans+=h[i];
		cout<<ans<<" ";
		tim++;
		queue<int>q;
		for(int i=1;i<=n;i++) if(!h[i]) q.push(i),vis[i]=tim;
		while(!q.empty()){
			int u=q.front();q.pop();
			for(auto v:e[u]){
				if(lin[v]==u) continue;
				vis[v+n]=tim,tag[v+n]=1;
				if(vis[lin[v]]!=tim) vis[lin[v]]=tim,q.push(lin[v]);
			}
		}
		for(int i=1;i<=n;i++) if(vis[i]!=tim){
			tag[i]=1;
			vector<int>tmp;
			for(auto v:e[i]) if(vis[v+n]!=tim) tmp.emplace_back(v);
			e[i].swap(tmp);
		}
	}
	cerr<<clock()*1.0/CLOCKS_PER_SEC<<"\n";
	return 0;
}