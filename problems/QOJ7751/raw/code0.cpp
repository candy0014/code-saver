#include <bits/stdc++.h>
using namespace std;
int n,m;
string s[55];
string ress="",res="";
int get(int x,int y){return 1<=x&&x<=n&&1<=y&&y<=m&&s[x][y]=='1';}
int sx,sy,ex,ey;
int vis[55][55],pre[55][55];
int dir[4][2]={1,0,0,1,-1,0,0,-1};
void dfs(int x,int y){
	vis[x][y]=1;
	for(int i=0;i<4;i++){
		int tx=x+dir[i][0],ty=y+dir[i][1];
		if(get(tx,ty)&&!vis[tx][ty]) pre[tx][ty]=i,ress+="0123"[i],dfs(tx,ty),ress+="2301"[i];
	}
}
void work(int t){
	t=(t+2)%4;
	int x1=sx,y1=sy,x2=ex,y2=ey,cnt=0;
	while(get(x1+dir[t][0],y1+dir[t][1])&&get(x2-dir[t][0],y2-dir[t][1])) x1+=dir[t][0],y1+=dir[t][1],x2-=dir[t][0],y2-=dir[t][1],cnt++,res+="DRUL"[t];
	if(get(x2-dir[t][0],y2-dir[t][1])) res+="DRUL"[t];
	cnt++;
	while(cnt--) res+="ULDR"[t];
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>s[i],s[i]=" "+s[i];
	cin>>sx>>sy>>ex>>ey;
	dfs(sx,sy);
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(s[i][j]=='1'&&!vis[i][j]){cout<<"-1\n";return 0;}
	int nx=ex,ny=ey;
	while(nx!=sx||ny!=sy){
		int t=pre[nx][ny];
		res+="0123"[t],nx-=dir[t][0],ny-=dir[t][1];
	}
	reverse(res.begin(),res.end()),ress+=res,res="";
	for(int i=0;ress[i];i++) work(ress[i]-'0'),sx+=dir[ress[i]-'0'][0],sy+=dir[ress[i]-'0'][1];
	ress=res,reverse(res.begin(),res.end());
	cout<<ress<<res<<"\n";
	return 0;
}