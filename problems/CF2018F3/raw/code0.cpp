#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,mod,dp[3005][3005],res[3005][3005],ans[3005];
ll ksm(ll u,ll v=mod-2){ll tmp=1;u%=mod;while(v) tmp=tmp*((v&1)?u:1)%mod,u=u*u%mod,v>>=1;return tmp;}
int jie[3005],inv[3005];
void add(int &u,ll v){u=(u+v)%mod;}
int calc(int l,int r){
	return 1ll*jie[n-l+1]*inv[n-r]%mod;
}
int F(int len){
	return 1ll*calc(len/2+1,len)*calc((len+3)/2,len)%mod;
}
void solve(){
	cin>>n>>mod;
	jie[0]=1;
	for(int i=1;i<=3002;i++) jie[i]=1ll*jie[i-1]*i%mod;
	inv[n]=ksm(jie[n]);
	for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod; 
	for(int i=0;i<=n+1;i++) for(int j=0;j<=n+1;j++) dp[i][j]=res[i][j]=0;
	dp[0][n+1]=1;
	for(int i=0;i<n;i++){
		int sum=0,l=i+1;
		for(int r=n;r>i;r--){
			int j=r+1;
			sum=(sum+1ll*dp[i][j]*inv[n-j+l])%mod;
			res[l][r]=1ll*sum*jie[n-r+l-1]%mod*F(r-l+1)%mod;
		}
		for(int j=i+2;j<=n+1;j++) if(dp[i][j]){
			add(dp[i+1][j],1ll*dp[i][j]*(n-j+i+2));
		}
		sum=0;
		for(int x=n-i-1;x>=1;x--){
			int j=x+i+2;
			sum=(sum+1ll*dp[i][j]*inv[n-j+1+i])%mod;
			add(dp[i+1][i+1+x],1ll*sum*jie[n-x]);
		}
	}
	for(int i=0;i<=n;i++) ans[i]=0;
	for(int i=1;i<=n;i++) for(int j=i;j<=n;j++){
		ans[j-i+1]=(1ll*ans[j-i+1]+res[i][j]-res[i-1][j]-res[i][j+1]+res[i-1][j+1])%mod;
	}
	int tmp=ksm(n,n);
	for(int i=1;i<=n;i++) ans[i]=(ans[i]+mod)%mod,tmp=(tmp-ans[i]+mod)%mod;
	ans[0]=tmp;
	for(int i=0;i<=n;i++) cout<<ans[i]<<" \n"[i==n];
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}