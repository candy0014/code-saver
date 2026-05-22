#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
const ll mod=7000007,base=233;
const ll inf=2e9;
const int N=2e5+5;
const int M=2e5+5;
const int V=2e6+5;
int n,f[500005],dp[500005];
ll ha[500005],pw[500005];
ll Hash(int l,int r){return (ha[r]-ha[l-1]*pw[r-l+1]%mod+mod)%mod;}
string s;
bitset<mod>mp;
int tmp[500005];
void solve(int Ca){
	cin>>n>>s,s=" "+s;
	for(int i=1;i<=n;i++) f[i]=1;
	pw[0]=1;
	for(int i=1;i<=n;i++) pw[i]=pw[i-1]*base%mod,ha[i]=(ha[i-1]*base+s[i])%mod;
	for(int len=2;;len++){
		memset(dp,0,sizeof(dp)),mp.reset();
		int flag=0;
		for(int i=1;i<=n-len+2;i++) tmp[i]=Hash(i,i+len-2);
		for(int i=n-len*(len+1)/2+1;i>=1;i--){
			if(f[i+len]) mp[tmp[i+len]]=1;
			if(mp[tmp[i]]||mp[tmp[i+1]]) dp[i]=1,flag=1;
		}
		if(!flag){cout<<len-1<<"\n";return;}
		for(int i=1;i<=n;i++) f[i]=dp[i];
	}
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