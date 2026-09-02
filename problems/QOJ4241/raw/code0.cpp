#include <bits/stdc++.h>
using namespace std;
const int mod=998244353;
int n,m,ca,al;
// int vis[105][105],id[105][105];
vector<int>vis[3000005],id[3000005];
int fa[4000005],sz[4000005],cnt[4000005],tag[4000005];
int Find(int u){return fa[u]==u?u:(fa[u]=Find(fa[u]));}
void merge(int u,int v){
	u=Find(u),v=Find(v);
	if(u==v) cnt[u]++;
	else fa[u]=v,sz[v]+=sz[u],cnt[v]+=cnt[u]+1,tag[v]+=tag[u];
}
string str;
void solve(){
	cin>>n>>m,al=(n+2)*(m+2);
	for(int i=0;i<=n+1;i++) vis[i].assign(m+2,0),id[i].assign(m+2,0);
	for(int i=1;i<=al;i++) fa[i]=i,sz[i]=1,cnt[i]=0,tag[i]=0;
	for(int i=0;i<=n+1;i++) for(int j=0;j<=m+1;j++) id[i][j]=i*(m+2)+j+1;
	for(int i=0;i<=n+1;i++) for(int j=0;j<=m+1;j++) vis[i][j]=(i==0||i==n+1||j==0||j==m+1),tag[id[i][j]]=vis[i][j];
	for(int i=1;i<=n;i++){
		cin>>str;
		for(int j=1;j<=m;j++) if(str[j-1]=='*') vis[i][j]=1,tag[id[i][j]]=1;
	}
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(vis[i][j]) merge(id[i-1][j],id[i+1][j]),merge(id[i][j-1],id[i][j+1]);
	int ans=1;
	for(int i=1;i<=al;i++) if(fa[i]==i){
		if(cnt[i]+tag[i]>sz[i]){cout<<"0\n";return;}
		if(cnt[i]==sz[i]-1){
			if(!tag[i]) ans=1ll*ans*sz[i]%mod;
		}
		else ans=2ll*ans%mod;
	}
	cout<<ans<<"\n";
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}