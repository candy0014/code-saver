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
ll d[500005],c[500005],res[500005];
void solve(int Ca){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>d[i]>>c[i];
	ll now=d[n];
	for(int i=n;i>=1;i--){
		now=min(now,d[i]);
		res[i]=now-c[i]+1,now-=c[i];
	}
	if(res[1]<=0){cout<<"No\n";return;}
	cout<<"Yes\n";
	for(int i=1;i<=n;i++) cout<<res[i]<<" \n"[i==n];
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