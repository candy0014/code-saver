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
int n,d;
vector<int>res;
bool check(int x,int y){return (x^y)>abs(x-y);}
void solve(int Ca){
	cin>>n,d=__lg(n),res.clear();
	if(n==1){cout<<"1\n";return;}
	if(!(n&(n+1))){cout<<"-1\n";return;}
	for(int i=1;i<=n;i++) if(i!=(1<<d)) res.emplace_back(i);
	sort(res.begin(),res.end(),[&](int u,int v){
		int tu=__builtin_popcount(u),tv=__builtin_popcount(v);
		if(tu!=tv) return tu>tv;
		return u>v;
	});
	int f=0;
	for(int i=0;i<(int)res.size();i++){
		if(i&&!check(res[i-1],res[i])) cout<<(1<<d)<<" ",f=1;
		cout<<res[i]<<" ";
	}
	if(!f) cout<<(1<<d);
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