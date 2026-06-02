#include <bits/stdc++.h>
using namespace std;
const int L=39;
int n,a[500005],dp[500005][4],ma[500005][4];
bool f[500005][40][4],g[40][7];
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	memset(dp,-0x3f3f3f3f,sizeof(dp));memset(ma,-0x3f3f3f3f,sizeof(ma));
	dp[0][0]=ma[0][0]=0;
	int suf=n;
	while(suf>1&&a[suf-1]<=a[suf]) suf--;
	if(suf==1){cout<<"0\n";return 0;}
	int ans=-0x3f3f3f3f;
	a[n+1]=1e9;
	for(int i=1;i<=n;i++){
		memset(g,0,sizeof(g));
		f[i][1][min(a[i],3)]=1;
		for(int len=2,j=i-1;j>=1&&len<L;j--,len++){
			if(len&1){
				for(int k=j,c1=1,c2=i-k;k<i;k+=2,c1+=2,c2-=2){
					f[i][len][0]|=((f[k][c1][1]|f[k][c1][2]|f[k][c1][3])&(g[c2][4]|g[c2][5]|g[c2][6]));
					f[i][len][1]|=((f[k][c1][0]|f[k][c1][2]|f[k][c1][3])&(g[c2][0]|g[c2][2]|g[c2][3]))|(f[k][c1][0]&&g[c2][6]);
					f[i][len][2]|=(f[k][c1][0]&(g[c2][1]|g[c2][4]))|(f[k][c1][1]&(g[c2][0]|g[c2][1]|g[c2][3]))|(f[k][c1][3]&g[c2][1]);
					f[i][len][3]|=(f[k][c1][0]&g[c2][5])|(f[k][c1][1]&g[c2][2])|(f[k][c1][2]&g[c2][1]);
				}
				for(int k=0;k<4;k++) if(f[i][len][k]){
					for(int p=0;p<=k;p++) dp[i][k]=max(dp[i][k],dp[j-1][p]+1);
				}
			}
			else{
				for(int k=j,c1=1,c2=i-k;k<i;k+=2,c1+=2,c2-=2){
					g[len][0]|=(f[k][c1][0]&f[i][c2][0]);
					g[len][1]|=(f[k][c1][0]&f[i][c2][1])|(f[k][c1][1]&f[i][c2][0]);
					g[len][2]|=(f[k][c1][0]&f[i][c2][2])|(f[k][c1][2]&f[i][c2][0]);
					g[len][3]|=(f[k][c1][0]&f[i][c2][3])|(f[k][c1][3]&f[i][c2][0]);
					g[len][4]|=(f[k][c1][1]&f[i][c2][3])|(f[k][c1][3]&f[i][c2][1])|(f[k][c1][1]&f[i][c2][1]);
					g[len][5]|=(f[k][c1][1]&f[i][c2][2])|(f[k][c1][2]&f[i][c2][1]);
					g[len][6]|=(f[k][c1][3]&f[i][c2][2])|(f[k][c1][2]&f[i][c2][3])|(f[k][c1][2]&f[i][c2][2])|(f[k][c1][3]&f[i][c2][3]);
				}
			}
		}
		if(i-(L+2)+1>=1){
			for(int k=0;k<4;k++){
				for(int p=0;p<=k;p++) dp[i][k]=max(dp[i][k],ma[i-(L+2)][p]+1);
			}
		}
		if(a[i]<=3){
			for(int p=0;p<=a[i];p++) dp[i][a[i]]=max(dp[i][a[i]],dp[i-1][p]+1);
		}
		if(i>=suf-1){
			for(int p=0;p<=min(3,a[i+1]);p++) ans=max(ans,dp[i][p]+n-i);
		}
		for(int p=0;p<4;p++) ma[i][p]=max(ma[i-1][p],dp[i][p]);
	}
	if(ans<=0) cout<<"-1\n";
	else cout<<(n-ans)/2<<"\n";
	return 0;
}