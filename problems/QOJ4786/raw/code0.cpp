#include <bits/stdc++.h>
using namespace std;
int n,m,s,t,head[5005],tot=1;
struct EDGE{int nex,to,f,w;}e[100005];
void ADD(int u,int v,int f,int w){e[++tot].nex=head[u],e[tot].to=v,e[tot].f=f,e[tot].w=w,head[u]=tot;}
void add(int u,int v,int f,int w){ADD(u,v,f,w),ADD(v,u,0,-w);}
struct Ans{int f,w;};
int dis[5005],_head[5005],vis[5005];
queue<int>q;
bool bfs(int op=0){
	for(int i=1;i<=n;i++) dis[i]=INT_MAX,vis[i]=0,_head[i]=head[i];
	dis[s]=0,vis[s]=1,q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop(),vis[u]=0;
		for(int i=head[u];i;i=e[i].nex){
			int v=e[i].to,f=e[i].f,w=e[i].w;
			if(op){
				if(u==s||v==s) f^=1;
			}
			if(!f||dis[v]<=dis[u]+w) continue;
			dis[v]=dis[u]+w;
			if(!vis[v]) q.push(v),vis[v]=1;
		}
	}
	return dis[t]!=INT_MAX;
}
Ans dfs(int u,int now){
	if(u==t) return Ans{now,0};
	Ans sum=Ans{0,0};
	vis[u]=1;
	for(int i=_head[u];i&&now;i=e[i].nex){
		_head[u]=i;
		int v=e[i].to,f=e[i].f,w=e[i].w;
		if(!f||dis[v]!=dis[u]+w||vis[v]) continue;
		Ans tmp=dfs(v,min(now,f));
		e[i].f-=tmp.f,e[i^1].f+=tmp.f,sum.f+=tmp.f,now-=tmp.f,sum.w+=tmp.w+tmp.f*w;
	}
    vis[u]=0;
	return sum;
}
Ans dinic(){
	Ans sum=Ans{0,0};
	while(bfs()){
		Ans tmp=dfs(s,INT_MAX);
		sum.f+=tmp.f,sum.w+=tmp.w;
	}
	return sum;
}
int nn,val[55][55],ans[105];
int main(){
	#ifndef ONLINE_JUDGE
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	cin>>nn;
	for(int i=1;i<=nn;i++) for(int j=1;j<=nn;j++) cin>>val[i][j];
	n=nn+nn+2,s=n-1,t=n;
	for(int i=1;i<=nn;i++){
		add(s,i,1,0),add(nn+i,t,1,0);
		for(int j=1;j<=nn;j++) add(i,nn+j,2,-val[i][j]);
	}
	Ans res=dinic();
	cout<<-res.w*nn<<"\n";
	bfs(1);
	for(int i=1;i<=nn;i++) ans[i]=dis[i],ans[i+nn]=-dis[i+nn];
	for(int i=1;i<=nn;i++) for(int j=1;j<=nn;j++) cout<<ans[i]+ans[j+nn]<<" \n"[j==nn];
	return 0;
}