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
char op;
int n,rt,k,son[1000005][2],vis[1000005],fa[1000005];
void dfs1(int u){
	if(!u) return;
	cout<<u<<" ";
	if(son[u][0]<=son[u][1]||!k) dfs1(son[u][0]),dfs1(son[u][1]);
	else k--,dfs1(son[u][1]),dfs1(son[u][0]);
}
vector<int>p;
void dfs2(int u){
	if(!u) return;
	if(!son[u][0]&&!son[u][1]) p.emplace_back(u);
	dfs2(son[u][0]),dfs2(son[u][1]);
}
void dfs3(int u,int l,int r){
	if(l+1==r){cout<<u<<" ";return;}
	int mi=1e9,mik=0;
	for(int i=l;i<r;i++) if(__builtin_popcount(i-l)<=k){
		if(p[i]<mi) mi=p[i],mik=i;
	}
	int mid=(l+r)>>1;
	if(mik<mid){
		dfs3(son[u][0],l,mid);
		if(op=='B') cout<<u<<" ";
		dfs3(son[u][1],mid,r);
		if(op=='C') cout<<u<<" ";
	}
	else{
		k--,dfs3(son[u][1],mid,r);
		if(op=='B') cout<<u<<" ";
		dfs3(son[u][0],l,mid);
		if(op=='C') cout<<u<<" ";
	}
}
void solve(int Ca){
	cin>>op>>n>>rt>>k;
	for(int i=1;i<=n;i++) cin>>son[i][0]>>son[i][1],fa[son[i][0]]=fa[son[i][1]]=i;
	if(op=='A'){
		dfs1(rt);return;
	}
	fa[0]=0;
	dfs2(rt);
	dfs3(rt,0,n/2+1);
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
//	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}