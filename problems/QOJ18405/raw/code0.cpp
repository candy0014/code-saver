#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define pb push_back
#define ft first
#define sd second
#define mp make_pair
#define gc getchar
#define pc putchar
#define ls (k<<1)
#define rs (k<<1|1)
constexpr long long INF=1e18;
ll rd(){
    char c=gc(),f=0;ll x=0;for(;!isdigit(c);c=gc())if(c=='-')f=1;
    for(;isdigit(c);c=gc())x=x*10+c-'0';return f?-x:x;
}
void wt(ll x){if(x<0)x=-x,pc('-');if(x>9)wt(x/10);pc(x%10+'0');}
void gmi(ll &x,ll y){if(x>y)x=y;}
ll n,ca,a[400005];
struct line{
	ll k,b;
	void ad(ll x){b+=k*x;}
	line operator +(const line&a)const{return (line){k+a.k,b+a.b};}
	bool operator <(const line&a)const{return k<a.k||k==a.k&&b<a.b;}
};
using pll=pair<line,ll>;
auto merge(line x,line y){
	if(x<y)swap(x,y);
	if(x.b>=y.b)return mp(x,INF);
	return mp(y,(y.b-x.b)/(x.k-y.k));
}
struct node{
	line mx,sum,l,r;
	ll v,tag;
	node operator +(const node&a)const{
		node x;pll t;
		x.sum=sum+a.sum,x.v=min(v,a.v),x.tag=0;
		t=merge(l,sum+a.l),x.l=t.ft,gmi(x.v,t.sd);
		t=merge(a.r,a.sum+r),x.r=t.ft,gmi(x.v,t.sd);
		t=merge(mx,a.mx),x.mx=t.ft,gmi(x.v,t.sd);
		t=merge(x.mx,r+a.l),x.mx=t.ft,gmi(x.v,t.sd);
		return x;
	}
}t[1600005];
void build(ll k,ll l,ll r){
	if(l==r){
		t[k].v=INF;
		t[k].l=t[k].r=t[k].mx=t[k].sum=(line){1,a[l]};
		return;
	}
	ll mid=l+r>>1;
	build(ls,l,mid),build(rs,mid+1,r);
	t[k]=t[ls]+t[rs];
}
void upd(ll k,ll v){
	t[k].tag+=v,t[k].v-=v;
	t[k].l.ad(v),t[k].r.ad(v),t[k].mx.ad(v),t[k].sum.ad(v);
}
void pushdown(ll k){
	if(t[k].tag)upd(ls,t[k].tag),upd(rs,t[k].tag),t[k].tag=0;
}
void dfs(ll k,ll l,ll r){
	if(t[k].v>=0)return;
	pushdown(k);
	ll mid=l+r>>1;
	dfs(ls,l,mid),dfs(rs,mid+1,r);
	t[k]=t[ls]+t[rs];
}
void U(ll k,ll l,ll r,ll x,ll y,ll v){
	if(x<=l&&r<=y){
		upd(k,v),dfs(k,l,r);
		return;
	}
	pushdown(k);
	ll mid=l+r>>1;
	if(x<=mid)U(ls,l,mid,x,y,v);
	if(y>mid)U(rs,mid+1,r,x,y,v);
	t[k]=t[ls]+t[rs];
}
node Q(ll k,ll l,ll r,ll x,ll y){
	if(x<=l&&r<=y)return dfs(k,l,r),t[k];
	pushdown(k);
	ll mid=l+r>>1;
	if(x<=mid){
		if(y>mid)return Q(ls,l,mid,x,y)+Q(rs,mid+1,r,x,y);
		return Q(ls,l,mid,x,y);
	}
	return Q(rs,mid+1,r,x,y);
}
ll res[400005];
vector<pair<ll,int> >as;
void solve(){
	n=rd(),ca=rd();
	for(int i=1;i<=n;i++) a[i]=rd();
	as.clear();
	for(int i=1,x;i<=ca;i++) x=rd(),as.emplace_back(x,i);
	sort(as.begin(),as.end());
	for(int i=1;i<=n;i++) a[i]+=as[0].first;
	build(1,1,n);
	for(int i=ca-1;i>=1;i--) as[i].first-=as[i-1].first;
	as[0].first=0;
	for(int i=0;i<ca;i++){
		U(1,1,n,1,n,as[i].first);
		res[as[i].second]=Q(1,1,n,1,n).mx.b;
	}
	for(int i=1;i<=ca;i++) cout<<res[i]<<" \n"[i==ca];
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	int Ca=rd();while(Ca--)solve();
	return 0;
}