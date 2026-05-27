#include <bits/stdc++.h>
using namespace std;
const int mod=998244353,inv2=(mod+1)/2,V=17;
int n,seed,a[17000005],b[17000005];
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=0;i<(1<<V);i++) a[i]=1;
	for(int i=1,u;i<=n;i++){
		cin>>u;
		int ta=a[u],tb=b[u];
		a[u]=(ta+2ll*tb)%mod,b[u]=(tb+2ll*ta)%mod;
	}
	for(int i=0;i<(1<<V);i++){
		int ta=a[i],tb=b[i];
		a[i]=(ta+tb)%mod,b[i]=(ta-tb+mod)%mod;
	}
	for(int len=1;len<(1<<V);len<<=1){
		for(int i=0;i<(1<<V);i+=(len<<1)){
			for(int j=0;j<len;j++){
				int a0=a[i+j],a1=a[i+j+len],b0=b[i+j],b1=b[i+j+len];
				a[i+j]=1ull*a0*a1%mod,b[i+j]=1ull*b0*b1%mod;
				a[i+j+len]=1ull*a0*b1%mod,b[i+j+len]=1ull*b0*a1%mod;
			}
		}
	}
	for(int len=1;len<(1<<V);len<<=1){
		for(int i=0;i<(1<<V);i+=len<<1){
			for(int j=0;j<len;j++){
				int a0=a[i+j],a1=a[i+j+len];
				a[i+j]=(a0+a1)%mod,a[i+j+len]=(a0-a1+mod)%mod;
			}
		}
	}
	int tmp=1;
	for(int i=0;i<V;i++) tmp=1ll*tmp*inv2%mod;
	cout<<1ull*a[0]*tmp%mod<<"\n";
	return 0;
}