#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,d;
ll a[1000005],sum;
void solve(){
	cin>>n>>d,sum=0;
	for(int i=1;i<=n;i++) cin>>a[i],sum+=a[i];
	if(!sum){cout<<"0\n";return;}
	sum/=n;
	ll now=0,ans=0;
	for(int i=1;i<=n;i++){
		ans=max(ans,abs(i-(now/sum+1)));
		now+=a[i];
		ans=max(ans,abs(i-((now-1)/sum+1)));
	}
	cout<<(ans+d-1)/d<<"\n";
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}