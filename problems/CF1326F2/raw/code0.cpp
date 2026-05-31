#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=998244353;
int n;
ll dp[500005][20],c[20][500005];
ll res[500005];
string s[20];
void add(int &u,int v){u+=v,u-=(u>=mod)*mod;}
ll g[20][500005];
map<int,ll>mp;
void dfs(int now,int ma,int de,int ha){
	if(now==n){
		ll tmp=0;
		for(int i=0;i<(1<<n);i++) tmp+=g[de][i];
		mp[ha]=tmp;
		return;
	}
	for(int i=1;i<=ma&&now+i<=n;i++){
		for(int j=0;j<(1<<n);j++) g[de+1][j]=g[de][j]*c[i][j];
		dfs(now+i,i,de+1,(ha*233ll+i)%mod);
	}
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=0;i<n;i++) cin>>s[i];
	for(int i=1;i<(1<<n);i++){
		if(!(i&(i-1))){dp[i][__lg(i)]=1;continue;}
		for(int j=0;j<n;j++) if((i>>j)&1) for(int k=0;k<n;k++) if(s[j][k]=='1') dp[i][j]+=dp[i^(1<<j)][k];
	}
	for(int i=1;i<(1<<n);i++){
		int t=__builtin_popcount(i);
		for(int j=0;j<n;j++) c[t][i]+=dp[i][j];
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<n;j++) for(int k=0;k<(1<<n);k++) if((k>>j)&1) c[i][k]+=c[i][k^(1<<j)];
	}
	for(int i=0;i<(1<<n);i++){
		if((n-__builtin_popcount(i))&1) g[0][i]=-1;
		else g[0][i]=1;
	}
	dfs(0,n,0,0);
	for(int i=0;i<(1<<(n-1));i++){
		vector<int>p;
		int cnt=1;
		for(int j=0;j<n;j++){
			if((i>>j)&1) cnt++;
			else p.emplace_back(cnt),cnt=1;
		}
		sort(p.begin(),p.end(),[&](int u,int v){return u>v;});
		int tmp=0;
		for(auto x:p) tmp=(tmp*233ll+x)%mod;
		res[i]=mp[tmp];
	}
	for(int i=0;i<n-1;i++) for(int j=(1<<(n-1))-1;j>=0;j--) if(!((j>>i)&1)) res[j]-=res[j|(1<<i)];
	for(int i=0;i<(1<<(n-1));i++) cout<<res[i]<<" \n"[i==(1<<n)-1];
	return 0;
}