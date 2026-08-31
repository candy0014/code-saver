#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=998244353,N=3e5+5;
ll ksm(ll u,ll v=mod-2){ll tmp=1;u%=mod;while(v)tmp=tmp*((v&1)?u:1)%mod,u=u*u%mod,v>>=1;return tmp;}
ll jie[N],inv[N];
void init(int n=N-3){
	jie[0]=1;
	for(int i=1;i<=n;i++) jie[i]=jie[i-1]*i%mod;
	inv[n]=ksm(jie[n],mod-2);
	for(int i=n-1;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
ll C(ll u,ll v){
	if(v<0||v>u) return 0;
	return jie[u]*inv[v]%mod*inv[u-v]%mod;
}
int n;
string s;
int calc(int x,int y){return C(x-1+n-y,x-1);}
int main(){
	init();
	cin>>s,n=s.length(),s=" "+s;
	int res=0;
	for(int i=1;i<=n;i++){
		int j=i;
		while(j<n&&s[j+1]==s[j]) j++;
		if(i==1&&j==n){cout<<n<<"\n";return 0;}
		for(int k=i;k<=j;k++) res=(res+1ll*(k-i+1)*calc(i-1,k)+1ll*(j-k+1)*calc(k,j+1)+C(n-j+k-1,k))%mod;
		i=j;
	}
	cout<<res<<"\n";
	return 0;
}