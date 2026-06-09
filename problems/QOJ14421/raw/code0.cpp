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
int n,m,rt[100005],k,ca,fa[100005],sz[100005];
vector<int>e[100005];
mt19937 rd(time(0));
int dis[505][100005];
queue<int>q;
int Find(int u){return fa[u]==u?u:(fa[u]=Find(fa[u]));}
void merge(int u,int v){u=Find(u),v=Find(v);if(u!=v)fa[u]=v,sz[v]+=sz[u];}
void solve(int Ca){
	cin>>n>>m>>ca;
	k=min(n,500);
	for(int i=1;i<=n;i++) rt[i]=i,fa[i]=i,sz[i]=1;
	for(int i=1,u,v;i<=m;i++) cin>>u>>v,e[u].emplace_back(v),e[v].emplace_back(u),merge(u,v);
	shuffle(rt+1,rt+n+1,rd);
	memset(dis,0x3f3f3f3f,sizeof(dis));
	for(int i=1;i<=k;i++){
		q.push(rt[i]);dis[i][rt[i]]=0;
		while(!q.empty()){
			int u=q.front();q.pop();
			for(auto v:e[u]){
				if(dis[i][v]==0x3f3f3f3f) dis[i][v]=dis[i][u]+1,q.push(v);
			}
		}
	}
	while(ca--){
		int u,v;cin>>u>>v;
		if(Find(u)!=Find(v)){cout<<"YES\n";continue;}
		if(sz[Find(u)]<=20000){cout<<"NO\n";continue;}
		int flag=0;
		for(int i=1;i<=k;i++){
			if(dis[i][u]+dis[i][v]<=20000){flag=1;break;}
		}
		if(flag) cout<<"NO\n";
		else cout<<"YES\n";
	}
}
int main(){
	// #ifdef ONLINE_JUDGE
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	// #endif
	#ifndef ONLINE_JUDGE
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	#endif
	
	int Ca=1;
//	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}