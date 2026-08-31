#include <bits/stdc++.h>
using namespace std;
int n,m;
vector<pair<int,int> >ee[1000005],e[1000005];
int du[1000005],dfn[1000005],num;
set<pair<int,int> >st;
vector<pair<int,int> >e2[1000005],e3[1000005];
int check1(int u,int v){
	int res=1e9;
	if(dfn[u]>dfn[v]) swap(u,v);
	for(auto [x,w]:e[u]) if(x==v) res=min(res,w);
	return res;
}
int check2(int u,int v){
	int res=check1(u,v);
	if(u>v) swap(u,v);
	auto tmp=lower_bound(e2[u].begin(),e2[u].end(),make_pair(v,0));
	if(tmp!=e2[u].end()&&(*tmp).first==v) res=min(res,(*tmp).second);
	for(auto [x,w]:e[u]) res=min(res,w+check1(x,v));
	for(auto [x,w]:e[v]) res=min(res,w+check1(x,u));
	return res;	
}
int check3(int u,int v){
	int res=check2(u,v);
	if(u>v) swap(u,v);
	auto tmp=lower_bound(e3[u].begin(),e3[u].end(),make_pair(v,0));
	if(tmp!=e3[u].end()&&(*tmp).first==v) res=min(res,(*tmp).second);
	for(auto [x,w]:e[u]) res=min(res,w+check2(x,v));
	for(auto [x,w]:e[v]) res=min(res,w+check2(x,u));
	return res;
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1,u,v,w;i<=m;i++) cin>>u>>v>>w,ee[u].emplace_back(v,w),ee[v].emplace_back(u,w),du[u]++,du[v]++;
	for(int i=1;i<=n;i++) st.insert(make_pair(du[i],i));
	for(int i=1;i<=n;i++){
		int u=(*st.begin()).second;st.erase(st.begin());
		dfn[u]=++num;
		for(auto [v,w]:ee[u]) if(!dfn[v]) st.erase(make_pair(du[v],v)),du[v]--,st.insert(make_pair(du[v],v));
	}
	for(int u=1;u<=n;u++) for(auto [v,w]:ee[u]) if(dfn[v]>dfn[u]) e[u].emplace_back(v,w);
	for(int i=1;i<=n;i++){
		for(int j=0;j<(int)e[i].size();j++) for(int k=j+1;k<(int)e[i].size();k++){
			int u=e[i][j].first,v=e[i][k].first;
			if(u>v) swap(u,v);
			e2[u].emplace_back(v,e[i][j].second+e[i][k].second);
		}
	}
	for(int i=1;i<=n;i++){
		for(auto [u,wu]:e[i]) for(auto [v,wv]:e[i]) if(u!=v) for(auto [x,wx]:e[v]){
			int a=u,b=x;
			if(a>b) swap(a,b);
			e3[a].emplace_back(b,wu+wv+wx);
		}
	}
	for(int i=1;i<=n;i++) sort(e2[i].begin(),e2[i].end()),sort(e3[i].begin(),e3[i].end());
	int ca;cin>>ca;while(ca--){
		int u,v;cin>>u>>v;
		int res=check3(u,v);
		if(res==1e9) res=-1;
		cout<<res<<"\n";
	}
	return 0;
}