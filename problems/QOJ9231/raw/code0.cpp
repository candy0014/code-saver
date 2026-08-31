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
int n,a[200005];
ll sum[200005];
void solve(int Ca){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],sum[i]=sum[i-1]+a[i];
	int res=0;
	for(int i=max(1,n/2-500);i<=min(n,n/2+500);i++){
		ll tmp=1ll*i*i;
		for(int j=i;j<=n;j++) res+=(sum[j]-sum[j-i]==tmp);
	}
	for(int i=1;i<=min(100,max(1,n/2-500)-1);i++){
		ll tmp=1ll*i*i;
		for(int j=i;j<=n;j++) res+=(sum[j]-sum[j-i]==tmp);
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