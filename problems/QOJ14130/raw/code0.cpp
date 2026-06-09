#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=998244353;
const int N=5e5+5;
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
int n,k;
vector<int>e[500005];
vector<int>d[500005];
void dfs(int u){
	d[u].emplace_back(1);
	for(auto v:e[u]){
		dfs(v);
		if(d[u].size()<d[v].size()+1){
			int tmp=d[u].size();
			d[u].resize(d[v].size()+1);
			for(int i=tmp;i<(int)d[u].size();i++) d[u][i]=0;
		}
		for(int i=0;i<(int)d[v].size();i++){
			d[u][i+1]+=d[v][i];
		}
	}
}
ll ans=0;
void dfs2(int u,vector<int>cnt){
	for(int i=1;i<(int)cnt.size();i++) ans+=C(cnt[i],k);
	for(auto v:e[u]){
		vector<int>_cnt;_cnt.resize(cnt.size()+1);
		_cnt[0]=1;
		for(int i=1;i<cnt.size()+1;i++){
			_cnt[i]=cnt[i-1];
			if(i<(int)d[v].size()) _cnt[i]+=d[v][i];
			if(i>=2&&i-2<(int)d[v].size()) _cnt[i]-=d[v][i-2];
		}
		while(_cnt.back()==0) _cnt.pop_back();
		dfs2(v,_cnt);
	}
}
void solve(){
	cin>>n>>k;k--;
	for(int i=1;i<=n;i++) e[i].clear(),d[i].clear();
	for(int i=2,u;i<=n;i++) cin>>u,e[u].emplace_back(i);
	if(!k){cout<<n<<"\n";return;}
	ans=0;
	dfs(1);
	dfs2(1,d[1]);
	cout<<ans%mod<<"\n";
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	init();
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}