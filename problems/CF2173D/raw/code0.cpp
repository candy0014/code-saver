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
ll n,k;
int dp[40][40][2];
void Min(int &u,int v){u=min(u,v);}
void solve(int Ca){
	cin>>n>>k,n<<=1;
	if(k>=30){cout<<__builtin_popcount(n)-1+k<<"\n";return;}
	memset(dp,0x3f3f3f3f,sizeof(dp)),dp[0][0][0]=0;
	for(int i=0;i<32;i++){
		int x=((n>>(i+1))&1);
		for(int j=0;j<=i;j++) for(int k:{0,1}) if(dp[i][j][k]<=100){
			Min(dp[i+1][j][(x+k)>>1],dp[i][j][k]+((x+k)&1));
			Min(dp[i+1][j+1][(x+k+1)>>1],dp[i][j][k]+((x+k+1)&1));
		}
	}
	int res=1e9;
	for(int i=0;i<=k;i++) res=min(res,dp[32][i][0]);
	cout<<__builtin_popcount(n)-res+k<<"\n";
}
int main(){
	#ifdef ONLINE_JUDGE
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	#endif
	#ifndef ONLINE_JUDGE
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	
	int Ca=1;
	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}