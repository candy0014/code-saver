#include <bits/stdc++.h>
using namespace std;
int n;
vector<int>e[100005];
int L[100005],R[100005],num,de[100005],mi[100005][20];
int getmi(int u,int v){return L[u]<L[v]?u:v;}
void dfs(int u,int fa){
	L[u]=++num,de[u]=de[fa]+1,mi[L[u]][0]=fa;
	for(auto v:e[u]) if(v!=fa) dfs(v,u);
	R[u]=num;
	if(u==1) for(int j=1;j<20;j++) for(int i=1;i+(1<<j)-1<=n;i++) mi[i][j]=getmi(mi[i][j-1],mi[i+(1<<(j-1))][j-1]);
}
int LCA(int u,int v){
	if(u==v) return u;
	if((u=L[u])>(v=L[v])) swap(u,v);
	int t=__lg(v-u++);
	return getmi(mi[u][t],mi[v-(1<<t)+1][t]);
}
int dis(int u,int v){return de[u]+de[v]-de[LCA(u,v)]*2;}
vector<pair<int,int> >ee[100005];
vector<pair<int,int> >as1[100005],as2[100005];
bool chk(int u,int v,int w){return dis(u,w)+dis(w,v)==dis(u,v);}
vector<pair<pair<int,int>,int> >as[100005];
void add(int l1,int r1,int l2,int r2,int w){
	if(r2<1||l2>n) return;
	if(l1>l2) swap(l1,l2),swap(r1,r2);
	as[l2].emplace_back(make_pair(l1,r1),w),as[r2+1].emplace_back(make_pair(l1,r1),-w);
}
struct TREE{
	int ma[400005],tag[400005];
	void init(){for(int i=1;i<=n*4;i++) ma[i]=tag[i]=0;}
	void pushdown(int p){tag[p*2]+=tag[p],tag[p*2+1]+=tag[p],ma[p*2]+=tag[p],ma[p*2+1]+=tag[p],tag[p]=0;}
	void change(int p,int l,int r,int L,int R,int k){
		if(r<L||l>R) return;
		if(L<=l&&r<=R){tag[p]+=k,ma[p]+=k;return;}
		int mid=(l+r)>>1;pushdown(p),change(p*2,l,mid,L,R,k),change(p*2+1,mid+1,r,L,R,k),ma[p]=max(ma[p*2],ma[p*2+1]);
	}
}tr;
bool check(int g){
	for(int i=1;i<=n;i++) as[i].clear();
	for(int i=0;i<=g;i++){
		for(auto [u,v]:as1[i]){
			int l1=L[u],r1=R[u],l2=L[abs(v)],r2=R[abs(v)];
			if(v<0) add(l1,r1,r2+1,n,1),add(l1,r1,1,l2-1,1);
			else add(l1,r1,l2,r2,1);
			// cout<<u<<" "<<v<<" 1\n";
		}
		for(auto [u,v]:as2[i]){
			int l1=L[u],r1=R[u],l2=L[abs(v)],r2=R[abs(v)];
			if(v<0) add(l1,r1,r2+1,n,-1),add(l1,r1,1,l2-1,-1);
			else add(l1,r1,l2,r2,-1);
			// cout<<u<<" "<<v<<" -1\n";
		}
		// cout<<"\n";
	}
	tr.init();
	for(int i=1;i<=n;i++){
		for(auto [x,w]:as[i]) tr.change(1,1,n,x.first,x.second,w);
		if(tr.ma[1]==g+1) return 1;
	}
	return 0;
}
void solve(){
	cin>>n,num=0;
	for(int i=1;i<=n;i++) e[i].clear();
	for(int i=0;i<n;i++) ee[i].clear(),as1[i].clear(),as2[i].clear();
	for(int i=1,u,v,w;i<n;i++) cin>>u>>v>>w,e[u].emplace_back(v),e[v].emplace_back(u),ee[w].emplace_back(u,v);
	dfs(1,0);
	for(int i=0;i<n;i++){
		for(auto [u,v]:ee[i]){
			if(de[v]>de[u]) swap(u,v);
			as1[i].emplace_back(u,-u);
		}
		for(int j=0;j<(int)ee[i].size();j++){
			for(int k=j+1;k<(int)ee[i].size();k++){
				int u1=ee[i][j].first,v1=ee[i][j].second;
				int u2=ee[i][k].first,v2=ee[i][k].second;
				int u,v,ma=-1;
				for(int uu:{u1,v1}) for(int vv:{u2,v2}) if(dis(uu,vv)>ma) ma=dis(uu,vv),u=uu,v=vv;
				int cnt=0;
				for(int p=0;p<(int)ee[i].size();p++) cnt+=chk(u,v,ee[i][p].first)&&chk(u,v,ee[i][p].second);
				if(cnt>2) continue;
				if(de[u]<de[v]) swap(u,v),swap(u1,u2),swap(v1,v2);
				if(LCA(u,v)==v) as2[i].emplace_back(u,-(u2+v2-v));
				else as2[i].emplace_back(u,v);
			}
		}
	}
	// cout<<check(3)<<"\n";
	int l=0,r=n-1,mid,ans=0;
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid)) ans=mid+1,l=mid+1;
		else r=mid-1;
	}
	cout<<ans<<"\n";
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;	
}