#include <bits/stdc++.h>
#include <cassert>
using namespace std;
int ID,n,m,k,ca;
map<int,int>mp[200005],g[200005];
set<pair<int,int> >p;
int get(int x,int y){
	if(!mp[x].count(y)) return 0;
	int t[3][3]={0,0,0,0,0,0,0,0,0};
	for(int dx:{-1,0,1}) for(int dy:{-1,0,1}) t[dx+1][dy+1]=mp[x+dx].count(y+dy);
	if((!t[0][1]&&!t[2][1])||(!t[1][0]&&!t[1][2])) return 0;
	for(int dx:{0,1}) for(int dy:{0,1}) if(t[dx][dy]&&t[dx][dy+1]&&t[dx+1][dy]&&t[dx+1][dy+1]) return 1;
	return 2;
}
struct TREE{
	int ls[10000005],rs[10000005],lc[10000005],rc[10000005],res[10000005],cnt;
	void pushup(int p,int l,int r){
		int mid=(l+r)>>1;
		if(!ls[p]){
			lc[p]=-1;
			if(rc[rs[p]]!=r-mid) rc[p]=rc[rs[p]];
			else rc[p]=-1;
			res[p]=res[rs[p]];
			return;
		}
		if(!rs[p]){
			rc[p]=-1;
			if(lc[ls[p]]!=mid-l+1) lc[p]=lc[ls[p]];
			else lc[p]=-1;
			res[p]=res[ls[p]];
			return;
		}
		lc[p]=lc[ls[p]],rc[p]=rc[rs[p]],res[p]=res[ls[p]]+res[rs[p]];
		if(lc[p]==mid-l+1){
			if(lc[rs[p]]==-1) lc[p]=-1;
			else lc[p]+=lc[rs[p]];
		}
		if(rc[p]==r-mid){
			if(rc[ls[p]]==-1) rc[p]=-1;
			else rc[p]+=rc[ls[p]];
		}
		if(rc[ls[p]]!=-1&&rc[ls[p]]!=mid-l+1&&lc[rs[p]]!=-1&&lc[rs[p]]!=r-mid){
			res[p]+=rc[ls[p]]+lc[rs[p]];
		}
	}
	int change(int p,int l,int r,int x,int k){
		if(!p) p=++cnt;
		if(l==r){
			res[p]=(k==1),lc[p]=rc[p]=k-1;
			return p;
		}
		int mid=(l+r)>>1;
		if(x<=mid) ls[p]=change(ls[p],l,mid,x,k);
		else rs[p]=change(rs[p],mid+1,r,x,k);
		pushup(p,l,r);
		return p;
	}
}tr;
int rt1[400005],rt2[400005];
int res,cnt;
void change(int x,int y,int k){
	if(g[x][y]==k) return;
	if(g[x][y]==1) cnt--;
	if(k==1) cnt++;
	g[x][y]=k;
	res-=tr.res[rt1[x+y]],rt1[x+y]=tr.change(rt1[x+y],1,m,y,k),res+=tr.res[rt1[x+y]];
	res-=tr.res[rt2[x-y+m]],rt2[x-y+m]=tr.change(rt2[x-y+m],1,m,y,k),res+=tr.res[rt2[x-y+m]];
}
void flip(int x,int y){
	if(mp[x].count(y)) mp[x].erase(y),p.erase(make_pair(x,y));
	else mp[x][y]=1,p.insert(make_pair(x,y));
	for(int dx:{-1,0,1}) for(int dy:{-1,0,1}) change(x+dx,y+dy,get(x+dx,y+dy));
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>/*ID>>*/n>>m>>k>>ca;
	for(int i=1,x,y;i<=k;i++) cin>>x>>y,flip(x,y);
	cout<<p.size()-(res-cnt)<<"\n";
	for(int i=1,x,y;i<=ca;i++){
		cin>>x>>y,flip(x,y);
		cout<<p.size()-(res-cnt)<<"\n";
	}
	return 0;
}