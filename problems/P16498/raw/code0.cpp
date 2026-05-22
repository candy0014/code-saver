#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
const ll mod=998244353;
const ll inf=2e9;
const int N=2e5+5;
const int M=2e5+5;
const int V=2e6+5;
int n,m,a[305][305],dp[305][305];
void solve(int Ca){
	cin>>n>>m;
	for(int i=1;i<=n;i++) for(int j=0;j<m;j++) cin>>a[i][j];
	for(int i=1;i<=n;i++) for(int j=0;j<m;j++) dp[i][j]=1e9;
	for(int j=0;j<m;j++) dp[1][j]=min(j,m-j);
	for(int i=2;i<=n;i++){
		for(int j=0;j<m;j++){
			int flag=0;
			for(int k=0;k<m;k++) if(a[i-1][k]>a[i][(j+k)%m]){flag=1;break;}
			if(flag) continue;
			for(int k=0;k<m;k++){
				int jj=(j+k)%m;
				dp[i][(j+k)%m]=min(dp[i][jj],dp[i-1][k]+min(jj,m-jj));
			}
		}
	}
	int res=1e9;
	for(int j=0;j<m;j++) res=min(res,dp[n][j]);
	if(res>1e8) res=-1;
	cout<<res<<"\n";
}
int main(){
	#ifdef ONLINE_JUDGE
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	#endif
	#ifndef ONLINE_JUDGE
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	
	int ID,Ca=1;
	cin>>ID>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}