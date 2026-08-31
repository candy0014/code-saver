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
int n,ca,a[200005];
int cnt0,cnt1,flag;
template <class T> struct BIT{
	int n;
	T sum[N];
	void init(int x){n=x;for(int i=1;i<=n;i++) sum[i]=0;}
	void add(int x,T k){while(x<=n) sum[x]+=k,x+=(x&(-x));}
	T _query(int x){T tmp=0;while(x) tmp+=sum[x],x-=(x&(-x));return tmp;}
	T query(int l, int r){return _query(r)-_query(l-1);}
};
BIT<int>b;
void change(int x,int y){
	if(x>1) cnt0-=a[x-1]>a[x];
	if(x<n) cnt0-=a[x]>a[x+1];
	cnt1-=(a[x]+x)&1;
	a[x]=y;
	if(x>1) cnt0+=a[x-1]>a[x];
	if(x<n) cnt0+=a[x]>a[x+1];
	cnt1+=(a[x]+x)&1;
}
void solve(int Ca){
	cin>>n>>ca;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=2;i<=n;i++) cnt0+=a[i-1]>a[i];
	for(int i=1;i<=n;i++) cnt1+=(a[i]+i)&1;
	b.init(n);
	for(int i=n;i>=1;i--) flag^=b._query(a[i])&1,b.add(a[i],1);
	while(ca--){
		int x,y,u,v;cin>>x>>y,u=a[x],v=a[y];
		change(x,v),change(y,u),flag^=1;
		if(flag) cout<<n<<"\n";
		else if(!cnt0) cout<<"-1\n";
		else if(!cnt1) cout<<n-2<<"\n";
		else cout<<n-1<<"\n";
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