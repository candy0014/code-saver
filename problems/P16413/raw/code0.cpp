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
int n,k,a[200005],b[200005];
ll pre[200005],suf[200005];
void solve(int Ca){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	pre[0]=suf[n+1]=1e18;
	for(int i=1;i<=n;i++) pre[i]=min(pre[i-1],b[i]-1ll*i*k);
	for(int i=n;i>=1;i--) suf[i]=min(suf[i+1],b[i]+1ll*i*k);
	for(int i=1;i<=n;i++) pre[i]+=1ll*i*k,suf[i]-=1ll*i*k;
	ll res=0;
	for(int i=1;i<=n;i++) res+=min(pre[a[i]],suf[a[i]]);
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