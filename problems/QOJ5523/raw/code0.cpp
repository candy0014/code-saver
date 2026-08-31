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
int n,m,e[30],res[30],dp[16777216];
void solve(int Ca){
	cin>>n;
	for(int i=0;i<n;i++){
		string str;cin>>str;
		for(int j=0;j<n;j++) if(str[j]=='1') e[i]|=(1<<j);
	}
	dp[1]=1,m=(1<<n)-1;
	for(int i=1;i<(1<<n);i++){
		int t=0;
		for(int j=0;j<n;j++) if((dp[i]>>j)&1) t|=e[j];
		t&=m^i;
		for(int j=0;j<n;j++) if((t>>j)&1) dp[i|(1<<j)]|=(1<<j);
	}
	for(int i=1;i<(1<<n);i++){
		int j=(m^i)|1;
		int x=dp[i],y=dp[j];
		for(int j=0;j<n;j++) if((x>>j)&1) res[j]|=y;
	}
	for(int i=0;i<n;i++,cout<<"\n") for(int j=0;j<n;j++) cout<<((res[i]>>j)&1);
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
//	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}