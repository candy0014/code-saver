#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
int n,pw[200005];
int sz,cnt,vis[65];
ll d[65],id[65];
void insert(ll x){
	ll tmp=0;
	for(int i=60;i>=0;i--) if((x>>i)&1){
		if(!d[i]){d[i]=x,id[i]=tmp^(1ll<<sz),sz++,cnt++;return;}
		x^=d[i],tmp^=id[i];
	}
	for(int i=0;i<sz;i++) if(((tmp>>i)&1)&&!vis[i]) vis[i]=1,cnt--;
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n,pw[0]=1;
	for(int i=1;i<=n;i++) pw[i]=pw[i-1]*2%mod;
	for(ll i=1,x;i<=n;i++){
		cin>>x,insert(x);
		cout<<((pw[i]-1ll*pw[i-sz]*i+((i==cnt)?0:(1ll*(i-cnt)*pw[i-sz-1])))%mod+mod)%mod<<"\n";
	}
	return 0;
}