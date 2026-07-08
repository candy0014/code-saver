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
string s,t;
int dp[5005][5005];
int nexs[5005][12],nextt[5005][12];
void Max(int &u,int v){u=max(u,v);}
void solve(int Ca){
	cin>>s>>t,s=" "+s,t=" "+t;
	int sx=0,tx=0;
	for(int i=1;s[i];i++){
		sx=(sx+s[i]-'0')%10;
		int now=0;
		for(int j=0;j<10;j++) nexs[i][j]=0;
		for(int j=i;s[j];j++){
			now=(now+s[j]-'0')%10;
			if(!nexs[i][now]) nexs[i][now]=j;
		}
	}
	for(int i=1;t[i];i++){
		tx=(tx+t[i]-'0')%10;
		int now=0;
		for(int j=0;j<10;j++) nextt[i][j]=0;
		for(int j=i;t[j];j++){
			now=(now+t[j]-'0')%10;
			if(!nextt[i][now]) nextt[i][now]=j;
		}
	}
	if(sx!=tx){cout<<"-1\n";return;}
	for(int i=0;s[i];i++) for(int j=0;t[j];j++) dp[i][j]=-1e9;
	dp[0][0]=0;
	for(int i=0;s[i+1];i++) for(int j=0;t[j+1];j++) if(dp[i][j]>=0){
		for(int k=0;k<10;k++) if(nexs[i+1][k]&&nextt[j+1][k]) Max(dp[nexs[i+1][k]][nextt[j+1][k]],dp[i][j]+1);
	}
	int ma=-1;
	for(int i=1;s[i];i++) ma=max(ma,dp[i][t.length()-1]);
	for(int i=1;t[i];i++) ma=max(ma,dp[s.length()-1][i]);
	cout<<ma<<"\n";
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