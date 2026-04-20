#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,ca,a[400005],L[400005],R[400005];
ll res[400005];
vector<pair<int,int> >as[400005];
vector<pair<pair<int,int>,int> >ch1;
vector<pair<int,int> >cc1[400005],cc2[400005];
int st[400005],top;
struct TREE{
	ll sum[400005],sum1[400005],al;
	void add(ll sum[],ll x,ll k){while(x<=n) sum[x]+=k,x+=(x&(-x));}
	void add(ll l,ll r,ll k){al+=k;add(sum,l,k),add(sum,r+1,-k),add(sum1,l,l*k),add(sum1,r+1,-(r+1)*k);}
	ll query(ll sum[],ll x){ll t=0;while(x)t+=sum[x],x-=(x&(-x));return t;}
	ll query(ll x){return (x+1)*query(sum,x)-query(sum1,x);}
}tr1,tr2;
ll pre[400005];
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>ca;
	for(int i=1;i<=n;i++) cin>>a[i],pre[i]=max(pre[i-1],1ll*a[i]);
	for(int i=1;i<=n;i++) pre[i]+=pre[i-1];
	for(int i=1;i<=n;i++){
		while(top&&a[i]>a[st[top]]) top--;
		L[i]=i-st[top],st[++top]=i;
	}
	st[0]=n+1,top=0;
	for(int i=n;i>=1;i--){
		while(top&&a[i]>=a[st[top]]) top--;
		R[i]=st[top]-i,st[++top]=i;
	}
	for(int i=1;i<=n;i++){
		// cout<<L[i]<<" "<<R[i]<<"\n";
		ch1.emplace_back(make_pair(1,i),a[i]);
		ch1.emplace_back(make_pair(L[i]+1,i),-a[i]);
		ch1.emplace_back(make_pair(R[i]+1,i+R[i]),-a[i]);
		ch1.emplace_back(make_pair(L[i]+R[i]+1,i+R[i]),a[i]);
	}
	for(auto [p,w]:ch1){
		// cout<<p.first<<" "<<p.second<<" "<<w<<"\n";
		cc1[p.first].emplace_back(p.second-1,-w);
		cc2[p.first].emplace_back(p.second-p.first+1,w);
	}
	for(int i=1,l,r,k;i<=ca;i++){
		cin>>k>>l>>r,k++;
		if(l<k) res[i]=pre[min(r,k-1)]-pre[l-1],l=k;
		if(l>r) continue;
		as[k].emplace_back(r,i);
		as[k].emplace_back(l-1,-i);
	}
	for(int i=1;i<=n;i++){
		for(auto [p,w]:cc1[i]) tr1.add(1,p,w);//,cout<<p<<" "<<w<<"!\n";
		for(auto [p,w]:cc2[i]) tr2.add(1,p,w);//,cout<<p<<" "<<w<<"?\n";
		for(auto [p,id]:as[i]){
			if(p==0) continue;
			ll tmp=tr1.query(p)+tr2.query(p-i+1)+tr2.al*(i-1);
			// cout<<tr1.query(1,1,n,1,p)<<"\n";
			if(id<0) res[-id]-=tmp;
			else res[id]+=tmp;
		}
	}
	for(int i=1;i<=ca;i++) cout<<res[i]<<"\n";
	return 0;
}