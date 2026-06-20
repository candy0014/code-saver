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
ll l[200005],r[200005];
void solve(int Ca){
	cin>>n;
	ll sl=0,sr=0;
	for(int i=1,u;i<=n;i++){
		cin>>u,l[i]=max(0,u*1000000-500000),r[i]=u*1000000+499999;
		sl+=l[i],sr+=r[i];
	}
	if(sl>100000000||sr<100000000){cout<<"No\n";return;}
	cout<<"Yes\n";
	ll tmp=100000000-sl;
	for(int i=1;i<=n;i++){
		ll x=l[i],t=min(tmp,r[i]-x);
		tmp-=t,cout<<x+t<<" ";
	}
	cout<<"\n";
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
