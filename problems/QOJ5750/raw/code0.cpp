#include <bits/stdc++.h>
#include <cassert>
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
ll a[100005];
int vis[100005];
void solve(int Ca){
	cin>>n;
	for(int i=0;i<n;i++) cin>>a[i],vis[i]=0;
	ll ans0=0,ans1=0,ans2=0;
	for(int i=0;i<n;i++) if(a[i]&&!vis[i]){
		vis[i]=1;
		int u=(i+a[i])%n;
		ll sum=a[i],flag=0;
		if(a[i]&1) flag=1;
		while(u!=i){
			vis[u]=1;
			sum+=a[u];
			if(a[u]&1) flag=1;
			u=(u+a[u])%n;
		}
		assert(sum%n==0);
		ll tmp=sum/n;
		if(flag) ans2+=tmp;
		else if(tmp%2==0&&(n&1)) ans1+=tmp/2,ans0+=tmp/2;
		else{
			if(i&1) ans1+=tmp;
			else ans0+=tmp;
		}
	}
	cout<<ans0<<" "<<ans1<<" "<<ans2<<"\n";
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