#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
namespace FastIO {
	static char buf[100000], *p1 = buf, *p2 = buf;
	#define gc (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++)
	inline ll read() { 
		ll res = 0;
		int w = 0, c = gc; 
		for (; !isdigit(c); c = gc) {
			((c == '-') && (w = 1));
		}
		for (; isdigit(c); c = gc) {
			res = (res << 1) + (res << 3) + (c ^ 48);
		}
		return (w ? -res : res);
	}
	inline char readC() {  
		int c = gc; 
		while (c == '\n' || c == '\r' || c == ' ') {
			c = gc;
		}
		return c;
	}
	inline string readS() {
		string res = "";
		char c = gc; 
		for (; (c == '\n' || c == '\r' || c == ' ' || c == EOF); c = gc);
		for (; !(c == '\n' || c == '\r' || c == ' ' || c == EOF); c = gc) {
			res += c;
		}
		return res;
	}   
	inline double readF() { 
		double res = 0, tmp = 0.1;
		int w = 0; 
		char c = gc; 
		for (; !isdigit(c); c = gc) {
			((c == '-') && (w = 1));
		}
		for (; isdigit(c); c = gc) {
			res = (res * 10) + (c ^ 48);
		}
		if (c == '.') {
			c = gc;
			for (; isdigit(c); c = gc) {
				res = res + tmp * (c ^ 48);
				tmp *= 0.1;
			}
		}
		return (w ? -res : res);
	}
	inline void write(ll x, char c = '\n') {
		((x < 0) && (putchar('-'), x *= -1));
		static int sta[50], top = 0; 
		do {
			sta[top++] = x % 10, x /= 10;
		} while (x); 
		while (top) {
			putchar(sta[--top] + 48);
		} 
		putchar(c);
	}
}

using namespace FastIO;
const int mod=998244353,N=100005;
const int inf=1e9;
int n,k,val[500005];
int mi[500005][20],dfn[500005],num,de[500005];
// vector<int>e[500005];
int head[500005],tot;
struct EDGE{int nex,to;}e[1000005];
void add(int u,int v){e[++tot].nex=head[u],e[tot].to=v,head[u]=tot;}
int getmi(int u,int v){return dfn[u]<dfn[v]?u:v;}
void init(int u,int fa){
	dfn[u]=++num,mi[dfn[u]][0]=fa,de[u]=de[fa]+1;
	for(int i=head[u];i;i=e[i].nex) if(e[i].to!=fa) init(e[i].to,u);
	if(u==1) for(int j=1;j<20;j++) for(int i=1;i+(1<<j)-1<=n;i++) mi[i][j]=getmi(mi[i][j-1],mi[i+(1<<(j-1))][j-1]);
}
int LCA(int u,int v){
	if(u==v) return u;
	if((u=dfn[u])>(v=dfn[v])) swap(u,v);
	int t=__lg(v-u++);
	return getmi(mi[u][t],mi[v-(1<<t)+1][t]);
}
int dis(int u,int v){return de[u]+de[v]-de[LCA(u,v)]*2;}
int vis[500005],sz[500005];
int rt,minn;
int fat[500005],ff[500005];
void dfs1(int u,int fa,int SZ){
	sz[u]=1,ff[u]=fa;
	int ma=0;
	for(int i=head[u];i;i=e[i].nex){
		int v=e[i].to;
		if(v!=fa&&!vis[v]) dfs1(v,u,SZ),sz[u]+=sz[v],ma=max(ma,sz[v]);
	}
	ma=max(ma,SZ-sz[u]);
	if(ma<minn) minn=ma,rt=u;
}
int dfs(int u,int SZ){
	rt=0,minn=1e9,dfs1(u,0,SZ),u=rt,vis[u]=1;
	for(int i=head[u];i;i=e[i].nex){
		int v=e[i].to;
		if(!vis[v]){
			int tmp=sz[v];
			if(v==ff[u]) tmp=SZ-sz[u];
			v=dfs(v,sz[v]),fat[v]=u;
		}
	}
	return u;
}
int dp[500005];
int sum[20000005];
struct BIT{
	int n,pre;
	void init(int _n,int _pre){
		n=_n,pre=_pre;
		for(int i=0;i<=n;i++) sum[pre+i]=inf;
	}
	void add(int x,int k){if(!x){sum[pre]=min(sum[pre],k);return;}while(x<=n)sum[x+pre]=min(sum[x+pre],k),x+=(x&(-x));}
	int query(int x){x=min(x,n);int t=sum[pre];while(x)t=min(t,sum[x+pre]),x-=(x&(-x));return t;}
}b1[500005];
int ds[500005][20];
void update(int u,int k,int op=0){
	int v=u,cc=0;
	while(v){
		b1[v].add(ds[u][cc],k);
		v=fat[v],cc++;
	}
}
int query(int u,int d){
	int v=u,la=0,res=inf,cc=0;
	while(v){
		int de=d-ds[u][cc];
		if(de<0){la=v,v=fat[v],cc++;continue;}
		res=min(res,b1[v].query(de));
		la=v,v=fat[v],cc++;
	}
	return res;
}
int tag[500005];
queue<int>q;
string str;
int res[500005];
void solve(){
	n=read(),k=read();
	num=0,tot=0;
	for(int i=1;i<=n;i++) head[i]=0,fat[i]=vis[i]=dp[i]=tag[i]=res[i]=0;
	str=readS();
	for(int i=1,u,v;i<n;i++) u=read(),v=read(),add(u,v),add(v,u);
	init(1,0),dfs(1,n);
	for(int i=1;i<=n;i++) if(!fat[i]){rt=i;break;}
	for(int i=1;i<=n;i++){
		int u=i,cc=0;
		while(u) ds[i][cc]=dis(u,i),dp[u]=max(dp[u],ds[i][cc]),u=fat[u],cc++;
	}
	int pre=0;
	for(int i=1;i<=n;i++) b1[i].init(dp[i],pre),pre+=dp[i]+1;
	q.push(1),tag[1]=1;
	while(!q.empty()){
		int u=q.front();q.pop();
		if(u==1) res[u]=0;
		else res[u]=query(u,k)+(str[u-1]=='0');
		update(u,res[u]);
		for(int i=head[u];i;i=e[i].nex) if(!tag[e[i].to]) q.push(e[i].to),tag[e[i].to]=1;
	}
	for(int i=2;i<=n;i++) write(res[i]," \n"[i==n]);
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	// ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca=read();while(Ca--)solve();
	cerr<<clock()*1.0/CLOCKS_PER_SEC<<"\n";
	return 0;
}