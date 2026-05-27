#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
const ll mod=1e9+7;
const ll inf=2e9;
const int N=2e5+5;
const int M=2e5+5;
const int V=2e6+5;
int n,ca,a[105],dp[10005];
struct MAT{
	int a[105][105];
	MAT(int op=0){
		for(int i=0;i<=100;i++) for(int j=0;j<=100;j++) a[i][j]=(i==j)*op;
	}
	MAT operator*(const MAT &rs)const{
		MAT res(0);
		for(int i=0;i<=100;i++) for(int j=0;j<=100;j++) for(int k=0;k<=100;k++) res.a[i][j]=(res.a[i][j]+1ll*a[i][k]*rs.a[k][j])%mod;
		return res;
	}	
}base,pw[40];
int res[105],f[105];
void solve(int Ca){
	cin>>n>>ca;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=100;i++) base.a[i][i-1]=1;
	for(int i=1;i<=n;i++) base.a[100-a[i]+1][100]++;
	pw[0]=base;
	for(int i=1;i<40;i++) pw[i]=pw[i-1]*pw[i-1];
	while(ca--){
		int x;cin>>x;
		memset(res,0,sizeof(res));
		res[100]=1;
		for(int i=0;i<=30;i++) if((x>>i)&1){
			memset(f,0,sizeof(f));
			for(int j=0;j<=100;j++) for(int k=0;k<=100;k++) f[j]=(f[j]+1ll*pw[i].a[j][k]*res[k])%mod;
			for(int j=0;j<=100;j++) res[j]=f[j];
		}
		cout<<res[100]<<"\n";
	}
}
int main(){
	#ifdef ONLINE_JUDGE
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	#endif
	#ifndef ONLINE_JUDGE
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	
	int Ca=1;
//	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}