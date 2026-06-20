#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7,N=1000005;
ll ksm(ll u,ll v=mod-2){ll tmp=1;u%=mod;while(v) tmp=tmp*((v&1)?u:1)%mod,u=u*u%mod,v>>=1;return tmp;}
ll jie[N],inv[N];
void init(int n=N-3){
	jie[0]=1;
	for(int i=1;i<=n;i++) jie[i]=1ll*jie[i-1]*i%mod;
	inv[n]=ksm(jie[n],mod-2);
	for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
ll A(ll u,ll v){
	if(v<0||v>u) return 0;
	return 1ll*jie[u]*inv[u-v]%mod;
}
ll C(ll u,ll v){
	if(v<0||v>u) return 0;
	return 1ll*jie[u]*inv[v]%mod*inv[u-v]%mod;
}
int n,ca,a[300005],res[300005];
int st[300005],head,tail;
int st2[300005],head2,tail2;
int la,la_pos;
vector<pair<int,int> >as[300005];
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	init();
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	cin>>ca;
	for(int i=1,l,r;i<=ca;i++) cin>>l>>r,as[l].emplace_back(r,i);
	la=n+1,la_pos=n+1,head=1,head2=1;
	for(int i=n,R=n;i>=1;i--){
		int tmp=tail;
		while(head<=tail&&a[st[tail]]<a[i]) tail--;
		for(int i=tail+1;i<=tmp;i++){
			int p=st[i];
			if(a[p]<la) la=a[p],la_pos=p,st2[++tail2]=p;
			else R=la_pos-1,la=a[p],la_pos=p,head2=tail2=1,st2[1]=p;
		}
		st[++tail]=i;
		while(head<=tail&&st[head]>R) head++;
		while(head2<=tail2&&st2[head2]>R) head2++;
		for(auto [r,id]:as[i]){
			if(r>R) continue;
			int x=lower_bound(st+head,st+tail+1,r,[&](int u,int v){return u>v;})-st;
			int y=lower_bound(st2+head2,st2+tail2+1,r,[&](int u,int v){return u>v;})-st2;
			if(y<=tail2){
				int z=lower_bound(st+head,st+tail+1,st2[y],[&](int u,int v){return a[u]>a[v];})-st;
				if((tail-z+1)+(tail2-y+1)!=a[st2[y]]) continue;
			}
			int c=a[st[x]]-(r-i+1),m=n-a[st[x]];
			if(m==0&&c==0) res[id]=1;
			else res[id]=C(2*m+c-1,m)-C(2*m+c-1,m-2);
		}
	}
	for(int i=1;i<=ca;i++) cout<<(res[i]+mod)%mod<<"\n";
	return 0;
}