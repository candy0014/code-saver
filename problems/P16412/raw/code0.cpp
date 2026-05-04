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
int n,cnt[500005];
void solve(int Ca){
	cin>>n;
	int ma=0;
	for(int i=1,u;i<=n;i++) cin>>u,cnt[min(u,n+2)]++,ma=max(ma,u);
	int mex=0;
	while(cnt[mex]) mex++;
	ll res=0;
	for(int i=0;i<=n+2;i++) if(cnt[i]){
		int x=i;
		if(i==n+2) x=ma;
		if(cnt[i]>=2) res=max(res,1ll*x*mex);
		else{
			int tmp=mex;
			if(i<mex) tmp=i;
			res=max(res,1ll*x*tmp);
		}
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
//	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}