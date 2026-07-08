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
int n,a[200005],_a[200005],b[200005],bb[200005],vis[200005],viss[200005],len[200005];
vector<int>p[200005];
void solve(int Ca){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],_a[a[i]]=i,p[i].clear(),vis[i]=0;
	for(int i=1;i<=n;i++) cin>>b[i],bb[i]=b[i];
	for(int i=1;i<=n;i++) if(!vis[i]){
		int cnt=0,u=i;
		vector<int>g;
		while(1){
			vis[u]=1,g.emplace_back(u),u=a[u],cnt++;
			if(u==i) break;
		}
		p[cnt].emplace_back(i);
		for(auto x:g) len[x]=cnt;
	}
	for(int i=1;i<=n;i++) reverse(p[i].begin(),p[i].end());
	for(int i=1;i<=n;i++) vis[i]=viss[i]=0;
	for(int i=1;i<=n;i++) if(b[i]!=-1&&!vis[i]){
		if(len[i]!=len[b[i]]){cout<<"NO\n";return;}
		int u=i,v=_a[b[i]];
		for(int j=1;j<=len[i];j++) b[u]=a[v],vis[u]=viss[v]=1,u=a[u],v=a[v];
	}
	for(int i=1;i<=n;i++) if(b[i]==-1){
		while(p[len[i]].size()&&viss[p[len[i]].back()]) p[len[i]].pop_back();
		if(!p[len[i]].size()){cout<<"NO\n";return;}
		int u=i,v=_a[p[len[i]].back()];p[len[i]].pop_back();
		for(int j=1;j<=len[i];j++) b[u]=a[v],vis[u]=viss[v]=1,u=a[u],v=a[v]; 
	}
	for(int i=1;i<=n;i++) vis[i]=0;
	for(int i=1;i<=n;i++){
		if((bb[i]!=-1&&b[i]!=bb[i])||vis[b[i]]){cout<<"NO\n";return;}
		vis[b[i]]=1;
	}
	cout<<"YES\n";
	for(int i=1;i<=n;i++) cout<<b[i]<<" \n"[i==n];
}
int main(){
	#ifdef ONLINE_JUDGE
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	#endif
	#ifndef ONLINE_JUDGE
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	
	int Ca=1;
	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}