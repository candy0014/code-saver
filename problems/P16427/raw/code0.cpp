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
ll n,x;
void solve(int Ca){
	cin>>n>>x;
	if(x==1){
		if(!(n&(n-1))) cout<<"Yes\n";
		else cout<<"No\n";
		return;
	}
	ll cnt=0,m=n;
	while(m) cnt+=m%x,m/=x;
	for(int i=0;(1<<i)<=n;i++) if((1ll<<i)>=cnt&&((1ll<<i)-cnt)%(x-1)==0){cout<<"Yes\n";return;}
	cout<<"No\n";
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