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
ll n,a[100005],b[100005];
void solve(int Ca){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	ll ma=0,sum=0;
	for(int i=1;i<=n;i++){
		cin>>b[i];
		if(a[i]>b[i]) swap(a[i],b[i]);
		ma=max(ma,a[i]),sum+=b[i];
	}
	ll res=ma+sum;
	for(int i=1;i<=n;i++){
		res=max(res,sum-b[i]+a[i]+max(ma,b[i]));
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
	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}