#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,k,flag;
ll _l[2000005],_r[2000005],nex[2000005];
ll a[2000005],_a[2000005];
int to[20][2000005];
bool check(ll x){
	if(x&1) x--;
	for(int i=0;i<n;i++) _l[i]=a[i]-(x-a[i+1]+a[i])/2,_r[i]=a[i+1]+(x-a[i+1]+a[i])/2,_l[i+n]=_l[i]+a[n],_r[i+n]=_r[i]+a[n];
	for(int i=0,j=0;i<n;i++){
		while(j<n+n&&_l[j]<=_r[i]) j++;
		nex[i]=j,nex[i+n]=min(n+n,j+n);
	}
	nex[n+n]=n+n;
	for(int i=0;i<=n+n;i++) to[0][i]=nex[i];
	for(int j=1;j<20;j++) for(int i=0;i<=n+n;i++) to[j][i]=to[j-1][to[j-1][i]];
	for(int i=0;i<n;i++){
		int u=i;
		for(int j=0;j<20;j++) if((k>>j)&1) u=to[j][u];
		if(x>=a[n]-a[n-1]&&u>=i+n) return 1;
		if(i==0&&u>=n-1&&a[n-1]<=x) return 1;
	}
	return 0;
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>k;
	ll l=0,r=0,mid,res=0;
	for(int i=1;i<=n;i++) cin>>a[i],a[i]*=2,r+=a[i],l=max(l,a[i]);
	for(int i=1;i<=n;i++) _a[i]=a[i];
	for(int i=1;i<=n;i++) if(a[i]==l){
		int tot=0;
		for(int j=i+1;j<=n;j++) a[++tot]=_a[j];
		for(int j=1;j<=i;j++) a[++tot]=_a[j];
		break;
	}
	l=0;
	for(int i=1;i<n;i++) l=max(l,a[i]);
	for(int i=1;i<=n;i++) a[i]+=a[i-1];
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid)) res=mid,r=mid-1;
		else l=mid+1;
	}
	cout<<res/2<<"\n";
	return 0;
}