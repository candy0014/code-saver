#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
const ll mod=1e9+7;
const ll inf=2e9;
const int N=5e5+5;
const int M=2e5+5;
const int V=2e6+5;
ll ksm(ll u,ll v=mod-2){ll tmp=1;u%=mod;while(v) tmp=tmp*((v&1)?u:1)%mod,u=u*u%mod,v>>=1;return tmp;}
ll jie[N],inv[N];
void init(int n=N-3){
	jie[0]=1;
	for(int i=1;i<=n;i++) jie[i]=1ll*jie[i-1]*i%mod;
	inv[n]=ksm(jie[n],mod-2);
	for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
ll A(ll u,ll v){
	if(v<0||v>u) return 0;
	return 1ll*jie[u]*inv[u-v]%mod;
}
ll C(ll u,ll v){
	if(v<0||v>u) return 0;
	return 1ll*jie[u]*inv[v]%mod*inv[u-v]%mod;
}
int n,a[500005],b[500005],w[500005],du[500005],p[500005],tot,vis[500005];
int res[500005],len[500005];
void solve(int Ca){
	cin>>n;
	for(int i=1;i<=n;i++) du[i]=0,vis[i]=0,len[i]=-1e9;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i],du[b[i]]++;
	for(int i=1;i<=n;i++) cin>>w[i];
	tot=0;
	queue<int>q;
	for(int i=1;i<=n;i++) if(!du[i]) q.push(i);
	while(!q.empty()){
		int u=q.front();q.pop(),vis[u]=1;
		p[++tot]=u;
		int v=b[u];
		du[v]--;
		if(!du[v]) q.push(v);
	}
	for(int i=1;i<=n;i++) if(!vis[i]){
		int u=b[i];
		vector<int>tmp;tmp.emplace_back(i);
		while(u!=i) tmp.emplace_back(u),u=b[u];
		for(auto x:tmp) vis[x]=1;
		int m=tmp.size(),g=-1;
		for(int j=0;j<m;j++) if(a[tmp[j]]<a[tmp[(j+1)%m]]){g=j;break;}
		if(g==-1) continue;
		for(int j=1;j<=m;j++) p[++tot]=tmp[(g+j)%m];
	}
	for(int i=tot;i>=1;i--){
		int u=p[i];
		// cout<<u<<"\n";
		if(a[u]<a[b[u]]) len[u]=1;
		else if(a[u]<a[b[u]]+w[b[u]]) len[u]=len[b[u]]+1;
	}
	for(int i=1;i<=n;i++){
		if(len[i]<0) cout<<a[i]<<" \n"[i==n];
		else cout<<(a[i]+1ll*inv[len[i]]*w[i])%mod<<" \n"[i==n];
	}
}
int main(){
	#ifdef ONLINE_JUDGE
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	#endif
	#ifndef ONLINE_JUDGE
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	init();
	int Ca=1;
	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}