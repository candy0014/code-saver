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
int n,m,k,b;
void solve(int Ca){
	cin>>n>>m>>k>>b;
	int res=0,cnt=0;
	for(int i=1;i<=n;i++){
		int s1=0,s2=0;
		for(int j=1,u;j<=m;j++){
			cin>>u,s1+=u;
			if(u<=0) s2+=u+1;
			else s2+=u-1;
		}
		if(s1>=k) res++;
		else if(s2>=k) cnt++;
	}
	cout<<res+min(cnt,b)<<"\n";
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