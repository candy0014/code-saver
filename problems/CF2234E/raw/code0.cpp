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
int n,flag;
ll a[500005],ls[500005],rs[500005],L[500005],R[500005];
int solve(int l,int r){
	if(l>r) return 0;
	if(flag) return 0;
	vector<int>p;
	for(int x=l;x<=r;){
		p.emplace_back(x);
		if(a[x]%(x-l+1)||x+a[x]/(x-l+1)-1>r){flag=1;return 0;}
		x+=a[x]/(x-l+1);
	}
	for(int i=1;i<(int)p.size();i++) ls[p[i]]=p[i-1];
	p.emplace_back(r+1);
	for(int i=0;i<(int)p.size()-1;i++) rs[p[i]]=solve(p[i]+1,p[i+1]-1);
	return p[p.size()-2];
}
void dfs(int u){
	if(!u) return;
	L[u]=R[u]=u,dfs(ls[u]),dfs(rs[u]);
	if(ls[u]) L[u]=L[ls[u]];
	if(rs[u]) R[u]=R[rs[u]];
}
void solve(int Ca){
	cin>>n,flag=0;
	for(int i=1;i<=n;i++) cin>>a[i],ls[i]=rs[i]=0;
	int rt=solve(1,n);
	if(flag){cout<<"0\n";return;}
	dfs(rt);
	int res=1;
	for(int i=1;i<=n;i++) res=1ll*res*C(R[i]-L[i],i-L[i])%mod;
	cout<<res<<"\n";
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