#include <bits/stdc++.h>
using namespace std;
namespace Flow{
int n,m,s,t,head[90005],tot=1,de[90005],_head[90005];
struct EDGE{int nex,to,f;}e[1000005];
void ADD(int u,int v,int f){e[++tot].nex=head[u],e[tot].to=v,e[tot].f=f,head[u]=tot;}
void add(int u,int v,int f){ADD(u,v,f),ADD(v,u,0);}
queue<int>q;
bool bfs(){
	while(!q.empty()) q.pop();
	for(int i=1;i<=n;i++) de[i]=0,_head[i]=head[i];
	de[s]=1,q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nex){
			int v=e[i].to,f=e[i].f;
			if(de[v]||!f) continue;
			de[v]=de[u]+1,q.push(v);
			if(v==t) return 1;
		} 
	}
	return 0;
}
int dfs(int u,int now){
	int sum=0;
	if(u==t) return now;
	for(int i=_head[u];i&&now;i=e[i].nex){
		_head[u]=i;
		int v=e[i].to,f=e[i].f;
		if(de[v]!=de[u]+1||!f) continue;
		int tmp=dfs(v,min(f,now));
		if(!tmp) de[v]=0;
		sum+=tmp,now-=tmp,e[i].f-=tmp,e[i^1].f+=tmp;
	}
	return sum;
}
int dinic(){
	int ans=0;
	while(bfs()) ans+=dfs(s,2e9);
	return ans;
}
}
int n,k,flag[40005],tot;
vector<pair<int,int> >e[40005];
int vis[1000005],tag[40005];
vector<int>res;
void dfs(int u){
	tag[u]=1;
	for(auto x:e[u]) if(!vis[x.second]) vis[x.second]=1,dfs(x.first);
	res.emplace_back(u);
}
int ans[40005];
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>k;
	for(int j=1;j<=k*2;j++){
		for(int i=1,u;i<=n;i++){
			cin>>u;
			if(u==i){
				if(!flag[i]) e[i].emplace_back(i,++tot);
				flag[i]^=1;
			}
			if(u>i) e[i].emplace_back(u,++tot),e[u].emplace_back(i,tot);
		}
	}
	Flow::n=n+n+2,Flow::t=n+n+2,Flow::s=n+n+1;
	for(int i=1;i<=n;i++) if(!tag[i]){
		res.clear(),dfs(i);
		for(int j=1;j<(int)res.size();j++) Flow::add(res[j-1],res[j]+n,1);
	}
	int tmp=Flow::tot;
	for(int i=1;i<=n;i++) Flow::add(n+n+1,i,1),Flow::add(i+n,n+n+2,1);
	for(int i=1;i<=k;i++){
		Flow::dinic();
		for(int j=1;j<=n;j++) ans[j]=0;
		for(int j=2;j<=tmp;j+=2) if(Flow::e[j+1].f) ans[Flow::e[j+1].to]=Flow::e[j].to-n,Flow::e[j+1].f=0;
		for(int j=tmp+1;j<=Flow::tot;j+=2) Flow::e[j].f++,Flow::e[j+1].f--;
		for(int j=1;j<=n;j++) cout<<ans[j]<<" \n"[j==n];
	}
	return 0;
}
