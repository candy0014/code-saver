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
ll n;
string F(ll x){
	string s="";
	while(x) s+=char(x%10+'0'),x/=10;
	sort(s.begin(),s.end());
	return s;
}
void solve(int Ca){
	cin>>n;
	int cnt=0;
	for(int i=2;i<=9;i++) if(n%i==0&&F(n)==F(n/i)) cnt++;
	cout<<cnt<<"\n";
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