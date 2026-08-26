#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7,N=2000005;
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
	if(u==-1&&v==0) return 1;
	if(v<0||v>u) return 0;
	return 1ll*jie[u]*inv[v]%mod*inv[u-v]%mod;
}
ll C(int a,int b,int c,int d){
	return 1ll*jie[a+b+c+d]*inv[a]%mod*inv[b]%mod*inv[c]%mod*inv[d]%mod;
}
int ID;
string s;
int cnt[3][3],g[3][3],c[3];
int work(int t,int op=0){
	int res=0;
	for(int i=0;i<=cnt[0][1]&&i<=cnt[1][2]&&i<=cnt[2][0];i++){
		for(int p=0;p<3;p++) for(int q=0;q<3;q++) g[p][q]=cnt[(p+t)%3][(q+t)%3];
		g[0][1]-=i,g[1][2]-=i,g[2][0]-=i;
		int j=g[1][0]-g[0][1];
		g[0][2]-=j,g[2][1]-=j,g[1][0]-=j;
		if(j<0||g[0][1]!=g[1][0]||g[1][2]!=g[2][1]||g[0][2]!=g[2][0]) continue;
		int x=g[0][1],y=g[2][0],z=g[1][2];
		// cout<<i<<" "<<j<<" "<<x<<" "<<y<<"\n";
		res=(res+1ll*C(i,j,x,y)*C(i+j+x+y+z+op-1,z))%mod;
	}
	// cout<<res<<"\n";
	for(int p=0;p<3;p++) res=1ll*res*C(c[p]+(p==t)+cnt[p][p]-1,cnt[p][p])%mod;
	return res;
}
void solve(){
	cin>>s,memset(cnt,0,sizeof(cnt));
	if(s.length()==1){cout<<"3\n";return;}
	for(int i=1;s[i];i++) cnt[s[i-1]-'a'][s[i]-'a']++;
	int flag=1;
	for(int i=1;s[i];i++) flag&=(s[i]==s[0]);
	if(flag){cout<<"1\n";return;}
	c[0]=c[1]=c[2]=0;
	for(int i=1;s[i];i++) if(s[i]!=s[i-1]) c[s[i]-'a']++;
	if(s[0]==s.back()){
		int res=0;
		for(int t=0;t<3;t++) if(c[t]) res=(res+work(t))%mod;
		cout<<res<<"\n";
		return;
	}
	int res=0;
	int x=s[0]-'a',y=s.back()-'a',z=3-x-y;
	if(cnt[x][y]) cnt[x][y]--,res=work(x,1),cnt[x][y]++;
	if(cnt[x][z]&&cnt[z][y]) cnt[x][z]--,cnt[z][y]--,res=(res+work(x,1))%mod;
	cout<<res<<"\n";
}
int main(){
	// freopen("bigrams.in","r",stdin);
	// freopen("bigrams.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	init();
	int Ca;cin>>ID>>Ca;while(Ca--)solve();
	return 0;
}