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
int x,y;
void solve(int Ca){
	cin>>x>>y;
	if(x*2<y||x>y){cout<<"-1\n";return;}
	x=y-x;
	for(int i=1;i<=x*2;i++) cout<<"s";
	for(int i=1;i<=x*2;i++) cout<<"ys";
	for(int i=1;i<=y-2*x;i++) cout<<"sys";
	for(int i=1;i<=y;i++) cout<<"u";
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