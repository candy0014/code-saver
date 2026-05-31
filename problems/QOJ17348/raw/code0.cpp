#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
const ll mod=998244353;
const ll inf=2e18;
const int N=2e5+5;
const int M=2e5+5;
const int V=2e6+5;
ll ksm(ll u,ll v=mod-2){ll tmp=1;u%=mod;while(v) tmp=tmp*((v&1)?u:1)%mod,u=u*u%mod,v>>=1;return tmp;}
int n,k,a[500005];
map<int,int>mp;
void solve(int Ca){
	cin>>n>>k,mp.clear();
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]<=k) mp[a[i]]++;
	}
	if(n==1&&a[1]==k){cout<<"0\n";return;}
	if(k==0){
		if(!mp[0]){cout<<"1\n";return;}
		else{cout<<"2\n";return;}
	}
	int flag=1;
	if(k<=n){
		flag=0;
		for(int i=0;i<k;i++) if(!mp.count(i)){flag=1;break;}
	}
	ll res=1;
	if(mp.count(k)&&(k==1||!flag)){cout<<"2\n";return;}
	ll dp=1,dp2=1;
	// for(int i=k-1;i>=0;i--){
	// 	res+=max(0ll,dp-mp[i]);
	// 	dp+=max(0ll,dp-mp[i]);
	// }
	vector<int>p;
	for(auto x:mp) if(x.first<k) p.emplace_back(x.first);
	reverse(p.begin(),p.end());
	if(!p.size()||p.back()) p.emplace_back(0);
	int la=k-1;
	for(int i=0;i<(int)p.size();i++){
		int now=p[i];
		ll tmp=ksm(2,la-now);
		res=(res+1ll*dp*(tmp-1))%mod;
		dp=1ll*dp*tmp%mod;
		if(la-now<=62&&dp2<=(inf>>(la-now))) dp2<<=(la-now);
		else dp2=inf;
		if(dp2>mp[now]){
			res=(res+dp-mp[now])%mod;
			dp=(dp+dp-mp[now])%mod;
			dp2=min(inf,dp2+dp2-mp[now]);
		}
		la=now-1;
	}
	cout<<(res+mod)%mod<<"\n";
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