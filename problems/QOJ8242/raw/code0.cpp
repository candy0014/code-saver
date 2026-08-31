#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,a[300005];
int mi=2e9,mik=0;
double sum[300005];
bool check(double x){
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i]-x;
	double mi=1e18;
	for(int i=1;i<=n;i++){
		if(i>=3&&i-3<mik-1) mi=min(mi,sum[i-3]);
		if(i>mik&&sum[i]>mi) return 1;
	}
	return 0;
}
void solve(){
	cin>>n,mi=2e9;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]<mi) mi=a[i],mik=i;
	}
	double l=0,r=1e9,mid;
	for(int i=1;i<=100;i++){
		mid=(l+r)/2;
		if(check(mid)) l=mid;
		else r=mid;
	}
	cout<<fixed<<setprecision(15)<<l<<"\n";
}
int main(){
	//freopen("test.in","r",stdin);
	//freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}