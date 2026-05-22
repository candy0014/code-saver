#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll res;
int n,m,k;
string s[2505];
int p1[2505][10],p2[2505][10],q1[20],q2[20];
void work(){
	for(int i=0;i<=k;i++) res+=1ll*(q1[i+1]-q1[i])*(q2[k-i+1]-q2[k-i]);
}
void dfs(int x,int xx,int y,int yy){
	if(x==xx&&y==yy){res+=(k==s[x][y]-'0');return;}
	int l,r,g1,g2;
	if(xx-x<=yy-y){
		l=x,r=xx,g1=-(y-1),g2=yy+1;
		int mid=(y+yy)>>1;
		for(int i=x;i<=xx;i++){
			int tot=0;p1[i][0]=-mid;
			for(int j=mid;j>=y&&tot<=k+1;j--) if(s[i][j]=='1') p1[i][++tot]=-j;
			while(tot<=k+1) p1[i][++tot]=g1;
			tot=0,p2[i][0]=mid+1;
			for(int j=mid+1;j<=yy&&tot<=k+1;j++) if(s[i][j]=='1') p2[i][++tot]=j;
			while(tot<=k+1) p2[i][++tot]=g2;
		}
	}
	else{
		l=y,r=yy,g1=-(x-1),g2=xx+1;
		int mid=(x+xx)>>1;
		for(int i=y;i<=yy;i++){
			int tot=0;p1[i][0]=-mid;
			for(int j=mid;j>=x&&tot<=k+1;j--) if(s[j][i]=='1') p1[i][++tot]=-j;
			while(tot<=k+1) p1[i][++tot]=g1;
			tot=0,p2[i][0]=mid+1;
			for(int j=mid+1;j<=xx&&tot<=k+1;j++) if(s[j][i]=='1') p2[i][++tot]=j;
			while(tot<=k+1) p2[i][++tot]=g2;
		}
	}
	ll tmp=res;
	for(int i=l;i<=r;i++){
		for(int j=0;j<=k+1;j++) q1[j]=p1[i][j],q2[j]=p2[i][j];
		work();
		for(int j=i+1;j<=r;j++){
			for(int t=1;t<=k+1;t++) q1[k+1+t]=p1[j][t],q2[k+1+t]=p2[j][t];
			inplace_merge(q1,q1+k+2,q1+k*2+3);
			inplace_merge(q2,q2+k+2,q2+k*2+3);
			work();
		}
	}
	if(xx-x<=yy-y){
		int mid=(y+yy)>>1;
		dfs(x,xx,y,mid),dfs(x,xx,mid+1,yy);
	}
	else{
		int mid=(x+xx)>>1;
		dfs(x,mid,y,yy),dfs(mid+1,xx,y,yy);
	}
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++) cin>>s[i],s[i]=" "+s[i];
	dfs(1,n,1,m);
	cout<<res<<"\n";
	return 0;
}