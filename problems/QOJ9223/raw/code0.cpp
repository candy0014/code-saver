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
ll n,k,m,a[200005];
void solve(int Ca){
	cin>>n>>k>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		if(k&1){
			if(a[i]!=m) continue;
			if(i-1>=k/2&&n-i>=k/2){cout<<"TAK\n";return;}
		}
		else{
			if(a[i]>m) continue;
			ll x=m*2-a[i];
			int it=lower_bound(a+i+1,a+n+1,x)-a;
			if(it<=n&&a[it]==x&&i>=k/2&&n-it+1>=k/2){cout<<"TAK\n";return;}
		}
	}
	cout<<"NIE\n";
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