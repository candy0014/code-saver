#include <bits/stdc++.h>
using namespace std;
int g[20][20];
int L[20]={0,5,5,5,5,1,2,3,4,5,5,5,5,5,10,11,12,13};
int R[20]={0,5,6,7,8,13,13,13,13,13,14,15,16,17,13,13,13,13};
int vis[20][20];
pair<int,int> t[20][20];
int res,flag,tx,ty;
bool check(int x,int y){return x<1||x>17||y<L[x]||y>R[x];}
void dfs(int x,int y,int lax,int lay){
	if(check(x,y)||vis[x][y]>=2||g[x][y]){
		if(x==lax&&y==lay) flag=1;
		return;
	}
	if(vis[x][y]){
		if(t[x][y]==make_pair(lax,lay)) return;
	}
	if(vis[x][y]==0&&(x!=tx||y!=ty)) res++;
	vis[x][y]++,t[x][y]=make_pair(lax,lay);
	int dir[6][2]={1,0,-1,0,0,1,0,-1,-1,-1,1,1};
	for(int i=0;i<6;i++){
		for(int j=1;!check(x+dir[i][0]*j*2,y+dir[i][1]*j*2);j++){
			if(g[x+dir[i][0]*j][y+dir[i][1]*j]){
				int sx=x+dir[i][0]*j*2,sy=y+dir[i][1]*j*2;
				if(check(sx,sy)) break;
				int f=0;
				for(int jj=j+1;jj<=j+j;jj++) if(g[x+dir[i][0]*jj][y+dir[i][1]*jj]){f=1;break;}
				if(f||(sx==lax&&sy==lay)) break;
				dfs(sx,sy,x,y);
				break;
			}
		}
	}
}
void solve(){
	memset(g,0,sizeof(g)),res=0,flag=0;
	int n,x,y;cin>>n;while(n--)cin>>x>>y,g[x][y+L[x]-1]=1;
	for(int i=1;i<=17;i++) for(int j=L[i];j<=R[i];j++) if(g[i][j]){
		memset(vis,0,sizeof(vis)),g[i][j]=0,tx=i,ty=j;
		dfs(i,j,-1,-1),g[i][j]=1;
	}
	cout<<res+flag<<"\n";
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}