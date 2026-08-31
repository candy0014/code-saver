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
int n,k,m;
ll c,d,a[200005],b[200005],sum[200005];
bool check(ll x){
	for(int i=1;i<=n;i++) b[i]=max(0ll,x-a[i]),sum[i]=0;
	for(int i=1;i<=n;i++){
		if(!b[i]){sum[1]++;continue;}
		if(b[i]<=c){sum[max(1,i-m+1)]++,sum[i+1]--;continue;}
		if(b[i]>c+(min(i,m)-1)*d) continue;
		sum[max(1,i-m+1)]++,sum[i-(b[i]-c-1)/d]--;
	}
	for(int i=1;i<=n;i++){
		sum[i]+=sum[i-1];
		if(sum[i]>=k) return 1;
	}
	return 0;
}
void solve(int Ca){
	cin>>n>>k>>m>>c>>d;
	for(int i=1;i<=n;i++) cin>>a[i];
	ll l=0,r=2e18,mid,res=0;
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid)) res=mid,l=mid+1;
		else r=mid-1;
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