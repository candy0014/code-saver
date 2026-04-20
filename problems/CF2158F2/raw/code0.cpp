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
int n;
int su[21]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73};
ll res[105];
vector<int>e[105];
vector<int>ans;
int viss[105][105];
void dfs(int u){
	for(auto v:e[u]) if(!viss[u][v]){
		viss[u][v]=viss[v][u]=1,dfs(v);
	}
	ans.emplace_back(u);
}
void solve(int Ca){
	cin>>n;
	for(int i=1;i<=100;i++) e[i].clear();
	memset(viss,0,sizeof(viss));
	for(int cnt=1;cnt<=100;cnt++){
		int tmp=cnt*(cnt+1)/2;
		if(cnt%2==0) tmp-=cnt/2-1;
		if(tmp+1>=n){
			for(int i=1;i<=cnt;i++) for(int j=i;j<=cnt;j++){
				if(cnt%2==0&&j==i+1&&(i&1)&&i!=1) continue;
				e[i].emplace_back(j),e[j].emplace_back(i);
			}
			ans.clear();
			dfs(1);
			// set<ll>st;
			// for(int i=2;i<=n;i++) st.insert(__gcd(res[ans[i-1]],res[ans[i-2]]));
			// cout<<st.size()<<"\n";
			for(int i=1;i<=n;i++) cout<<res[ans[i-1]]<<" \n"[i==n];
			return;
		}
	}
}
mt19937 rd(time(0));
int vis[2200005],id[21];
int main(){
	#ifdef ONLINE_JUDGE
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	#endif
	#ifndef ONLINE_JUDGE
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	for(int i=0;i<21;i++) id[i]=i;
	for(int i=1;i<=100;i++){
		while(1){
			shuffle(id,id+21,rd);
			int x=0,flag=0;
			ll tmp=1;
			for(int j=0;j<11;j++) x|=(1<<id[j]),tmp*=su[id[j]];
			if(tmp>1e18) continue;
			res[i]=x;
			for(int j=1;j<=i;j++){
				if(vis[x&res[j]]){
					for(int k=1;k<j;k++) vis[x&res[k]]=0;
					flag=1;break;
				}
				vis[x&res[j]]=1;
			}
			if(!flag) break;
		}
	}
	for(int i=1;i<=100;i++){
		int x=res[i];res[i]=1;
		for(int j=0;j<21;j++) if((x>>j)&1) res[i]=res[i]*su[j];
	}
	// set<ll>st;
	// for(int i=1;i<=100;i++) for(int j=i;j<=100;j++) st.insert(__gcd(res[i],res[j]));
	// cout<<st.size()<<"\n";
	int Ca=1;
	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}