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
string s;
int n,sum[55];
void solve(int Ca){
	cin>>s,n=s.length(),s=" "+s;
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+s[i]-'0';
	int res=sum[n];
	for(int i=1;i<=n;i++) for(int j=i;j<=n;j++){
		res=min(res,(j-i+1)-(sum[j]-sum[i-1])+sum[i-1]+sum[n]-sum[j]);
	}
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
	
	int Ca=1;
//	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}