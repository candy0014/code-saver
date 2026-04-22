#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
ll d;
struct node{
	ll l,r,x;
}s[5005];
ll dp[5005];
void solve(){
	cin>>n>>d;
	for(ll i=1,p;i<=n;i++){
		cin>>p>>s[i].x;
		s[i].l=p-s[i].x,s[i].r=p+s[i].x+d,s[i].x*=2;
	}
	sort(s+1,s+n+1,[&](node u,node v){return u.r<v.r;});
	for(int i=1;i<=n;i++) dp[i]=1e18;
	for(int i=0;i<n;i++) if(dp[i]!=1e18){
		ll sum=0,mi=1e18;
		for(int j=i;j<n;j++){
			if(j!=i) sum+=s[j].x,mi=min(mi,s[j].r-sum);
			ll tmp=max(dp[i],s[j+1].l)+s[j+1].x;
			if(tmp<=s[j+1].r&&tmp<=mi) dp[j+1]=min(dp[j+1],tmp+sum);
		}
	}
	if(dp[n]!=1e18) cout<<"Yes\n";
	else cout<<"No\n";
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}