#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
const ll mod=998244353;
const ll inf=2e9;
const int N=2e5+5;
const int M=2e5+5;
const int V=2e6+5;
ll ksm(ll u,ll v=mod-2){ll tmp=1;u%=mod;while(v) tmp=tmp*((v&1)?u:1)%mod,u=u*u%mod,v>>=1;return tmp;}
int jie[105],inv[105];
int n,c,a[105],dp[105][105][105],f[105][105],g[105];
void add(int &u,ll v){u=(u+v)%mod;}
void solve(int Ca){
	cin>>n>>c;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1),a[0]=1,a[n+1]=c+1;
	memset(dp,0,sizeof(dp));
	for(int i=0;i<=n;i++){
		for(int j=0;j<=n;j++){
			g[j]=0;
			for(int k=0,tmp=1;k<=j;k++) add(g[j],1ll*tmp*inv[k]%mod*f[k][j]),tmp=1ll*tmp*(a[i+1]-a[i]-k)%mod;
		}
		if(i==0){
			for(int j=0;j<=n;j++) dp[0][0][j]=g[j];
			continue;
		}
		for(int j=0;j<=i-1;j++) for(int k=j;k<=n;k++) if(dp[i-1][j][k]) for(int p=0;p+k<=n;p++){
			add(dp[i][min(i,j+p)][k+p],1ll*dp[i-1][j][k]*g[p]);
		}
	}
	int tmp=1ll*jie[n]*ksm(ksm(c),n)%mod;
	for(int i=0;i<=n;i++) cout<<1ll*tmp*dp[n][i][n]%mod<<" \n"[i==n];
}
int main(){
	#ifdef ONLINE_JUDGE
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	#endif
	#ifndef ONLINE_JUDGE
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	jie[0]=inv[0]=1;
	for(int i=1;i<=100;i++) jie[i]=1ll*jie[i-1]*i%mod,inv[i]=ksm(jie[i]);
	f[0][0]=1;
	for(int i=1;i<=100;i++) for(int j=i;j<=100;j++) for(int k=1;k<=j;k++) add(f[i][j],1ll*f[i-1][j-k]*inv[k]);
	int Ca=1;
	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}