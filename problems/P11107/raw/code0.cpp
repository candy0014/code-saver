#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
int mod=998244353;
ll G=3,iG=(mod+1)/G;
const int N=1000005;
ll ksm(ll u,ll v=mod-2){ll tmp=1;u%=mod;while(v) tmp=tmp*((v&1)?u:1)%mod,u=u*u%mod,v>>=1;return tmp;}
vector<int>dp[20][20],f[20][20];
ll jie[N],inv[N];
void init(int n=N-3){
	jie[0]=1;
	for(int i=1;i<=n;i++) jie[i]=1ll*jie[i-1]*i%mod;
	inv[n]=ksm(jie[n],mod-2);
	for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
ll Comb(ll u,ll v){
	if(v<0||v>u) return 0;
	return 1ll*jie[u]*inv[v]%mod*inv[u-v]%mod;
}
void add(int &u,ll v){u=(u+v)%mod;}
ull A[1000005],B[1000005],C[1000005];
int pos[N];
ull pw[N];
void NTT(ull *a,int len,int op){
	for(int i=1;i<len;i++) pos[i]=(pos[i>>1]>>1)|((i&1)?(len>>1):0);
	for(int i=0;i<len;i++) if(pos[i]<i) swap(a[i],a[pos[i]]);
	for(int l=1;l<len;l<<=1){
		ull w=ksm((op==1)?G:iG,(mod-1)/(l<<1));
		pw[0]=1;
		for(int i=1;i<l;i++) pw[i]=pw[i-1]*w%mod;
		for(int i=0;i<len;i+=(l<<1)){
			for(int t=i;t<i+l;t++){
				ull tmp=a[t+l]*pw[t-i]%mod;
				a[t+l]=a[t]+mod-tmp,a[t]+=tmp;
			}
		}
		if(l==(1<<16)) for(int i=0;i<len;i++) a[i]%=mod;
	}
	if(op==-1){
		int tmp=ksm(len);
		for(int i=0;i<len;i++){
			a[i]=a[i]%mod*tmp%mod;
		}
	}
	else{
		for(int i=0;i<len;i++) a[i]%=mod;
	}
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>mod;
	vector<int>d;
	for(int i=1;i*i<=mod;i++) if((mod-1)%i==0) d.emplace_back(i),d.emplace_back(mod/i);
	for(int i=2;;i++){
		int flag=0;
		for(auto x:d) if(ksm(i,x)==1){flag=1;break;}
		if(!flag){
			G=i,iG=ksm(G);
			break;
		}
	}
	init();
	for(int k=0;k<=17;k++){
		for(int j=0;j<=17;j++) dp[k][j].resize(1<<k),f[k][j].resize(1<<k);
		if(k==0){
			dp[k][0][1]=1;
			continue;
		}
		if(k==1){
			dp[k][0][1]=1;
			dp[k][1][2]=1;
			f[k][0][1]=1;
			continue;
		}
		for(int p=0;p<=k;p++){
			for(int x=0;x<(1<<k);x++) A[x]=B[x]=C[x]=0;
			for(int x=1;x<(1<<(k-1));x++) A[x]=dp[k-1][p][x];
			for(int x=0;x<=(1<<(k-1));x++) B[x]=Comb(1<<(k-1),x),C[x]=Comb((1<<(k-1))-1,x);
			NTT(A,1<<k,1),NTT(B,1<<k,1),NTT(C,1<<k,1);
			for(int x=0;x<(1<<k);x++) B[x]=1ll*B[x]*A[x]%mod,C[x]=1ll*C[x]*A[x]%mod;
			NTT(B,1<<k,-1),NTT(C,1<<k,-1);
			for(int x=0;x<(1<<k);x++) dp[k][p][x]=B[x],f[k][p][x]=C[x];
			for(int n=(1<<(k-1));n<(1<<k);n++){
				add(dp[k][p][n],dp[k-1][p][n-(1<<(k-1))]);
				add(f[k][p][n],f[k-1][p][n-(1<<(k-1))]);
				add(dp[k][p][n],f[k-1][p][n-(1<<(k-1))]);
				if(p==k-1){
					int tmp=Comb((1<<(k-1))-2,n-(1<<(k-1)));
					add(dp[k][p][n],tmp),add(f[k][p][n],tmp);
				}
			}
		}
		add(dp[k][k][1<<k],1);
	}
	int Ca;cin>>Ca;while(Ca--){
		int k,n,p;
		cin>>k>>n>>p;p--;
		if(p&(p+1)){cout<<"0\n";continue;}
		p=__lg(p+1);
		cout<<dp[k][p][n]<<"\n";
	}
	return 0;
}