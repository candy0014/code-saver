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
ll ksm(ll u,ll v=mod-2){ll tmp=1;u%=mod;while(v) tmp=tmp*((v&1)?u:1)%mod,u=u*u%mod,v>>=1;return tmp;}
ll n,a[2005],b[2005],val[2005][2005];
ll li[4000005],tot;
template <class T> struct BIT{
	int n;
	T sum[N];
	void init(int x){n=x;for(int i=1;i<=n;i++) sum[i]=0;}
	void add(int x,T k){while(x<=n) sum[x]+=k,x+=(x&(-x));}
	T _query(int x){T tmp=0;while(x) tmp+=sum[x],x-=(x&(-x));return tmp;}
	T query(int l, int r){return _query(r)-_query(l-1);}
};
BIT<int>p;
void solve(int Ca){
	cin>>n,tot=0;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) li[++tot]=a[i]*b[j];
	sort(li+1,li+tot+1),tot=unique(li+1,li+tot+1)-li-1;
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) val[i][j]=lower_bound(li+1,li+tot+1,a[i]*b[j])-li;
	p.init(tot);
	ll res=0;
	for(int i=1;i<=n;i++){
		int cnt=0;
		for(int j=1;j<i;j++) cnt+=(a[j]>a[i]);
		for(int j=1;j<=n;j++){
			res=(res+p.query(val[i][j]+1,tot)-cnt)%mod;
		}
		for(int j=1;j<=n;j++) p.add(val[i][j],1);
	}
	cout<<res*ksm(n)%mod*ksm(n-1)%mod<<"\n";
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