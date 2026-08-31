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
int n,m,a[1000005];
void solve(int Ca){
	cin>>n,m=1<<n;
	for(int i=0;i<m;i++) cin>>a[i];
	sort(a,a+m,[&](int u,int v){return u>v;});
	ll res=-1e18;
	for(int i=0;i<=n;i++){
		ll tmp=0;
		for(int j=0;j<(1<<i);j++) tmp+=a[j];
		res=max(res,tmp);
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