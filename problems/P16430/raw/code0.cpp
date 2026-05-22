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
int n,k,a[1005],b[1005];
void solve(int Ca){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	__int128 res=1;
	for(int i=1;i<=25;i++) res*=10;
	for(int i=1;i<=n;i++){
		vector<ll>p;
		for(int j=1;j<=n;j++) if(a[j]<=a[i]) p.emplace_back(1ll*(a[i]-a[j])*b[j]);
		if(p.size()<k) continue;
		sort(p.begin(),p.end());
		__int128 sum=0;
		for(int j=0;j<k;j++) sum+=p[j];
		res=min(res,sum);
	}
	if(res==0){cout<<"0\n";return;}
	stack<int>ans;
	while(res)ans.push(res%10),res/=10;
	while(!ans.empty()) cout<<ans.top(),ans.pop();
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
//	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}