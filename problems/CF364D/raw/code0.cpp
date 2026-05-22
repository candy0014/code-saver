#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
ll a[1000005];
int id[1000005],cnt[1000005];
vector<ll>p;
ll calc(ll x){
	p.clear();
	for(int i=1;1ll*i*i<=x;i++) if(x%i==0) id[i]=p.size(),p.emplace_back(i);
	for(int i=p.size()-1;i>=0;i--) if(p[i]*p[i]!=x) p.emplace_back(x/p[i]);
	int m=p.size();
	for(int i=0;i<m;i++) cnt[i]=0;
	for(int i=1;i<=n;i++){
		ll y=__gcd(x,a[i]);
		if(y<=x/y) cnt[id[y]]++;
		else cnt[m-1-id[x/y]]++;
	}
	ll res=1;
	for(int i=0;i<m;i++){
		for(int j=i+1;j<m;j++) if(p[j]%p[i]==0) cnt[i]+=cnt[j];
		if(cnt[i]*2>=n) res=p[i];
	}
	return res;
}
mt19937 rd(time(0));
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	ll res=1,ca=10;
	while(ca--) res=max(res,calc(a[rd()%n+1]));
	cout<<res<<"\n";
	return 0;
}