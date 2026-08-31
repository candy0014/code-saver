#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
ll a[5005],l,r,sum[2][5005];
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>l>>r;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++) sum[0][i]=sum[0][i-1],sum[1][i]=sum[1][i-1],sum[i&1][i]+=a[i];
	for(int i=1;i<=n;i++){
		int flag=0;
		for(int j=1;j<=n;j++) if(j!=i){
			int x=min(i,j),y=max(i,j);
			ll p=sum[1][x-1]+sum[0][y-1]-sum[0][x]+sum[1][n]-sum[1][y],q=sum[0][n]+sum[1][n]-p-a[x]-a[y];
			if(l-a[i]<=p&&q<=r-a[i]){cout<<"Alice\n";return 0;}
		}
	}
	cout<<"Bob\n";
	return 0;
}