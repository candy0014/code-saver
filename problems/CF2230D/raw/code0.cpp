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
int n,a[500005],b[500005],na[500005],nb[500005],vis[500005],ta[500005],tb[500005],g[500005];
void solve(int Ca){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	for(int i=1;i<=n+1;i++) vis[i]=n+1;
	for(int i=n;i>=1;i--) na[i]=vis[a[i]+1],vis[a[i]]=i,ta[i]=vis[1];
	for(int i=1;i<=n+1;i++) vis[i]=n+1;
	for(int i=n;i>=1;i--) nb[i]=vis[b[i]+1],vis[b[i]]=i,tb[i]=vis[1];
	for(int i=n;i>=1;i--){
		if(a[i]==b[i]){
			if(na[i]!=nb[i]||na[i]==n+1) g[i]=min(na[i],nb[i]);
			else if(na[i]) g[i]=g[na[i]];
		}
		else g[i]=i;
	}
	ll res=0;
	for(int i=1;i<=n;i++){
		if(ta[i]!=tb[i]||ta[i]==n+1){res+=min(ta[i],tb[i])-i;continue;}
		else res+=g[ta[i]]-i;
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