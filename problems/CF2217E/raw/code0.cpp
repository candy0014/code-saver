#include <bits/stdc++.h>
using namespace std;
int n,a[5005],d[5005],res[5005];
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>d[i],res[i]=0;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++) d[i]-=(a[j]>a[i]);
		if(d[i]>0){cout<<"-1\n";return;}
	}
	for(int i=1;i<=n;i++){
		int mi=1e9,mik=0;
		for(int j=1;j<=n;j++) if(!res[j]&&d[j]==0&&a[j]<mi) mi=a[j],mik=j;
		res[mik]=i;
		for(int j=1;j<mik;j++) if(!res[j]&&a[j]<a[mik]) d[j]++;
	}
	for(int i=1;i<=n;i++) cout<<res[i]<<" \n"[i==n];
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}