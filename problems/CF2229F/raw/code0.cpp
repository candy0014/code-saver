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
int n,k;
ll a[20];
int dp[500005];
ll f[500005];
bool check(ll x){
	for(int i=1;i<(1<<n);i++){
		dp[i]=-1;
		for(int j=0;j<n;j++) if((i>>j)&1){
			int p=i^(1<<j);
			ll tmp=f[p]+a[j],flag=0;
			if(tmp>=x) tmp=0,flag=1;
			if(dp[p]+flag>dp[i]) dp[i]=dp[p]+flag,f[i]=tmp;
			else if(dp[p]+flag==dp[i]) f[i]=max(f[i],tmp);
		}
	}
	return dp[(1<<n)-1]>=k;
}
void solve(int Ca){
	cin>>n>>k;
	for(int i=0;i<n;i++) cin>>a[i];
	sort(a,a+n);n--;
	ll l=0,r=2e10,mid,res=0;
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid)) l=mid+1,res=mid;
		else r=mid-1;
	}
	cout<<res+a[n]<<"\n";
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