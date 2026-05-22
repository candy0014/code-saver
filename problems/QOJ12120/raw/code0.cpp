#include <bits/stdc++.h>
using namespace std;
int n;
vector<int>e[2][500005];
int L[2][500005],R[2][500005],id[2][500005],fat[2][500005],sz[2][500005],num[2];
void dfs1(int u,int fa,int op){
	fat[op][u]=fa,sz[op][u]=1;
	for(auto v:e[op][u]) if(v!=fa) dfs1(v,u,op),sz[op][u]+=sz[op][v];
}
void dfs2(int u,int fa,int op){
	L[op][u]=++num[op],id[op][num[op]]=u;
	for(auto v:e[op][u]) if(v!=fa) dfs2(v,u,op);
	R[op][u]=num[op];
}
int get(int op,int u,int v){
	if(v==fat[op][u]) return n-sz[op][u];
	return sz[op][v];
}
vector<pair<pair<int,int>,int> >as[500005];
void add(int l1,int r1,int l2,int r2){
	if(l1>r1||l2>r2) return;
	// cout<<l1<<" "<<r1<<" "<<l2<<" "<<r2<<"\n";
	as[l1].emplace_back(make_pair(l2,r2),1);
	as[r1+1].emplace_back(make_pair(l2,r2),-1);
}
int res[500005];
struct BIT{
	int sum[500005];
	void add(int u,int k){while(u<=n)sum[u]+=k,u+=(u&(-u));}
	void add(int l,int r,int k){add(l,k),add(r+1,-k);}
	int query(int u){int t=0;while(u)t+=sum[u],u-=(u&(-u));return t;}
}b;
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int op:{0,1}) for(int i=1,u,v;i<n;i++) cin>>u>>v,e[op][u].emplace_back(v),e[op][v].emplace_back(u);
	dfs1(1,0,0),dfs1(1,0,1);
	for(int op:{0,1}) for(int u=1;u<=n;u++){
		sort(e[op][u].begin(),e[op][u].end(),[&](int a,int b){return get(op,u,a)<get(op,u,b);});
	}
	dfs2(1,0,0),dfs2(1,0,1);
	for(int u=1;u<=n;u++){
		for(int i=0,j=-1,flag=0,la=-1;i<(int)e[1][u].size();i++){
			int v=e[1][u][i];
			while(j+1<e[0][u].size()&&get(0,u,e[0][u][j+1])<get(1,u,v)){
				j++;int v=e[0][u][j];
				if(v==fat[0][u]) flag=1;
				else la=R[0][v];
			}
			if(j==-1) continue;
			if(!flag){
				if(v==fat[1][u]){
					add(L[0][u]+1,la,1,L[1][u]-1),add(L[0][u]+1,la,R[1][u]+1,n);
				}
				else{
					add(L[0][u]+1,la,L[1][v],R[1][v]);
				}
			}
			else{
				if(v==fat[1][u]){
					add(1,L[0][u]-1,1,L[1][u]-1),add(1,L[0][u]-1,R[1][u]+1,n);
					add(L[0][u]+1,la,1,L[1][u]-1),add(L[0][u]+1,la,R[1][u]+1,n);
					add(R[0][u]+1,n,1,L[1][u]-1),add(R[0][u]+1,n,R[1][u]+1,n);
				}
				else{
					add(1,L[0][u]-1,L[1][v],R[1][v]);
					add(L[0][u]+1,la,L[1][v],R[1][v]);
					add(R[0][u]+1,n,L[1][v],R[1][v]);
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(auto [x,k]:as[i]) b.add(x.first,x.second,k);
		// cout<<id[0][i]<<" "<<L[1][id[0][i]]<<"\n";
		res[id[0][i]]=b.query(L[1][id[0][i]]);
	}
	for(int i=1;i<=n;i++) cout<<res[i]<<" \n"[i==n];
	return 0;
}
