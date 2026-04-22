#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=998244353;
ll ksm(ll u,ll v=mod-2){ll tmp=1;u%=mod;while(v) tmp=tmp*((v&1)?u:1)%mod,u=u*u%mod,v>>=1;return tmp;}
mt19937_64 rd(time(0));
int n,m,k;
vector<int>e[100005];
vector<int> val[100005];
int du[100005];
queue<int>q;
vector<int>d[55];
int tim[55],cnt;
void insert(vector<int>x,int now){
	for(int i=k;i>=1;i--) if(x[i]){
		if(!tim[i]){tim[i]=now,d[i]=x,cnt++;return;}
		if(tim[i]<now) swap(x,d[i]),swap(now,tim[i]);
		ll tmp=1ll*x[i]*ksm(d[i][i])%mod;
		for(int j=1;j<=i;j++) x[j]=(x[j]-1ll*d[i][j]*tmp%mod+mod)%mod;
	}
}
ll res[55];
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++) val[i].resize(k+1);
	for(int i=1,u,v;i<=m;i++) cin>>u>>v,e[u].emplace_back(v),du[v]++;
	for(int i=1;i<=k;i++) val[i][i]=1;
	for(int i=1;i<=n;i++) if(!du[i]) q.push(i);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(auto v:e[u]){
			int w=rd()%mod;
			for(int i=1;i<=k;i++) val[v][i]=(val[v][i]+1ll*val[u][i]*w)%mod;
			du[v]--;
			if(!du[v]) q.push(v);
		}
	}
	for(int i=k+1;i<=n;i++){
		insert(val[i],i);
		vector<int>t;
		for(int j=1;j<=k;j++) if(tim[j]) t.emplace_back(tim[j]);
		t.emplace_back(k),t.emplace_back(i);
		sort(t.begin(),t.end(),[&](int u,int v){return u>v;});
		for(int j=0;j<(int)t.size()-1;j++) res[j]+=t[j]-t[j+1];
	}
	for(int i=0;i<=k;i++) cout<<res[i]<<"\n";
	return 0;
}