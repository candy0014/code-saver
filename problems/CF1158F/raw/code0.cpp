#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=998244353;
ll ksm(ll u,ll v=mod-2){ll tmp=1;u%=mod;while(v) tmp=tmp*((v&1)?u:1)%mod,u=u*u%mod,v>>=1;return tmp;}
const int lim=10;
int n,c,a[3005],res[3005],pw[3005],mul[3005],suf[3005],cnt[3005];
namespace solve1{
	int dp[2][3005];
	void solve(){
		dp[0][0]=1;
		int now=0;
		for(int j=1;j<=n/c;j++){
			now^=1;
			for(int i=j*c;i<=n;i++){
				memset(cnt,0,sizeof(cnt));
				int tmp=1,tot=0,sum=0;
				for(int k=i;k>(j-1)*c;k--){
					tot+=!cnt[a[k]],++cnt[a[k]];
					if(a[k]!=a[i]) tmp=1ll*tmp*mul[cnt[a[k]]]%mod;
					if(tot==c) sum=(sum+1ll*tmp*dp[now^1][k-1])%mod;
				}
				dp[now][i]=sum,res[j]=(res[j]+1ll*sum*suf[i+1])%mod;
			}
		}
		res[0]=(res[0]+suf[1])%mod;
	}
}
namespace solve2{
	int dp[2][3005][8192];
	void add(int &u,int v){u+=v,u-=(u>=mod)*mod;}
	void solve(){
		int now=0;
		dp[0][0][0]=1;
		for(int i=0;i<n;i++){
			for(int j=0;j<=(i+1)/c;j++) for(int k=0;k<(1<<c);k++) dp[now^1][j][k]=dp[now][j][k];
			for(int j=0;j<=i/c;j++) for(int k=0;k<(1<<c);k++) if(dp[now][j][k]){
				int tmp=k|(1<<a[i+1]);
				add(dp[now^1][j+(tmp==(1<<c)-1)][(tmp!=(1<<c)-1)*tmp],dp[now][j][k]);
			}
			now^=1;
		}
		for(int j=0;j<=n/c;j++) for(int k=0;k<(1<<c);k++) add(res[j],dp[now][j][k]);
	}
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>c,pw[0]=mul[1]=1;
	for(int i=1;i<=n;i++) pw[i]=pw[i-1]*2%mod;
	for(int i=2;i<=n;i++) mul[i]=1ll*(pw[i]-1)*ksm(pw[i-1]-1)%mod;
	for(int i=1;i<=n;i++) cin>>a[i],a[i]--;
	int tmp=1,tot=0;suf[n+1]=1;
	for(int i=n;i>=1;i--){
		tot+=!cnt[a[i]],tmp=1ll*tmp*mul[++cnt[a[i]]]%mod;
		suf[i]=(pw[n-i+1]-(tot==c)*tmp+mod)%mod;
	}
	if(c>lim) solve1::solve();
	else solve2::solve();
	res[0]=(res[0]-1+mod)%mod;
	for(int i=0;i<=n;i++) cout<<res[i]<<" \n"[i==n];
	return 0;
}