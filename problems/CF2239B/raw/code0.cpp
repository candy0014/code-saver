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
int n,d;
ll a[400005],b[400005];
void solve(int Ca){
	cin>>n>>d;
	for(int i=1;i<=n;i++) cin>>a[i],a[i+n]=a[i];
	for(int i=1;i<=n+n;i++) b[i]=b[i-1]+a[i];
	ll res=0;
	for(int i=d+1;i<=d+n;i++) res+=max(0ll,a[i]*d*2-(b[i+d]-b[i-d-1]-a[i]));
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