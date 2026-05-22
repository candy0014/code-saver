#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m,h[50005];
vector<ll>s[105];
ll dp[105][50005],f[50005],now;
void solve(int l,int r,int lc,int rc){
	if(l>r) return;
	int mid=(l+r)>>1;
	ll mi=8e18,mik=lc;
	for(int k=max(1,lc-mid);k==1||(k<(int)s[now].size()&&mid+k<=rc);k++){
		ll tmp=max(1ll,dp[now+1][min(m,mid+k)]-h[min(m,mid+k)])+s[now][k];
		if(tmp<mi) mi=tmp,mik=mid+k;
	}
	dp[now][mid]=min((ll)1e18,mi),solve(l,mid-1,lc,mik),solve(mid+1,r,mik,rc);
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++) cin>>h[i];
	for(int i=1,u,v;i<=n;i++){
		cin>>u,s[i].emplace_back(0);
		while(u--) cin>>v,s[i].emplace_back(v);
		sort(s[i].begin(),s[i].end());
		for(int j=1;j<(int)s[i].size();j++) s[i][j]+=s[i][j-1];
		for(int j=1;j<(int)s[i].size();j++) s[i][j]+=s[i][j-1];
	}
	for(int j=1;j<m;j++) dp[n+1][j]=4e18;
	for(int i=n;i>=1;i--) now=i,solve(1,m,1,m);
	cout<<dp[1][1]<<"\n";
	return 0;
}
