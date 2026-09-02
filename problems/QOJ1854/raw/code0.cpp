#include <bits/stdc++.h>
using namespace std;
int n,a,b;
void solve(){
	cin>>n>>a>>b;
	if(__gcd(a,b)!=1){cout<<"-1\n";return;}
	if(a==1){for(int i=0;i<n;i++)cout<<i<<" \n"[i==n-1];return;}
	if(b==1){for(int i=n-1;i>=0;i--)cout<<i<<" \n"[i==0];return;}
	int k=n%(a+b);
	if(k!=0&&k!=1&&k!=a+b-1){cout<<"-1\n";return;}
	int now=0;
	if(k!=a+b-1) cout<<"0 ";
	else n++;
	for(int i=1;i<n;i++){
		if((now+a)%(a+b)<now%(a+b)&&(now+a)%(a+b)) now-=b;
		else now+=a;
		cout<<now-(k==a+b-1)<<" ";
	}
	cout<<"\n";
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}