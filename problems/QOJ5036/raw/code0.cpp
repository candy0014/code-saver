#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct EDGE{int nex,to,f,w;}e[3000005];
int s,t,n;
int tot=1,head[500005],_head[500005];
void ADD(int u,int v,int f,int w){e[++tot].nex=head[u],e[tot].to=v,e[tot].f=f,e[tot].w=w,head[u]=tot;}
void add(int u,int v,int f,int w){ADD(u,v,f,w),ADD(v,u,0,-w);/*cerr<<u<<" "<<v<<" "<<f<<" "<<w<<"\n";*/}
ll h[500005];
void init(){
	vector<int>du(n+1,0);
	queue<int>q;
	for(int i=2;i<=tot;i+=2) du[e[i].to]++;
	for(int i=1;i<=n;i++) if(!du[i]) q.push(i);
	for(int i=1;i<=n;i++) h[i]=1e18;
	h[s]=0;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nex) if(e[i].f){
			int v=e[i].to;
			h[v]=min(h[v],h[u]+e[i].w);
			if(!--du[v]) q.push(v);
		}
	}
}
bool bfs(){
	priority_queue<pair<ll,int> >q;
	vector<ll>dis(n+1,1e18);
	vector<int>vis(n+1,0);
	q.emplace(0,s),dis[s]=0;
	while(!q.empty()){
		int u=q.top().second;q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(int i=head[u];i;i=e[i].nex) if(e[i].f){
			ll v=e[i].to,w=dis[u]+e[i].w+h[u]-h[v];
			if(dis[v]>w) dis[v]=w,q.emplace(-dis[v],v);
		}
	}
	for(int i=1;i<=n;i++) h[i]+=dis[i],_head[i]=head[i];
	// cerr<<dis[t]<<"\n";
	return dis[t]<1e18;
}
ll res;
int vis[500005];
int dfs(int u,int now){
	if(u==t) return now;
	vis[u]=1;
	int sum=0;
	for(int &i=_head[u];i&&now;i=e[i].nex){
		int v=e[i].to;
		if(vis[v]||!e[i].f||h[v]!=h[u]+e[i].w) continue;
		int tmp=dfs(v,min(now,e[i].f));
		e[i].f-=tmp,e[i^1].f+=tmp,now-=tmp,sum+=tmp,res+=1ll*tmp*e[i].w;
	}
	vis[u]=0;
	return sum;
}
int dinic(){
	int sum=0;
	while(bfs()) sum+=dfs(s,1e9);
	return sum;
}
int nn,m,k;
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>nn>>m>>k,n=nn+3,s=nn+2,t=nn+3;
	for(int i=1;i<=nn;i++) add(i,i+1,k,0);
	add(s,1,k,0),add(nn+1,t,k,0);
	while(m--){
		int l,r,x;
		cin>>l>>r>>x;
		add(l,r+1,1,-x);
	}
	init(),dinic();
	cout<<-res<<"\n";
	return 0;
}
