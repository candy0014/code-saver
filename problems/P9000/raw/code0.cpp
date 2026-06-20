#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll inf=2e18;
const int V=1e9;
int tot=1;
struct TREE{
	ll mi[10000005],ma[10000005],res[10000005],tag[10000005];
	int ls[10000005],rs[10000005],cnt[10000005];
	void pushup(int p){
		if(!ls[p]) res[p]=res[rs[p]],mi[p]=mi[rs[p]],ma[p]=ma[rs[p]];
		if(!rs[p]) res[p]=res[ls[p]],mi[p]=mi[ls[p]],ma[p]=ma[ls[p]];
		if(ls[p]&&rs[p]){
			res[p]=max({res[rs[p]],res[ls[p]],ma[rs[p]]-mi[ls[p]]});
			mi[p]=min(mi[ls[p]],mi[rs[p]]);
			ma[p]=max(ma[ls[p]],ma[rs[p]]);
		}
		cnt[p]=cnt[ls[p]]+cnt[rs[p]];
	}
	void update(int p,ll t){if(p)tag[p]+=t,mi[p]+=t,ma[p]+=t;}
	void pushdown(int p){update(ls[p],tag[p]),update(rs[p],tag[p]),tag[p]=0;}
	void change(int p,int l,int r,int L,int R,ll k){
		if(!p||r<L||l>R||L>R) return;
		if(L<=l&&r<=R){update(p,k);return;}
		int mid=(l+r)>>1;
		pushdown(p),change(ls[p],l,mid,L,R,k),change(rs[p],mid+1,r,L,R,k),pushup(p);
	}
	int query(int p,int l,int r,int L,int R){
		if(!p||r<L||l>R||L>R) return 0;
		if(L<=l&&r<=R) return cnt[p];
		int mid=(l+r)>>1;pushdown(p);return query(ls[p],l,mid,L,R)+query(rs[p],mid+1,r,L,R);
	}
	int insert(int p,int l,int r,int x,ll k){
		if(!p) p=++tot;
		if(l==r){
			if(!cnt[p]) mi[p]=ma[p]=k,cnt[p]=1;
			else mi[p]=min(mi[p],k),ma[p]=max(ma[p],k),cnt[p]++,res[p]=ma[p]-mi[p];
			return p;
		}
		int mid=(l+r)>>1;pushdown(p);
		if(x<=mid) ls[p]=insert(ls[p],l,mid,x,k);
		else rs[p]=insert(rs[p],mid+1,r,x,k);
		pushup(p);
		return p;
	}
}tr;
int n,ca,d;
void insert(int x){
	int c=tr.query(1,1,V,1,x-1);
	tr.change(1,1,V,x,V,d),tr.insert(1,1,V,x,1ll*c*d-x);
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>ca>>d;
	for(int i=1,u;i<=n;i++) cin>>u,insert(u);
	while(ca--){
		int u;cin>>u;insert(u);
		ll res=tr.res[1];
		if(res&1) cout<<res/2<<".5 ";
		else cout<<res/2<<" ";
	}
	cout<<"\n";
	return 0;
}