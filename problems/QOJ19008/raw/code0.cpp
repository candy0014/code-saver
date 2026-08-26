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
int n;
string s;
int nex[5000005][10];
int dp[512][10],pre[512][10];
void solve(int Ca){
	cin>>n>>s,s=" "+s;
	for(int i=0;i<10;i++) nex[n][i]=nex[n+1][i]=n+1;
	for(int i=n;i>=1;i--){
		for(int j=0;j<10;j++) nex[i-1][j]=nex[i][j];
		nex[i-1][s[i]-'0']=i;
	}
	memset(dp,0x3f3f3f3f,sizeof(dp));
	dp[1][0]=0;
	int ma=0,mak=0,mat=0;
	for(int i=0;i<512;i++) for(int t=0;t<9;t++) if(dp[i][t]<=n){
		if(__builtin_popcount(i)-1>ma) ma=__builtin_popcount(i)-1,mak=i,mat=t;
		for(int j=0;j<10;j++) if(!((i>>((j+t)%9))&1)){
			int tmp=i|(1<<((j+t)%9)),x=nex[dp[i][t]][j];
			if(x<=dp[tmp][(j+t)%9]){
				dp[tmp][(j+t)%9]=x,pre[tmp][(j+t)%9]=j;
			}
		}
	}
	vector<int>res;
	for(int i=1;i<=ma;i++){
		res.emplace_back(dp[mak][mat]);
		int tmp=pre[mak][mat];
		mak^=(1<<mat),mat=(mat+9-tmp)%9;
	}
	cout<<ma;
	for(int i=ma-1;i>=0;i--) cout<<" "<<res[i];cout<<"\n";
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