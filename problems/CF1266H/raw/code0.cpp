#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=1000000000000000003;
ll ksm(ll u,ll v=mod-2){ll tmp=1;u%=mod;while(v) tmp=(__int128)tmp*((v&1)?u:1)%mod,u=(__int128)u*u%mod,v>>=1;return tmp;}
ll n,A[60][60],B[60],a[60][120],L[60],R[60],b[60],c[60],vis[60];
void solve(){
	int u;string s;
	cin>>u>>s,s=" "+s;
	memset(b,0,sizeof(b)),memset(c,0,sizeof(c)),memset(B,0,sizeof(B));
	for(int i=1;i<=n;i++){
		if(s[i]=='R'){
			b[i]=(b[i]+1)%mod,B[i]++;
			if(R[i]<=n) b[R[i]]=(b[R[i]]-1+mod)%mod,B[R[i]]--;
		}
	}
	b[1]=(b[1]-1+mod)%mod,b[u]=(b[u]+1)%mod,B[1]--,B[u]++;
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) c[i]=(c[i]+(__int128)a[i][j+n]*b[j])%mod;
	// for(int i=1;i<=n;i++) cout<<c[i]<<" \n"[i==n];
	for(int i=1;i<=n;i++){
		__int128 tmp=B[i];
		for(int j=1;j<=n;j++) tmp-=(__int128)A[i][j]*c[j];
		if(tmp){cout<<"-1\n";return;}
	}
	for(int i=1;i<=n;i++) if(c[i]||s[i]=='R'){
		memset(vis,0,sizeof(vis));
		int v=i;
		while(!vis[v]) vis[v]=1,v=(s[v]=='R')?R[v]:L[v];
		if(!vis[u]){cout<<"-1\n";return;}
	}
	ll res=0;
	for(int i=1;i<=n;i++) res+=c[i]*2+(s[i]=='R');
	cout<<res<<"\n";
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n,n--;
	for(int i=1;i<=n;i++){
		cin>>L[i]>>R[i];
		a[i][i]=(a[i][i]-2+mod)%mod,A[i][i]-=2;
		if(L[i]<=n) a[L[i]][i]=(a[L[i]][i]+1)%mod,A[L[i]][i]++;
		if(R[i]<=n) a[R[i]][i]=(a[R[i]][i]+1)%mod,A[R[i]][i]++;
	}
	for(int i=1;i<=n;i++) a[i][i+n]=1;
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++) if(a[j][i]){swap(a[i],a[j]);break;}
		ll tmp=ksm(a[i][i]);
		for(int j=i;j<=n+n;j++) a[i][j]=(__int128)a[i][j]*tmp%mod;
		for(int j=1;j<=n;j++) if(j!=i){
			for(int k=n+n;k>=i;k--) a[j][k]=(a[j][k]-(__int128)a[j][i]*a[i][k]%mod+mod)%mod;
		}
	}
	int ca;cin>>ca;while(ca--)solve();
	return 0;
}