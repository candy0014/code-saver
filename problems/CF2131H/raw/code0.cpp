#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
const ll mod=998244353;
const ll inf=2e9;
const int N=2e5+5;
const int M=2e5+5;
const int V=2e6+5;
int su[V],tot,mu[V];
bool vis[V];
vector<int>d[1000005];
void init(int n=V-3){
	vis[0]=vis[1]=1,mu[1]=1;
	for(int i=2;i<=n;i++){
		if(!vis[i]) su[++tot]=i,mu[i]=-1;
		for(int j=1;j<=tot&&su[j]*i<=n;j++){
			vis[su[j]*i]=1;
			mu[su[j]*i]=-mu[i];
			if(i%su[j]==0){
				mu[su[j]*i]=0;
				break;
			}
		}
	}
}
int n,m,a[200005],cnt[1000005],ans[4],du[1000005];
void get(int u,int &v,int b1,int b2){
	for(int i=1;i<=n;i++) if(i!=u&&i!=b1&&i!=b2&&__gcd(a[u],a[i])==1){v=i;return;}
}
void solve(int Ca){
	cin>>n>>m;
	for(int i=1;i<=m;i++) cnt[i]=0;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		for(int x:d[a[i]]) cnt[x]++;
	}
	int mi=1e9,mik=0;
	for(int i=1;i<=n;i++){
		int tmp=0;
		for(int x:d[a[i]]) tmp+=cnt[x]*mu[x];
		tmp-=(a[i]==1),du[i]=tmp;
		if(tmp&&tmp<mi) mi=tmp,mik=i;
	}
	if(!mik){cout<<"0\n";return;}
	ans[1]=ans[2]=ans[3]=0,ans[0]=mik;
	get(ans[0],ans[1],0,0);
	for(int i=1;i<=n;i++){
		if(__gcd(a[i],a[ans[0]])==1) du[i]--;
		if(__gcd(a[i],a[ans[1]])==1) du[i]--;
	}
	du[ans[0]]=du[ans[1]]=0;
	for(int i=1;i<=n;i++) if(du[i]){ans[2]=i;break;}
	if(!ans[2]){cout<<"0\n";return;}
	get(ans[2],ans[3],ans[0],ans[1]);
	cout<<ans[0]<<" "<<ans[1]<<" "<<ans[2]<<" "<<ans[3]<<"\n";
}
int main(){
	#ifdef ONLINE_JUDGE
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	#endif
	#ifndef ONLINE_JUDGE
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	init();
	for(int i=1;i<=1000000;i++) for(int j=i;j<=1000000;j+=i) d[j].emplace_back(i);
	int Ca=1;
	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}