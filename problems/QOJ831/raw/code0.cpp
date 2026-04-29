#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod=998244353,N=1200005;
ll ksm(ll u,ll v=mod-2){ll tmp=1;u%=mod;while(v) tmp=tmp*((v&1)?u:1)%mod,u=u*u%mod,v>>=1;return tmp;}
ll jie[N],inv[N];
void init(int n=N-3){
	jie[0]=1;
	for(int i=1;i<=n;i++) jie[i]=1ll*jie[i-1]*i%mod;
	inv[n]=ksm(jie[n],mod-2);
	for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
int n,m,k,val[300005];
int mi[300005][20],dfn[300005],num,de[300005];
vector<int>e[300005];
int getmi(int u,int v){return dfn[u]<dfn[v]?u:v;}
void init(int u,int fa){
	dfn[u]=++num,mi[dfn[u]][0]=fa,de[u]=de[fa]+1;
	for(auto v:e[u]) if(v!=fa) init(v,u);
	if(u==1) for(int j=1;j<20;j++) for(int i=1;i+(1<<j)-1<=n;i++) mi[i][j]=getmi(mi[i][j-1],mi[i+(1<<(j-1))][j-1]);
}
int LCA(int u,int v){
	if(u==v) return u;
	if((u=dfn[u])>(v=dfn[v])) swap(u,v);
	int t=__lg(v-u++);
	return getmi(mi[u][t],mi[v-(1<<t)+1][t]);
}
int dis(int u,int v){return de[u]+de[v]-de[LCA(u,v)]*2;}
int vis[300005],sz[300005];
int rt,minn;
int fat[300005];
void dfs1(int u,int fa,int SZ){
	sz[u]=1;
	int ma=0;
	for(auto v:e[u]) if(v!=fa&&!vis[v]) dfs1(v,u,SZ),sz[u]+=sz[v],ma=max(ma,sz[v]);
	ma=max(ma,SZ-sz[u]);
	if(ma<minn) minn=ma,rt=u;
}
vector<int>ee[300005];
int dfs(int u,int SZ){
	rt=0,minn=1e9,dfs1(u,0,SZ),u=rt,dfs1(u,0,SZ),vis[u]=1;
	for(auto v:e[u]) if(!vis[v]) v=dfs(v,sz[v]),fat[v]=u,ee[u].emplace_back(v);
	return u;
}
int dp[300005];
struct BIT{
	int n;
	vector<int>sum;
	void init(int _n){n=_n,sum.resize(n+1);}
	void add(int x,int k){if(!x){sum[x]+=k;return;}while(x<=n)sum[x]+=k,x+=(x&(-x));}
	int query(int x){x=min(x,n);int t=0;while(x)t+=sum[x],x-=(x&(-x));return t+sum[0];}
}b1[300005],b2[300005];
void update(int u,int k,int op=0){
	int v=u;
	while(v){
		b1[v].add(dis(v,u),k);
		if(fat[v]) b2[v].add(dis(fat[v],u),k);
		v=fat[v];
	}
}
int query(int u,int d){
	int v=u,la=0,res=0;
	while(v){
		int de=d-dis(u,v);
		if(de<0){la=v,v=fat[v];continue;}
		res+=b1[v].query(de);
		if(la) res-=b2[la].query(de);
		la=v,v=fat[v];
	}
	return res;
}
int tag[300005];
queue<int>q;
ull res[N],f[N];
const ll G=3,iG=(mod+1)/G;
int pos[N];
ull pw[N];
void NTT(ull *a,int len,int op){
	pw[0]=1;
	for(int i=0;i<len;i++) if(pos[i]<i) swap(a[i],a[pos[i]]);
	for(int l=1;l<len;l<<=1){
		ull w=ksm((op==1)?G:iG,(mod-1)/(l<<1));
		for(int i=1;i<l;i++) pw[i]=pw[i-1]*w%mod;
		for(int i=0;i<len;i+=(l<<1)){
			for(int t=i;t<i+l;t++){
				ull tmp=a[t+l]*pw[t-i]%mod;
				a[t+l]=a[t]+mod-tmp,a[t]+=tmp;
			}
		}
		if(l==(1<<16)) for(int i=0;i<len;i++) a[i]%=mod;
	}
	if(op==-1){
		int tmp=ksm(len);
		for(int i=0;i<len;i++){
			a[i]=a[i]%mod*tmp%mod;
		}
	}
	else{
		for(int i=0;i<len;i++) a[i]%=mod;
	}
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>k;
	init();
	for(int i=1,u,v;i<n;i++) cin>>u>>v,e[u].emplace_back(v),e[v].emplace_back(u);
	init(1,0),dfs(1,n);
	for(int i=1;i<=n;i++) if(!fat[i]){rt=i;break;}
	for(int i=1;i<=n;i++){
		int u=i;
		while(u) dp[u]=max(dp[u],dis(u,i)),u=fat[u];
	}
	for(int i=1;i<=n;i++) b1[i].init(dp[i]),b2[i].init(dp[i]*2+1);
	q.push(1),tag[1]=1;
	while(!q.empty()){
		int u=q.front();q.pop();
		res[query(u,k)]++,update(u,1);
		for(auto v:e[u]) if(!tag[v]) q.push(v),tag[v]=1;
	}
	for(int i=0;i<n;i++) res[i]=1ll*res[i]*jie[i]%mod,f[i]=inv[n-i-1];
	int len=1;
	while(len<n+n) len*=2;
	for(int i=1;i<len;i++) pos[i]=(pos[i>>1]>>1)|((i&1)?(len>>1):0);
	NTT(res,len,1),NTT(f,len,1);
	for(int i=0;i<len;i++) res[i]=res[i]*f[i]%mod;
	NTT(res,len,-1);
	for(int i=n-1;i<n+n-1;i++) cout<<res[i]*inv[i-n+1]%mod<<" ";
	return 0;
}
