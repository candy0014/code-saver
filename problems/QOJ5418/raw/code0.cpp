#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
const ll mod=998244353;
const ll inf=2e9;
const int N=2e5+5;
const int M=2e5+5;
const int V=2e6+5;
int n,a[N];
vector<int>e[N];
int dfn[N],R[N],num;
int mi[N][20],de[N];
vector<int>p[N];
int getmi(int u,int v){return dfn[u]<dfn[v]?u:v;}
int LCA(int u,int v){
	if(u==v) return u;
	if((u=dfn[u])>(v=dfn[v])) swap(u,v);
	int t=__lg(v-u++);
	return getmi(mi[u][t],mi[v-(1<<t)+1][t]);
}
void dfs(int u,int fa){
	dfn[u]=++num,mi[dfn[u]][0]=fa,de[u]=de[fa]+1,p[de[u]].emplace_back(u);
	for(auto v:e[u]) if(v!=fa) dfs(v,u);
	R[u]=num;
	if(u==1) for(int j=1;j<20;j++) for(int i=1;i+(1<<j)-1<=n;i++) mi[i][j]=getmi(mi[i][j-1],mi[i+(1<<(j-1))][j-1]);
}
int st[N][20];
int query(int l,int r){
	int t=__lg(r-l+1);
	return min(st[l][t],st[r-(1<<t)+1][t]);
}
vector<int>q;
ll dp[N];
vector<pair<int,int> >as[N];
void solve(int Ca){
	cin>>n,num=0;
	for(int i=1;i<=n;i++) cin>>a[i],e[i].clear(),p[i].clear(),st[i][0]=a[i];
	for(int j=1;j<20;j++) for(int i=1;i+(1<<j)-1<=n;i++) st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
	for(int i=1,u,v;i<n;i++) cin>>u>>v,e[u].emplace_back(v),e[v].emplace_back(u);
	dfs(1,0);
	ll res=0;
	for(int i=1;i<=n;i++) if(p[i].size()){
		sort(p[i].begin(),p[i].end(),[&](int u,int v){return dfn[u]<dfn[v];});
		q=p[i];
		int m=q.size();
		for(int j=1;j<m;j++) q.emplace_back(LCA(q[j],q[j-1]));
		q.emplace_back(1);
		sort(q.begin(),q.end(),[&](int u,int v){return dfn[u]<dfn[v];});
		m=unique(q.begin(),q.end())-q.begin();
		for(int j=0;j<p[i].size();j++) as[j].clear(),dp[j]=1e9;
		for(int j=0;j<m;j++){
			int _l=lower_bound(p[i].begin(),p[i].end(),dfn[q[j]],[&](int u,int v){return dfn[u]<v;})-p[i].begin();
			int _r=lower_bound(p[i].begin(),p[i].end(),R[q[j]]+1,[&](int u,int v){return dfn[u]<v;})-p[i].begin()-1;
			as[_r].emplace_back(_l,i-de[q[j]]+1);
		}
		for(int j=0;j<p[i].size();j++){
			for(auto [x,t]:as[j]){
				dp[j]=min(dp[j],(x==0?0:dp[x-1])+query(t,i));
			}
		}
		res+=dp[p[i].size()-1];
	}
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
	
	int Ca=1;
	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}
