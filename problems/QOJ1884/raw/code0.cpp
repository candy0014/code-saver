#include <bits/stdc++.h>
using namespace std;
int n,m,rt;
vector<int>e[200005];
int L[200005],R[200005],num;
vector<int>le;
void dfs(int u,int fa){
	L[u]=num;
	if(e[u].size()==1) num++,le.emplace_back(u);
	for(auto v:e[u]) if(v!=fa) dfs(v,u);
	R[u]=num-1;
}
vector<pair<int,int> >as[200005];
void solve(){
	cin>>n,m=0,num=0,le.clear();
	for(int i=1;i<=n;i++) e[i].clear();
	for(int i=1,u,v;i<n;i++) cin>>u>>v,e[u].emplace_back(v),e[v].emplace_back(u);
	if(n==2){cout<<"1 2\n1 2\n";return;}
	for(int i=1;i<=n;i++){
		if(e[i].size()==1) m++;
		else rt=i;
	}
	for(int i=0;i<m;i++) as[i].clear();
	dfs(rt,0);
	for(int i=1;i<=n;i++) if(i!=rt&&e[i].size()!=2){
		if((R[i]-L[i]+1)%2==0) as[(R[i]+L[i]+1)/2].emplace_back(i,(R[i]-L[i]+1)/2);
		if((m-R[i]+L[i]-1)%2==0) as[(R[i]+(m-R[i]+L[i]-1)/2+1)%m].emplace_back(i,(m-R[i]+L[i]-1)/2);
	}
	vector<pair<int,int> >res;
	for(int i=0;i<m;i++) if(as[i].size()<=1){
		int u=0,t=0;
		if(as[i].size()) u=as[i][0].first,t=as[i][0].second;
		for(int j=0;j<t;j++) res.emplace_back(le[(i+j)%m],le[(i-j-1+m)%m]);
		if(u) res.emplace_back(rt,u);
		for(int j=t;j<m/2;j++) res.emplace_back(le[(i+j)%m],le[(i-j-1+m)%m]);
		break;
	}
	while(res.size()<m/2+1) res.emplace_back(1,2);
	for(auto x:res) cout<<x.first<<" "<<x.second<<"\n";
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}