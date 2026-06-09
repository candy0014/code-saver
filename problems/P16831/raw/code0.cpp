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
int n,son[1000005][2];
bool dfs(int u){
	if(!u) return 1;
	if(!son[u][0]&&!son[u][1]) return 0;
	return dfs(son[u][0])||dfs(son[u][1]);
}
void solve(int Ca){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>son[i][0]>>son[i][1];
	if(dfs(1)) cout<<"Yes\n";
	else cout<<"No\n";
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