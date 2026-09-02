#include <bits/stdc++.h>
using namespace std;
int n,m;
string s[2005],res[2005];
int id[2005][2005],cnt,h[2000005];
int heade[2000005],tot;
struct node{int nex,v,w;}e[2000005];
void add(int u,int v,int w){e[++tot].nex=heade[u],e[tot].v=v,e[tot].w=w,heade[u]=tot;}
void dfs(int x,int y){
	if(x<0||x>=n||y<0||y>=m||s[x][y]=='.'||id[x][y]) return;
	id[x][y]=cnt;
	dfs(x+1,y),dfs(x,y+1),dfs(x-1,y),dfs(x,y-1);
}
int q[2000005],head,tail;
int vis[2000005],dis[2000005];
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=n-1;i>=0;i--) cin>>s[i];
	for(int i=0;i<n;i++) for(int j=0;j<m;j++) if(s[i][j]=='#'&&!id[i][j]) ++cnt,h[cnt]=i,dfs(i,j);
	for(int j=0;j<m;j++){
		int la=-1;
		for(int i=0;i<n;i++) if(s[i][j]=='#'){
			if(la!=-1&&id[i][j]!=id[la][j]){
				add(id[la][j],id[i][j],1+(la-h[id[la][j]])-(i-h[id[i][j]]));
			}
			la=i;
		}
	}
	head=1;
	for(int i=1;i<=cnt;i++) q[++tail]=i,vis[i]=1;
	while((tail+1)%(cnt+1)!=head){
		int u=q[head++];vis[u]=0;
		if(head==cnt+1) head=0;
		for(int i=heade[u];i;i=e[i].nex){
			int v=e[i].v,w=e[i].w;
			if(dis[v]>dis[u]-w){
				dis[v]=dis[u]-w;
				if(!vis[v]){
					if(++tail==cnt+1) tail=0;
					q[tail]=v,vis[v]=1;
				}
			}
		}
	}
	for(int i=0;i<n;i++) for(int j=0;j<m;j++) res[i]+='.';
	for(int i=0;i<n;i++) for(int j=0;j<m;j++) if(s[i][j]=='#') res[i-h[id[i][j]]-dis[id[i][j]]][j]='#';
	for(int i=n-1;i>=0;i--) cout<<res[i]<<"\n";
	return 0;
}