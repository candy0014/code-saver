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
vector<int>p;
void solve(int Ca){
	ll n;cin>>n;
	for(auto x:p) if(n-x>=0&&(n-x)%12==0){cout<<x<<" "<<n-x<<"\n";return;}
	cout<<"-1\n";
}
int main(){
	#ifdef ONLINE_JUDGE
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	#endif
	#ifndef ONLINE_JUDGE
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	for(int i=0;i<=9;i++) p.emplace_back(i);
	p.emplace_back(11),p.emplace_back(22);
	int Ca=1;
	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}