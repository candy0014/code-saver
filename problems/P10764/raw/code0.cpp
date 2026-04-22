#include <bits/stdc++.h>
using namespace std;
const int mod=998244353;
int n,m,pw[500005];
vector<int>ee[500005],e[1000005];
int dfn[500005],low[500005],num,st[500005],top,val[1000005],cnt;
void tarjan(int u){
	st[++top]=u,dfn[u]=low[u]=++num;
	for(auto v:ee[u]){
		if(!dfn[v]){
			tarjan(v),low[u]=min(low[u],low[v]);
			if(low[v]==dfn[u]){
				cnt++;
				while(1){
					int w=st[top--];
					e[cnt].emplace_back(w),e[w].emplace_back(cnt),val[cnt]++;
					if(w==v) break;
				}
				e[cnt].emplace_back(u),e[u].emplace_back(cnt);
			}
		}
		else low[u]=min(low[u],dfn[v]);
	}
}
int dp[1000005],f[1000005],res;
void dfs(int u,int fa){
	for(auto v:e[u]) if(v!=fa) dfs(v,u);
	int s1=1,s2=0;
	for(auto v:e[u]) if(v!=fa){
		s1=1ll*s1*(f[v]+1)%mod,
		s2=(s2+f[v])%mod;
	}
	dp[u]=1ll*pw[val[u]+(u<=n)]*(s1-s2-1+mod)%mod;
	if(u<=n) dp[u]=(dp[u]+1ll*pw[val[u]]*s2)%mod;
	f[u]=(dp[u]+1ll*pw[val[u]]*s2+(u<=n))%mod;
	res=(res+dp[u])%mod;
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m,pw[0]=1,cnt=n;
	for(int i=1;i<=n;i++) pw[i]=pw[i-1]*2%mod;
	for(int i=1,u,v;i<=m;i++) cin>>u>>v,ee[u].emplace_back(v),ee[v].emplace_back(u);
	tarjan(1),dfs(1,0);
	cout<<((res+n)*2+1)%mod<<"\n";
	return 0;
}