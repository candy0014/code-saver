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
int n;
ll a[1000005],b[1000005];
void solve(int Ca){
	cin>>n;
	ll sum=0;
	for(int i=1;i<=n;i++) cin>>a[i],sum+=a[i];
	if(sum%n){cout<<"-1\n";return;}
	sum/=n;
	for(int i=1;i<=n;i++) a[i]-=sum;
	ll res=0;
	for(int i=1;i<n;i++){
		b[i]=-a[i],a[i+1]+=a[i];
		if(b[i]<0){cout<<"-1\n";return;}
	}
	for(int i=1;i<n;i++) res+=max(0ll,b[i]-b[max(0,i-2)]);
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