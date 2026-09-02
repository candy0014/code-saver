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
int n,ca;
int L[105],R[105],a[105];
void solve(int Ca){
	cin>>n>>ca;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) L[i]=0,R[i]=2e9;
	for(int i=1,u,l,r;i<=ca;i++) cin>>u>>l>>r,L[u]=max(L[u],l),R[u]=min(R[u],r);
	ll res=0;
	for(int i=1;i<=n;i++){
		if(L[i]>R[i]){cout<<"-1\n";return;}
		if(a[i]<L[i]) res+=L[i]-a[i];
		if(a[i]>R[i]) res+=a[i]-R[i];
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