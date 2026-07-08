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
int n,suf[200005],a[200005],tag[200005];
void solve(int Ca){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	suf[n]=0;
	for(int i=n;i>=1;i--){
		if(a[i]==3) suf[i]=suf[i+1]-1;
		else suf[i]=suf[i+1]+1;
	}
	int mi=suf[n];
	for(int i=n-1;i>=2;i--){
		if(suf[i]>=mi) tag[i]=1;
		else tag[i]=0,mi=suf[i];
	}
	int now=0;
	for(int i=1;i<=n-2;i++){
		if(a[i]==1) now++;
		else now--;
		if(now>=0&&tag[i+1]){cout<<"YES\n";return;}
	}
	cout<<"NO\n";
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