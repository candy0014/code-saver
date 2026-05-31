#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
const ll mod=1e9+9;
const ll inf=2e9;
const int N=2e5+5;
const int M=2e5+5;
const int V=2e6+5;
ll n,m;
ll ksm(ll u,ll v=mod-2){ll tmp=1;u%=mod;while(v) tmp=tmp*((v&1)?u:1)%mod,u=u*u%mod,v>>=1;return tmp;}
void solve(int Ca){
	cin>>n>>m;
	ll g=n*(n-1)/2;
	if(m>g){cout<<"0\n";return;}
	ll tmp=1;
	for(ll i=g;i>=g-m+1;i--) tmp=tmp*(i%mod)%mod;
	for(int i=1;i<=m;i++) tmp=tmp*ksm(i)%mod;
	for(int i=1;i<=n;i++) tmp=tmp*i%mod;
	cout<<tmp<<"\n";
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