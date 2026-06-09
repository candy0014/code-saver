#include <bits/stdc++.h>
using namespace std;
int n,li[1000005],tot;
int a[1000005],b[1000005],t[1000005],id[1000005];
int dp[1000005][3][3];
pair<int,int>h[1000005][3];
bool check(pair<int,int>u,pair<int,int>v){
	if(u.second<=v.first||v.second<=u.first) return 1;
	return 0;
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	cin>>n,n+=2;
	for(int i=3;i<=n;i++){
		cin>>a[i]>>t[i]>>b[i],id[i]=i;
		h[i][0]=make_pair(a[i],b[i]);
		h[i][1]=make_pair(t[i],b[i]);
		h[i][2]=make_pair(a[i],t[i]);
	}
	id[1]=1,id[2]=2;
	sort(id+1,id+n+1,[&](int u,int v){return t[u]<t[v];});
	memset(dp,-0x3f3f3f3f,sizeof(dp));
	dp[2][0][0]=0;
	for(int ii=2;ii<n;ii++){
		int i=id[ii+1],p=id[ii],q=id[ii-1];
		for(int x=0;x<3;x++) for(int y=0;y<3;y++) if(dp[ii][x][y]>=0){
			for(int z=0;z<3;z++){
				if(check(h[i][z],h[p][x])&&check(h[i][z],h[q][y])){
					dp[ii+1][z][x]=max(dp[ii+1][z][x],dp[ii][x][y]+h[i][z].second-h[i][z].first);
				}
			}
		}
	}
	int ans=-1;
	for(int i=0;i<3;i++) for(int j=0;j<3;j++) ans=max(ans,dp[n][i][j]);
	cout<<ans<<"\n";
	return 0;
}