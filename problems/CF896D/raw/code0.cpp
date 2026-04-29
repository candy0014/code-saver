#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,mod,l,r;
ll ksm(ll u,ll v=mod-2){ll tmp=1;u%=mod;while(v) tmp=tmp*((v&1)?u:1)%mod,u=u*u%mod,v>>=1;return tmp;}
vector<int>p,q;
int m;
void exgcd(int a,int b,ll &x,ll &y){
	if(b==0) x=1,y=0;
	else exgcd(b,a%b,y,x),y-=a/b*x;
}
int Inv(int a){
 	ll x,y;
 	exgcd(a,mod,x,y);
 	return (x%mod+mod)%mod;
}
struct DATA{
	int x;
	vector<int>g;
	DATA(int a=0){
		for(int i=0;i<m;i++){
			int cnt=0;
			while(a%p[i]==0) a/=p[i],cnt++;
			g.emplace_back(cnt);
		}
		x=a;
	}
	DATA operator*(const DATA &rs)const{
		DATA res(1);res.x=1ll*x*rs.x%mod;
		res.g.resize(m);
		for(int i=0;i<m;i++) res.g[i]=g[i]+rs.g[i];
		return res;
	}
	DATA operator/(const DATA &rs)const{
		DATA res(1);res.x=1ll*x*Inv(rs.x)%mod,res.g.resize(m);
		for(int i=0;i<m;i++) res.g[i]=g[i]-rs.g[i];
		return res;
	}
	int get(){
		int res=x;
		for(int i=0;i<m;i++) res=1ll*res*ksm(p[i],g[i])%mod;
		return res;
	}
};
DATA jie[100005];
int C(int u,int v){
	if(u<v||v<0) return 0;
	return (jie[u]/jie[v]/jie[u-v]).get();
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>mod>>l>>r;
	int tmp=mod;
	for(int i=2;i*i<=tmp;i++) if(tmp%i==0){
		int cnt=0;
		while(tmp%i==0) tmp/=i,cnt++;
		p.emplace_back(i),q.emplace_back(cnt);
	}
	if(tmp>1) p.emplace_back(tmp),q.emplace_back(1);
	m=p.size();
	jie[0]=DATA(1);
	for(int i=1;i<=n;i++) jie[i]=jie[i-1]*DATA(i);
	ll res=0;
	for(int i=l;i<=n;i++){
		int L=max(0,(i-r+1)/2),R=(i-l)/2;
		if(L>R) continue;
		res=(res+1ll*C(n,i)*(C(i,R)-C(i,L-1)))%mod;
	}
	cout<<(res%mod+mod)%mod<<"\n";
	return 0;
}