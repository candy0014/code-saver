#include <bits/stdc++.h>
using namespace std;
const int mod=998244353;
int n,a[1500005],dp[1500005],f[1500005],pre[1500005];
int C[1500025][22];
vector<int>g[1500005];
int vis[1500005];
int F(int i,int n){
	return C[n+i-1][i];
}
int calc(int x,int n){
	if(x==1) return n>=0;
	if(n<=0) return 0;
	int res=1;
	for(auto p:g[x]) res=1ll*res*F(p,n)%mod;
	return res;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=2;i<=1500000;i++) if(!vis[i]){
		for(int j=i+i;j<=1500000;j+=i) vis[j]=1;
		for(int j=i;j<=1500000;j+=i){
			int tmp=j,cnt=0;
			while(tmp%i==0) tmp/=i,cnt++;
			g[j].emplace_back(cnt);
		}
	}
	for(int i=0;i<=n+21;i++){
		C[i][0]=1;
		for(int j=1;j<=min(i,21);j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	for(int i=n-1;i>=1;i--) a[i]=min(a[i],a[i+1]);
	dp[1]=1,a[0]=1;
	for(int i=0;i<n;i++){
		int j=i+1;
		while(j<n&&a[j+1]<=a[i+1]*2) j++;
		for(int k=i;k<=j;k++){
			for(int p=(k==i)?1:(a[k-1]+1);p<=a[k];p++) pre[p]=k-1;
		}
		for(int k=1;k<=a[j];k++) f[k]=0;
		for(int k=1;k<=a[i];k++){
			for(int p=1;k*p<=a[j];p++){
				f[k*p]=(f[k*p]+1ll*dp[k]*(calc(p,j-i)-calc(p,pre[p*k]-i)))%mod;
			}
		}
		for(int k=1;k<=a[j];k++) dp[k]=f[k];
		i=j-1;
	}
	int res=0;
	for(int i=1;i<=a[n];i++) res=(res+dp[i])%mod;
	cout<<(res+mod)%mod<<"\n";
	return 0;
}