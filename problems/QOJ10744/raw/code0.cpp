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
int n,k,a[55][55];
void solve(int Ca){
	cin>>n>>k;
	if(k<n||k>n*(n-1)+1){cout<<"No\n";return;}
	cout<<"Yes\n";
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) a[i][j]=0;
	int tot=0;
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if(i!=j&&tot+1<k) a[i][j]=++tot;
	a[1][1]=++tot;
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++){
		if(!a[i][j]) a[i][j]=++tot;
		cout<<a[i][j]<<" \n"[j==n];
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