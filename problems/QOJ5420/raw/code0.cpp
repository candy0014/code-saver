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
int n,a[1000005],sum[1000005],tag[1000005];
vector<int>p;
void solve(int Ca){
	cin>>n;
	int ca=1,cb=1;
	for(int i=1;i<=n;i++){
		cin>>a[i],tag[i]=0;
		if(a[i]==0) a[i]=1,tag[i]=1;
		if(a[i]==1) ca++,cb++;
		else cb--;
		sum[i]=sum[i-1]+a[i];
	}
	for(int i=1;i<=n;i++) if(sum[i]<0){cout<<"-1\n";return;}
	int mi=1e9,cnt=0;
	for(int i=n;i>=1;i--){
		mi=min(mi,sum[i]);
		if(tag[i]){
			if(mi>=2) mi-=2,cnt++;
			else break;
		}
	}
	int ra=0,rb=1;
	for(int i=0;i<=cnt;i++){
		int ta=ca-i,tb=cb-i*2;
		if(1ll*ta*rb>1ll*ra*tb) ra=ta,rb=tb;
	}
	int g=__gcd(ra,rb);
	cout<<ra/g<<" "<<rb/g<<"\n";
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