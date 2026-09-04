#include <bits/stdc++.h>
using namespace std;
int n,m,k;
vector<int>e[50005];
vector<pair<int,int> >ee;
int du[50005],tag[50005];
set<pair<int,int> >st;
int co[50005];
mt19937 rd(time(0));
void solve(){
	cin>>n>>m>>k,ee.resize(m);
	for(int i=1;i<=n;i++) e[i].clear(),du[i]=0,tag[i]=0;
	for(int i=0;i<m;i++) cin>>ee[i].first>>ee[i].second;
	while(1){
		for(int i=1;i<=n;i++) co[i]=rd()%2;
		int cnt=0;
		for(auto [u,v]:ee) cnt+=co[u]^co[v];
		if(cnt>=n*k) break;
	}
	for(auto [u,v]:ee) if(co[u]^co[v]) e[u].emplace_back(v),e[v].emplace_back(u),du[u]++,du[v]++;
	st.clear();
	for(int i=1;i<=n;i++) st.insert(make_pair(du[i],i));
	while(st.size()){
		int u=(*st.begin()).second;
		if(du[u]>k) break;
		st.erase(st.begin()),tag[u]=1;
		for(auto v:e[u]) if(!tag[v]){
			st.erase(make_pair(du[v],v)),du[v]--;
			st.insert(make_pair(du[v],v));
		}
	}
	vector<int>res[2];
	for(int i=1;i<=n;i++) if(!tag[i]) res[co[i]].emplace_back(i);
	for(int op:{0,1}){
		cout<<res[op].size();
		for(int u:res[op]) cout<<" "<<u;
		cout<<"\n";
	}
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}