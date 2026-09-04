#include <bits/stdc++.h>
using namespace std;
int n,ca;
int x[500005],y[500005],xx[500005],yy[500005];
int li[1000005],tot,X,Y;
vector<pair<pair<int,int>,int> >as[1000005];
int fat[500005][20];
vector<int>e[500005];
struct TREE{
	int tag[4000005];
	void pushdown(int p){
		if(tag[p]==-1) return;
		tag[p*2]=tag[p*2+1]=tag[p],tag[p]=-1;
	}
	void change(int p,int l,int r,int L,int R,int k){
		if(r<L||l>R) return;
		if(L<=l&&r<=R){tag[p]=k;return;}
		int mid=(l+r)>>1;pushdown(p),change(p*2,l,mid,L,R,k),change(p*2+1,mid+1,r,L,R,k);
	}
	int query(int p,int l,int r,int x){
		if(l==r) return tag[p];
		int mid=(l+r)>>1;pushdown(p);
		if(x<=mid) return query(p*2,l,mid,x);
		return query(p*2+1,mid+1,r,x);
	}
}tr;
int L[500005],R[500005],num=-1,de[500005];
void dfs(int u,int fa){
	L[u]=++num,de[u]=de[fa]+1;
	for(int i=1;i<20;i++) fat[u][i]=fat[fat[u][i-1]][i-1];
	for(auto v:e[u]) if(v!=fa) dfs(v,u);
	R[u]=num;
}
struct BIT{
	int sum[500005];
	void add(int x,int k){while(x<=n)sum[x]+=k,x+=(x&(-x));}
	void add(int l,int r,int k){add(l,k),add(r+1,-k);}
	int query(int x){int t=0;while(x)t+=sum[x],x-=(x&(-x));return t;}
	int query(int l,int r){return query(r)-query(l-1);}
}b,res;
int tag[500005];
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>ca;
	for(int i=1;i<=n;i++) cin>>x[i]>>y[i]>>xx[i]>>yy[i];
	for(int i=1;i<=n;i++) li[++tot]=x[i],li[++tot]=xx[i];
	sort(li+1,li+tot+1),X=tot=unique(li+1,li+tot+1)-li-1;
	for(int i=1;i<=n;i++) x[i]=lower_bound(li+1,li+tot+1,x[i])-li,xx[i]=lower_bound(li+1,li+tot+1,xx[i])-li;
	tot=0;
	for(int i=1;i<=n;i++) li[++tot]=y[i],li[++tot]=yy[i];
	sort(li+1,li+tot+1),Y=tot=unique(li+1,li+tot+1)-li-1;
	for(int i=1;i<=n;i++) y[i]=lower_bound(li+1,li+tot+1,y[i])-li,yy[i]=lower_bound(li+1,li+tot+1,yy[i])-li;
	for(int i=1;i<=n;i++) as[x[i]].emplace_back(make_pair(y[i],yy[i]),i),as[xx[i]].emplace_back(make_pair(y[i],yy[i]),-i);
	for(int i=1;i<=X;i++){
		for(auto [x,id]:as[i]){
			if(id>0){
				fat[id][0]=tr.query(1,1,Y,x.first),e[fat[id][0]].emplace_back(id);
				tr.change(1,1,Y,x.first,x.second,id);
			}
			else{
				tr.change(1,1,Y,x.first,x.second,fat[-id][0]);
			}
		}
	}
	de[0]=-1,dfs(0,0);
	while(ca--){
		char op;int x;
		cin>>op>>x;
		if(op=='^'){
			if(!tag[x]){
				if(!b.query(L[x],R[x])){
					int y=x;
					for(int i=19;i>=0;i--) if(fat[y][i]&&!b.query(L[fat[y][i]],R[fat[y][i]])) y=fat[y][i];
					res.add(de[y],de[x],1);
				}
				tag[x]=1,b.add(L[x],1);
			}
			else{
				tag[x]=0,b.add(L[x],-1);
				if(!b.query(L[x],R[x])){
					int y=x;
					for(int i=19;i>=0;i--) if(fat[y][i]&&!b.query(L[fat[y][i]],R[fat[y][i]])) y=fat[y][i];
					res.add(de[y],de[x],-1);
				}
			}
		}
		else cout<<res.query(x+1)<<"\n";
	}
	return 0;
}