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
int n,ca,fat[500005];
ll de[500005];
vector<int>e[500005];
int res[1000005];
vector<pair<ll,int> >p[500005];
ll LCM(ll u,ll v){
	if(u==0) return v;
	if(u>1e18) return 2e18;
	__int128 tmp=(__int128)u*v/__gcd(u,v);
	if(tmp>1e18) return 2e18;
	return tmp;
}
void dfs(int u,ll lcm){
	if(!p[u].size()) return;
	if(!e[u].size()){
		for(auto x:p[u]) res[x.second]=u;
		return;
	}
	ll x=LCM(lcm,e[u].size());
	if(x==lcm){
		int v=e[u][(p[u][0].first+de[u])%e[u].size()];
		swap(p[u],p[v]),dfs(v,x);
		return;
	}
	for(auto x:p[u]){
		int v=e[u][(x.first+de[u])%e[u].size()];
		p[v].emplace_back(x);
	}
	p[u].clear();
	for(auto v:e[u]) dfs(v,x);
}
void solve(int Ca){
	cin>>n>>ca;
	for(int i=1;i<=n;i++) e[i].clear(),p[i].clear();
	for(int i=2,u;i<=n;i++) cin>>u,fat[i]=u,e[u].emplace_back(i);
	for(int i=2,u;i<=n;i++) cin>>u,de[i]=de[fat[i]]+u;
	for(ll i=1,x;i<=ca;i++) cin>>x,p[1].emplace_back(x,i);
	dfs(1,0);
	for(int i=1;i<=ca;i++) cout<<res[i]<<" \n"[i==ca];
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