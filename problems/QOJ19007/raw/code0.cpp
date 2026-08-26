#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
const ll mod=10000000000002137ll;
const ll inf=2e9;
const int N=2e5+5;
const int M=2e5+5;
const int V=2e6+5;
ll ksm(ll u,ll v=mod-2){ll tmp=1;u%=mod;while(v) tmp=(__int128)tmp*((v&1)?u:1)%mod,u=(__int128)u*u%mod,v>>=1;return tmp;}
int n,ca;
template <class T> struct BIT{
	int n;
	T sum[N];
	void init(int x){n=x;for(int i=1;i<=n;i++) sum[i]=0;}
	void add(int x,T k){while(x<=n) sum[x]=(sum[x]+k)%mod,x+=(x&(-x));}
	T _query(int x){T tmp=0;while(x) tmp=(tmp+sum[x])%mod,x-=(x&(-x));return tmp;}
	T query(int l,int r){return (_query(r)-_query(l-1)+mod)%mod;}
};
BIT<ll>b;
ll a[N];
void solve(int Ca){
	cin>>n>>ca;
	b.init(n);
	for(int i=1,u;i<=n;i++) cin>>u,a[i]=ksm(u),b.add(i,a[i]);
	while(ca--){
		int op,x,y;
		cin>>op>>x>>y;
		if(op==0){
			if(b.query(x,y)<=n) cout<<"yes\n";
			else cout<<"no\n";
		}
		else{
			b.add(x,(ksm(y)-a[x]+mod)%mod),a[x]=ksm(y);
		}
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
//	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}