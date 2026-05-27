#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
ll a[20],suml[1100005],sumr[1100005];
bool check(int s){
	vector<ll>ls,rs;
	for(int i=0;i<n;i++) if((s>>i)&1) ls.emplace_back(a[i]);
	while(ls.size()>rs.size()+1) rs.emplace_back(ls.back()),ls.pop_back();
	int nl=ls.size(),nr=rs.size();
	if(!nr) return ls[0]==0;
	suml[0]=sumr[0]=0;
	for(auto x:ls) suml[0]-=x;
	for(auto x:rs) sumr[0]-=x;
	for(int i=1;i<(1<<nl);i++) suml[i]=suml[i&(i-1)]+2*ls[__lg(i&(-i))];
	for(int i=1;i<(1<<nr);i++) sumr[i]=sumr[i&(i-1)]+2*rs[__lg(i&(-i))];
	int m=__builtin_popcount(s)-1;
	for(int i=0;i<(1<<nr)-1;i++){
		ll d=abs(suml[0]-sumr[i]);
		if(d<=m&&(m-d)%2==0) return 1;
	}
	for(int i=1;i<(1<<nr);i++){
		ll d=abs(suml[(1<<nl)-1]-sumr[i]);
		if(d<=m&&(m-d)%2==0) return 1;
	}
	sort(suml+1,suml+(1<<nl)-1),sort(sumr,sumr+(1<<nr));
	for(int i=1,j0=0,j1=0;i<(1<<nl)-1;i++){
		if((abs(suml[i])^m)&1){
			while(j1<(1<<nr)&&(sumr[j1]<suml[i]-m||!(abs(sumr[j1])&1))) j1++;
			if(j1<(1<<nr)&&sumr[j1]<=suml[i]+m) return 1;
		}
		else{
			while(j0<(1<<nr)&&(sumr[j0]<suml[i]-m||abs(sumr[j0])&1)) j0++;
			if(j0<(1<<nr)&&sumr[j0]<=suml[i]+m) return 1;
		}
	}
	return 0;
}
int dp[1100005];
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=0;i<n;i++) cin>>a[i];
	for(int i=1;i<(1<<n);i++) if(!dp[i]&&check(i)){
		dp[i]=1;
		int j=((1<<n)-1)^i;
		for(int k=j;k;k=(k-1)&j) dp[i|k]=max(dp[i|k],dp[k]+1);
	}
	cout<<n-dp[(1<<n)-1]<<"\n";
	return 0;
}