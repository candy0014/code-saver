#include <bits/stdc++.h>
#include <cassert>
using namespace std;
typedef long long ll;
int V1,V2;
int n;
ll lim;
int x[200005],xx[200005],y[200005],yy[200005],c[200005],res[4][200005];
struct TREE{
	int tot,ls[20000005],rs[20000005];
	ll ma[20000005],tag[20000005];
	void clear(){
		tot=1,ma[1]=tag[1]=ls[1]=rs[1]=0;
	}
	void update(int &p,ll t){
		if(!p) p=++tot,ls[p]=rs[p]=ma[p]=tag[p]=0;
		ma[p]+=t,tag[p]+=t;
	}
	void pushdown(int p){update(ls[p],tag[p]),update(rs[p],tag[p]),tag[p]=0;}
	void change(int p,int l,int r,int L,int R,ll k){
		if(r<L||l>R) return;
		if(L<=l&&r<=R){update(p,k);return;}
		int mid=(l+r)>>1;pushdown(p),change(ls[p],l,mid,L,R,k),change(rs[p],mid+1,r,L,R,k),ma[p]=max(ma[ls[p]],ma[rs[p]]);
	}
}tr;
void work(int op){
	vector<pair<int,int> >as;
	for(int i=1;i<=n;i++) as.emplace_back(x[i],i),as.emplace_back(xx[i]+1,-i);
	sort(as.begin(),as.end()),tr.clear();
	int tim=n;
	for(int j=0;j<(int)as.size();){
		int jj=j;
		while(jj<(int)as.size()&&as[jj].first==as[j].first){
			int i=as[jj++].second;
			if(abs(i)<=tim) tr.change(1,1,V2,y[abs(i)],yy[abs(i)],(i>0)?c[abs(i)]:-c[abs(i)]);
		}
		while(tr.ma[1]>=lim){
			res[op][tim]=as[j].first;
			if(x[tim]<=as[j].first&&as[j].first<=xx[tim]) tr.change(1,1,V2,y[tim],yy[tim],-c[tim]);
			tim--;
		}
		j=jj;
	}
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>V1>>V2>>n>>lim;
	for(int i=1;i<=n;i++) cin>>x[i]>>xx[i]>>y[i]>>yy[i]>>c[i];
	work(0);
	for(int i=1;i<=n;i++) x[i]=V1-x[i]+1,xx[i]=V1-xx[i]+1,swap(x[i],xx[i]);
	work(1),swap(V1,V2);
	for(int i=1;i<=n;i++) swap(x[i],y[i]),swap(xx[i],yy[i]);
	work(2);
	for(int i=1;i<=n;i++) x[i]=V1-x[i]+1,xx[i]=V1-xx[i]+1,swap(x[i],xx[i]);
	work(3);
	for(int i=1;i<=n;i++){
		if(!res[0][i]) cout<<"0\n";
		else cout<<1ll*((V2-res[1][i]+1)-res[0][i]+1)*((V1-res[3][i]+1)-res[2][i]+1)<<"\n";
	}
	return 0;
}