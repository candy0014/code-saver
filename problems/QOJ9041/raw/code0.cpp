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
int n,m;
vector<int>e[500005];
vector<int>p[500005];
vector<pair<int,int> >q[500005];
int cnt;
int dfn[500005],low[500005],num,scc[500005];
stack<int>st;
int res;
vector<int>_e[500005];
void update(int x){
	if(res==-1||x==-1){res=-1;return;}
	if(!x) return;
	if(!res) res=x;
	else if(res!=x) res=-1;
}
void dfs(int u,int fa,int ed,int de){
	if(u==ed){update(de*2);return;}
	for(auto v:_e[u]) if(v!=fa) dfs(v,u,ed,de+1);
}
void work(vector<int>&p,vector<pair<int,int> >&q){
	if(res==-1) return;
	if(p.size()==2) return;
	for(auto u:p) _e[u].clear();
	for(auto [u,v]:q) _e[u].emplace_back(v),_e[v].emplace_back(u);
	int rt1=0,rt2=0;
	for(auto u:p) if(_e[u].size()!=2){
		if(rt1==0) rt1=u;
		else if(rt2==0) rt2=u;
		else{res=-1;return;}
	}
	if(!rt1){update(p.size());return;}
	if(!rt2||_e[rt1].size()!=_e[rt2].size()){update(-1);return;}
	dfs(rt1,0,rt2,0);
}
void tarjan(int u){
	st.push(u),dfn[u]=low[u]=++num;
	for(auto v:e[u]){
		if(!dfn[v]){
			tarjan(v),low[u]=min(low[u],low[v]);
			if(low[v]==dfn[u]){
				++cnt,p[cnt].clear(),q[cnt].clear();
				while(1){
					int tmp=st.top();st.pop();
					p[cnt].emplace_back(tmp);
					scc[tmp]=cnt;
					if(tmp==v) break;
				}
				p[cnt].emplace_back(u);
			}
		}
		else low[u]=min(low[u],dfn[v]);
	}
}
void solve(int Ca){
	cin>>n>>m,res=0,num=0,cnt=0;
	for(int i=1;i<=n;i++) e[i].clear(),dfn[i]=0;
	for(int i=1,u,v;i<=m;i++) cin>>u>>v,e[u].emplace_back(v),e[v].emplace_back(u);
	for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i),st.pop();
	for(int i=1;i<=n;i++) for(auto v:e[i]) if(dfn[v]<dfn[i]){
		q[scc[i]].emplace_back(i,v);
	}
	for(int i=1;i<=cnt;i++) work(p[i],q[i]);
	if(res==-1) cout<<"No\n";
	else cout<<"Yes\n";
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