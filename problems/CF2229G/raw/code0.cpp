#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,k,g,h[200005],d[200005],tim[200005],pre[200005],nex[200005],st[200005],top,vis[200005];
ll dis[200005],sum[200005];
priority_queue<pair<ll,int> >q;
void solve(){
	cin>>n>>k>>g;
	for(int i=1;i<=n;i++) cin>>h[i],sum[i]=sum[i-1]+h[i],vis[i]=0,dis[i]=-2e18;
	for(int i=1;i<n;i++) cin>>d[i];
	tim[g]=dis[g]=0;
	for(int i=g+1;i<=n;i++) tim[i]=max(tim[i-1]+1,d[i-1]);
	for(int i=g-1;i>=1;i--) tim[i]=max(tim[i+1]+1,d[i]);
	st[top=0]=0;
	for(int i=1;i<=n;i++){
		while(top&&h[i]>=h[st[top]]) top--;
		pre[i]=st[top],st[++top]=i;
	}
	st[top=0]=n+1;
	for(int i=n;i>=1;i--){
		while(top&&h[i]>=h[st[top]]) top--;
		nex[i]=st[top],st[++top]=i;
	}
	q.push(make_pair(0,g)),dis[g]=0;
	while(!q.empty()){
		int u=q.top().second;q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		int v=pre[u];
		if(v&&tim[v]-abs(u-v)>=tim[u]){
			ll tmp=dis[u]+1ll*(tim[v]-abs(u-v)-tim[u])*h[u]+sum[u-1]-sum[v-1];
			if(tmp>dis[v]) dis[v]=tmp,q.push(make_pair(-tim[v],v));
		}
		v=nex[u];
		if(v!=n+1&&tim[v]-abs(u-v)>=tim[u]){
			ll tmp=dis[u]+1ll*(tim[v]-abs(u-v)-tim[u])*h[u]+sum[v]-sum[u];
			if(tmp>dis[v]) dis[v]=tmp,q.push(make_pair(-tim[v],v));
		}
	}
	ll res=0;
	for(int i=1;i<=n;i++) if(tim[i]<=k) res=max(res,dis[i]+1ll*(k-tim[i])*h[i]);
	cout<<res<<"\n";
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}