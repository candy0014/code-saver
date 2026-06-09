#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=998244353;
int V,n;
vector<int>p[2];
int li[1000005],tot;
bool vis[2][1000005];
int work(int a,int b,int c,int d){
	if((a||b)&&!p[0].size()) return 0;
	if((c||d)&&!p[1].size()) return 0;
	int res=1;
	for(auto x:p[0]){
		if(!vis[1][x]&&!(c&&x<p[1][0])&&!(d&&x>p[1].back())) res=res*2%mod;
	}
	for(auto x:p[1]){
		if(!vis[0][x]&&!(a&&x<p[0][0])&&!(b&&x>p[0].back())) res=res*2%mod;
	}
	return res;
}
void solve(){
	cin>>V>>n,tot=0;
	p[0].clear(),p[1].clear();
	for(int i=1;i<=n;i++){
		vis[0][i]=vis[1][i]=0;
		int x,y;cin>>x>>y,p[x-1].emplace_back(y),li[++tot]=y;
	}
	sort(li+1,li+tot+1);
	sort(p[0].begin(),p[0].end()),sort(p[1].begin(),p[1].end());
	for(auto &x:p[0]) x=lower_bound(li+1,li+tot+1,x)-li,vis[0][x]=1;
	for(auto &x:p[1]) x=lower_bound(li+1,li+tot+1,x)-li,vis[1][x]=1;
	int ans=0;
	for(int i=0;i<16;i++) ans=(ans+work(i&1,i&2,i&4,i&8))%mod;
	for(int i=1;i<=n;i++) ans=ans*2%mod;
	cout<<ans<<"\n";
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}
