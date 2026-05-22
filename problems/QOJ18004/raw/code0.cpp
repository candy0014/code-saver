#include <bits/stdc++.h>
#include <cassert>
using namespace std;
typedef long long ll;
const ll mod=998244353,base=233;
ll ha[100005],pw[100005],pw2[100005];
ll ksm(ll u,ll v=mod-2){
	if(u==base) return pw2[v/100000]*pw[v%100000]%mod;
	ll tmp=1;u%=mod;while(v) tmp=tmp*((v&1)?u:1)%mod,u=u*u%mod,v>>=1;return tmp;
}
string s;
int m,n;
int len[100005],id[100005],tag[100005];
vector<int>p,res;
vector<ll>q;
ll calc(ll ha,int len,int c){
	ll t=ksm(base,len);
	return ha*(ksm(t,c)-1)%mod*ksm(t-1)%mod;
}
ll query(int x){
	if(x<=m) return ha[x];
	int t=lower_bound(p.begin(),p.end(),x)-p.begin()-1;
	return (calc(q[t],p[t],x/p[t])*ksm(base,x%p[t])+query(x%p[t]))%mod;
}
char get(int x){
	if(x<=m) return s[x];
	int t=lower_bound(p.begin(),p.end(),x)-p.begin()-1;
	x%=p[t];
	if(!x) x=p[t];
	return get(x);
}
int num;
void solve(){
	num++;
	cin>>s>>n,m=s.length(),s=" "+s;
	for(int i=1;i<=m;i++) ha[i]=(ha[i-1]*base+s[i])%mod;
	for(int i=1;i<=n;i++) cin>>len[i],id[i]=i,tag[i]=0;
	sort(id+1,id+n+1,[&](int u,int v){return len[u]<len[v];}),sort(len+1,len+n+1);
	p.clear(),q.clear();
	if(m<len[1]){
		p.emplace_back(m),q.emplace_back(ha[m]);
		p.emplace_back(len[1]),q.emplace_back((calc(ha[m],m,len[1]/m)*pw[len[1]%m]+ha[len[1]%m])%mod);
	}
	else p.emplace_back(len[1]),q.emplace_back(ha[len[1]]),m=len[1];
	tag[1]=tag[n]=1;
	for(int i=2;i<n;i++){
		int l=1,r=len[n],mid,res=0;
		ll nq=(calc(q.back(),p.back(),len[i]/p.back())*ksm(base,len[i]%p.back())+query(len[i]%p.back()))%mod;
		while(l<=r){
			mid=(l+r)>>1;
			ll ha1=query(mid);
			p.emplace_back(len[i]),q.emplace_back(nq);
			ll ha2=query(mid);
			p.pop_back(),q.pop_back();
			if(ha1==ha2) res=mid,l=mid+1;
			else r=mid-1;
		}
		if(res!=len[n]){
			char g1=get(res+1);
			p.emplace_back(len[i]);
			char g2=get(res+1);
			if(g2<=g1) p.pop_back();
			else q.emplace_back(nq),tag[i]=1;
		}
	}
	res.clear();
	for(int i=1;i<=n;i++) if(!tag[i]) res.emplace_back(id[i]);
	for(int i=1;i<=n;i++) if(tag[i]) res.emplace_back(id[i]);
	for(int i=0;i<n;i++) cout<<res[i]<<" \n"[i==n-1];
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	pw[0]=pw2[0]=1;
	for(int i=1;i<=100000;i++) pw[i]=pw[i-1]*base%mod;
	for(int i=1;i<=100000;i++) pw2[i]=pw2[i-1]*pw[100000]%mod;
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}
