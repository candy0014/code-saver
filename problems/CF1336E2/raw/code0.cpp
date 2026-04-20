#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=998244353,inv2=(mod+1)/2;
ll d[60],n,m,cnt=0,mul;
ll C[60][60];
int insert(ll x){
	for(int i=m-1;i>=0;i--) if((x>>i)&1){
		if(!d[i]){
			for(int j=i-1;j>=0;j--) if((x>>j)&1) x^=d[j];
			d[i]=x,cnt++;
			for(int j=i+1;j<m;j++) if((d[j]>>i)&1) d[j]^=d[i];
			return 1;
		}
		x^=d[i];
	}
	return 2;
}
ll res[60];
namespace solve1{
	vector<ll>p;
	int g;
	void dfs(int i=0,ll now=0){
		if(i==g){res[__builtin_popcountll(now)]++;return;}
		dfs(i+1,now),dfs(i+1,now^p[i]);
	}
	void solve(){
		p.clear();
		for(int i=0;i<m;i++) if(d[i]) p.emplace_back(d[i]);
		g=p.size(),dfs();
	}
}
namespace solve2{
	ll tmp[60],re[60];
	vector<ll>p;
	int g;
	void dfs(int i=0,ll now=0,int cnt=0){
		if(i==g){re[__builtin_popcountll(now)+cnt]++;return;}
		dfs(i+1,now,cnt),dfs(i+1,now^p[i],cnt+1);
	}
	void solve(){
		memset(tmp,0,sizeof(tmp)),memset(re,0,sizeof(re));
		for(int i=0;i<m;i++) if(d[i]){
			for(int j=0;j<i;j++) if((d[i]>>j)&1) tmp[j]|=(1ll<<i);
		}
		p.clear();
		for(int i=0;i<m;i++) if(!d[i]) p.emplace_back(tmp[i]);
		g=p.size(),dfs();
		for(int i=0;i<=m;i++) for(int j=0;j<=i;j++) for(int k=0;k<=m-i;k++){
			ll tmp=re[i]*C[i][j]%mod*C[m-i][k]%mod;
			if(j&1) tmp=mod-tmp;
			res[j+k]=(res[j+k]+tmp)%mod;
		}
		for(int i=0;i<g;i++) mul=1ll*mul*inv2%mod;
	}
}
void solve(){
	mul=1;
	cin>>n>>m,memset(d,0,sizeof(d)),cnt=0,memset(res,0,sizeof(res));
	for(ll i=1,u;i<=n;i++) cin>>u,mul=mul*insert(u)%mod;
	if(cnt<=27) solve1::solve();
	else solve2::solve();
	for(int i=0;i<=m;i++) cout<<res[i]*mul%mod<<" \n"[i==m];
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	for(int i=0;i<60;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	}
	solve();
	return 0;
}