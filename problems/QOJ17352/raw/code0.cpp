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
vector<int>e[3000005];
int sz[3000005],fat[3000005];
void dfs(int u,int fa){
	fat[u]=fa,sz[u]=1;
	for(auto v:e[u]) if(v!=fa) dfs(v,u),sz[u]+=sz[v];
}
bool F(ll x){return (x*(x+1)/2)&1;}
void solve(int Ca){
	cin>>n,n=(1<<n);
	for(int i=0;i<n;i++) e[i].clear();
	for(int i=1,u,v;i<n;i++) cin>>u>>v,e[u].emplace_back(v),e[v].emplace_back(u);
	dfs(0,0);
	ll al=F(n-1),res=0;
	for(int u=1;u<n;u++){
		ll sum=al;
		for(auto v:e[u]){
			if(v==fat[u]) sum^=F(n-sz[u]-1);
			else sum^=F(sz[v]);
		}
		if(sum) res^=u;
	}
	cout<<res<<"\n";
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
