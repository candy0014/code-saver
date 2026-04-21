#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
ll a[1000005];
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],a[i]+=a[i-1];
	int ma=0;
	for(int i=1,flag=0;i<n;i++){
		if(a[i]*n<a[n]*i){cout<<"Yes\n";return;}
		if(a[i]*n>a[n]*i) flag++;
		else flag=0;
		ma=max(ma,flag);
	}
	if(ma>=2) cout<<"No\n";
	else cout<<"Yes\n";
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}