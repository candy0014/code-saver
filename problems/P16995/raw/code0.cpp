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
ll n,k,a[1000005],b[1000005];
void solve(int Ca){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i],b[i]=a[i];
	for(int i=62;i>=0;i--){
		ll ma=-1,mak=0,t=(1ull<<(i+1))-1;
		for(int j=1;j<=n;j++) if((a[j]&t)>ma) ma=a[j]&t,mak=j;
		if((ma>>i)&1) continue;
		ma=(1ll<<i)-ma;
		if(ma<=k) k-=ma,a[mak]+=ma;
	}
	for(int i=0;i<=62;i++){
		for(int j=1;j<=n;j++) if(!((a[j]>>i)&1)){
			if(k>=(1ll<<i)) k-=(1ll<<i),a[j]+=(1ll<<i);
			else{a[j]+=k,i=63;break;}
		}
	}
	ll res=0;
	for(int i=1;i<=n;i++) res|=a[i];
	cout<<res<<"\n";
	for(int i=1;i<=n;i++) cout<<a[i]-b[i]<<" \n"[i==n];
}
int main(){
	#ifdef ONLINE_JUDGE
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	#endif
	#ifndef ONLINE_JUDGE
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	
	int ID,Ca=1;
	cin>>ID>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}