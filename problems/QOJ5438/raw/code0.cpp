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
ll x,y;
vector<int>g;
int flag;
void dfs(ll s1,ll s2){
	if(s1>s2||flag) return;
	if(s1==s2){
		for(int i=1;i<=s1;i++) g.emplace_back(1);
		flag=1;
		return;
	}
	ll t=floor(sqrt(0.25+s2+s2)-0.5);
	for(int i=0;i<=1000;i++){
		ll p=t-i;
		if(p<=1) break;
		g.emplace_back(p);
		dfs(s1-p,s2-p*(p+1)/2);
		if(flag) return;
		g.pop_back();
	}
}
void work(ll _x){
	x=_x,y=x*(x+1)/4,g.clear(),flag=0;
	dfs(x,y);
}
ll n,m;
int a[1000005];
mt19937 rd(time(0));
void solve(int Ca){
	cin>>n>>m;
	// n=1,m=rd()%1000000+1;
	if(n*(n+1)/2%2&&m*(m+1)/2%2){cout<<"No\n";return;}
	if(n*(n+1)/2%2) work(m);
	else work(n);
	int c=0,flag=0;
	for(auto x:g){
		while(x--) a[++c]=flag;
		flag^=1;
	}
	cout<<"Yes\n";
	// if(!g.size()){cout<<m<<"\n";exit(0);}
	if(n*(n+1)/2%2){
		for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cout<<a[j]<<" \n"[j==m];
	}
	else{
		for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cout<<a[i]<<" \n"[j==m];
	}
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