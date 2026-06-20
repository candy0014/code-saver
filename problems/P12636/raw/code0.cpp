#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,k,t,a[1000005],bn,b[1000005],res=6e18;
void print(){
	cout<<res<<"\n";
	for(int i=1;i<=bn;i++){
		b[i]+=res*t;
		if(b[i]<=0) cout<<"0 ";
		else cout<<(b[i]-1)/(k+t)+1<<" ";
	}
	cout<<"\n",exit(0);
}
ll sum[1000005];
ll check(ll x){
	for(int i=0;i<n;i++) sum[i]=0;
	ll l=x*n,r=l+n-1;
	for(int i=1;i<=n;i++){
		ll tmp;
		if(a[i]+l*t<=0) tmp=0;
		else tmp=(a[i]+l*t-1)/(k+t)+1;
		ll tt=(tmp*(k+t)-a[i])/t+1;
		sum[0]+=tmp;
		if(tt<=r) sum[tt-l]++;
	}
	for(int i=1;i<n;i++) sum[i]+=sum[i-1];
	for(int i=0;i<n;i++) if(sum[i]<=l+i) return l+i;
	return -1;
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>k>>t;bn=n;
	for(int i=1;i<=n;i++) cin>>b[i],a[i]=b[i];
	sort(a+1,a+n+1,[&](ll u,ll v){return u>v;});
	if(!k){
		for(int i=1;i<=n;i++) if(a[i]>0){cout<<"-1\n";return 0;}
		res=0,print();
	}
	if(!t){
		res=0;
		for(int i=1;i<=n;i++) if(a[i]>0) res+=(a[i]-1)/k+1;
		print();
	}
	ll _r=4e18;
	while(n&&k<(n-1)*t){
		if(a[n]>0){cout<<"-1\n";return 0;}
		_r=min(_r,(-a[n])/t),n--;
	}
	ll l=0,r=1e9,mid;
	while(l<=r){
		mid=(l+r)>>1;
		ll tmp=check(mid);
		if(tmp>=0) r=mid-1,res=tmp;
		else l=mid+1;
	}
	if(res>_r){cout<<"-1\n";return 0;}
	print();
	return 0;
}