#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=998244353;
ll ksm(ll u,ll v=mod-2){ll tmp=1;u%=mod;while(v) tmp=tmp*((v&1)?u:1)%mod,u=u*u%mod,v>>=1;return tmp;}
int n,m,a[1005];
pair<int,int>dp0,dp1,dp2;
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	if(n==1){cout<<"0\n";return 0;}
	for(int i=1;i<=n;i++) cin>>a[i],m+=a[i];
	sort(a+1,a+n+1);
	dp1=make_pair(2,1),dp0=make_pair(0,1);
	int now=1,res=0;
	for(int i=1;i<m;i++){
		while(a[now]==i) now++,res=(res+1ll*dp1.first*ksm(dp1.second))%mod;
		dp2=make_pair((1ll*dp1.first*dp0.second%mod*(3*m-2*i)-1ll*dp1.second*dp0.first%mod*(2*m-i))%mod,1ll*dp1.second*dp0.second%mod*(m-i)%mod);
		dp0=dp1,dp1=dp2;
	}
	cout<<(1ll*dp1.first*ksm(dp1.second)%mod-res+mod*2)%mod<<"\n";
	return 0;
}