#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,p,q,a[100005],tag[100005];
ll sz[100005],al;
ll mi,rt;
vector<int>e[100005];
void dfs(int u,int fa){
	tag[u]=0,sz[u]=a[u];
	ll ma=0;
	for(auto v:e[u]) if(v!=fa) dfs(v,u),tag[u]+=(sz[v]>0),sz[u]+=sz[v],ma=max(ma,sz[v]);
	tag[u]=(a[u]>0||tag[u]>=2);
	ma=max(ma,al-sz[u]);
	if(ma<mi||(ma==mi&&a[u]>a[rt])) mi=ma,rt=u;
}
vector<ll>res;
void solve(){
	cin>>n>>p>>q,al=0;
	int cnt=0;
	for(int i=1;i<=n;i++) cin>>a[i],al+=a[i],cnt+=(a[i]>0),e[i].clear();
	for(int i=1,u,v;i<n;i++) cin>>u>>v,e[u].emplace_back(v),e[v].emplace_back(u);
	mi=1e18,rt=0,dfs(1,0);int u=rt;dfs(u,0);
	res.clear();
	for(int i=1;i<=n;i++) if(i!=u&&tag[i]) res.emplace_back(sz[i]);
	sort(res.begin(),res.end());
	ll ans=1ll*q*cnt;
	for(int i=0;i<(int)res.size();i++) ans=min(ans,1ll*p*res[i]+1ll*q*((int)res.size()-i));
	cout<<ans<<"\n";
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}