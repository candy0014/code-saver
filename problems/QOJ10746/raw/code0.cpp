#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll inf=1e17;
int n,m,s,t,head[5005],tot=1;
struct EDGE{int nex,to,f;ll w;}e[100005];
void ADD(int u,int v,int f,ll w){e[++tot].nex=head[u],e[tot].to=v,e[tot].f=f,e[tot].w=w,head[u]=tot;}
void add(int u,int v,int f,ll w){ADD(u,v,f,w),ADD(v,u,0,-w);}
struct Ans{int f;ll w;};
ll dis[5005];
int _head[5005],vis[5005];
queue<int>que;
bool bfs(){
	for(int i=1;i<=n;i++) dis[i]=1e18,vis[i]=0,_head[i]=head[i];
	dis[s]=0,vis[s]=1,que.push(s);
	while(!que.empty()){
		int u=que.front();que.pop(),vis[u]=0;
		for(int i=head[u];i;i=e[i].nex){
			int v=e[i].to,f=e[i].f;
			ll w=e[i].w;
			if(!f||dis[v]<=dis[u]+w) continue;
			dis[v]=dis[u]+w;
			if(!vis[v]) que.push(v),vis[v]=1;
		}
	}
	return dis[t]!=1e18;
}
Ans dfs(int u,int now){
	if(u==t) return Ans{now,0};
	Ans sum=Ans{0,0};
	vis[u]=1;
	for(int i=_head[u];i&&now;i=e[i].nex){
		_head[u]=i;
		int v=e[i].to,f=e[i].f;
		ll w=e[i].w;
		if(!f||dis[v]!=dis[u]+w||vis[v]) continue;
		Ans tmp=dfs(v,min(now,f));
		e[i].f-=tmp.f,e[i^1].f+=tmp.f,sum.f+=tmp.f,now-=tmp.f,sum.w+=tmp.w+tmp.f*w;
	}
    vis[u]=0;
	return sum;
}
Ans dinic(){
	Ans sum=Ans{0,0};
	while(bfs()){
		Ans tmp=dfs(s,INT_MAX);
		sum.f+=tmp.f,sum.w+=tmp.w;
	}
	return sum;
}
int nn,mm,p[55],q[55],a[55],b[55],cnt[55];
ll calc(int x,int op=0){
	for(int i=0;i<=mm;i++) cnt[i]=0;
	for(int i=1;i<=nn;i++) cnt[p[i]]++;
	n=nn+mm+3,s=n-1,t=n;
	for(int i=1;i<=n;i++) head[i]=0;
	tot=1;
	for(int i=0;i<=mm;i++) add(s,i+1,cnt[i],0);
	for(int i=1;i<mm;i++) add(i+1,t,x,0);
	add(1,t,1e9,0),add(mm+1,t,x,-inf);
	vector<int>tt(nn+1);
	for(int i=1;i<=nn;i++){
		add(p[i]+1,mm+i+1,1,0);
		add(mm+i+1,q[i]+1,1,a[i]);
		add(mm+i+1,mm+1,1,b[i]);
		tt[i]=tot;
	}
	Ans res=dinic();
	if(!op){
		if(res.f!=nn) return 2e18;
		return res.w+x*inf;
	}
	for(int i=1;i<=nn;i++){
		if(e[tt[i]-2].f) cout<<a[i]<<" ";
		else if(e[tt[i]].f) cout<<b[i]<<" ";
		else cout<<"0 ";
	}
	cout<<"\n";
	return 0;
}
void solve(){
	cin>>nn>>mm,mm++;
	for(int i=1;i<=nn;i++){
		vector<int>w(mm,0);
		map<int,int>mp;
		for(int j=1;j<mm;j++) cin>>w[j],mp[w[j]]++;
		int ma=0,sma=0;
		for(int j=1;j<mm;j++) if(w[j]&&mp[w[j]]==1){
			if(w[j]>=ma) sma=ma,ma=w[j];
			else sma=max(sma,w[j]);
		}
		a[i]=ma,b[i]=ma+1;
		while(mp[b[i]]>1) b[i]++;
		p[i]=q[i]=0;
		for(int j=1;j<mm;j++) if(w[j]){
			if(w[j]==ma) p[i]=j;
			if(w[j]==sma) q[i]=j;
		}
	}
	ll mi=1e18,mik;
	for(int i=0;i<=nn;i++){
		ll tmp=calc(i);
		if(tmp<mi) mi=tmp,mik=i;
	}
	calc(mik,1);
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}