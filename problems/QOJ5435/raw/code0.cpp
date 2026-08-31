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
ll n,d,a[5005],b[5005];
ll work(ll l){
	ll res=0;
	for(int i=1;i<=n;i++) b[i]=max(min(a[i],l+d),l);
	for(int i=2;i<=n;i++) res+=abs(b[i]-b[i-1]);
	return res;
}
void solve(int Ca){
	cin>>n>>d;
	for(int i=1;i<=n;i++) cin>>a[i];
	ll res=0;
	for(int i=1;i<=n;i++) res=max({res,work(a[i]),work(a[i]-d)});
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