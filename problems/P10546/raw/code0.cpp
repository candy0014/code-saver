#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
mt19937 rd(time(0));
int n;
ll ask[10005];
int res[55][10005],sz[55][10005];
int tag[10005];
map<ll,int>mp;
pair<int,int>ans[10005];

vector<pair<int,int>>ee;

vector<int>e[10005];
int dfs(int u){
	int cnt=1;
	for(auto v:e[u]) cnt+=dfs(v);
	return cnt;
}
void query(int id){
	for(int i=1;i<=n;i++) e[i].clear();
	for(int i=0;i<n-1;i++){
		if((ask[i+1]>>id)&1) e[ee[i].first].emplace_back(ee[i].second);
		else e[ee[i].second].emplace_back(ee[i].first);
	}
	for(int i=1;i<=n;i++) res[id][i]=dfs(i);
}
int main(){
	cin>>n;
	// for(int i=1,u,v;i<n;i++) cin>>u>>v,ee.emplace_back(u,v);
	vector<int>p;
	for(int i=0;i<50;i++) p.emplace_back(i);
	for(int i=1;i<n;i++){
		shuffle(p.begin(),p.end(),rd);
		for(int j=0;j<25;j++) ask[i]|=1ll<<p[j];
		mp[ask[i]]=i,mp[((1ll<<50)-1)^ask[i]]=-i;
	}
	for(int i=0;i<50;i++){
		cout<<"? ";
		for(int j=1;j<n;j++) cout<<((ask[j]>>i)&1);
		cout<<endl;
		// query(i);
		// for(int j=1;j<=n;j++) cout<<res[i][j]<<" \n"[j==n];
		for(int j=1;j<=n;j++) cin>>res[i][j],sz[i][j]=1;
	}
	queue<int>q;
	for(int i=1;i<=n;i++){
		int cnt=0;
		for(int j=0;j<50;j++) cnt+=res[j][i]==1;
		if(cnt==25) q.push(i);
	}
	for(int c=1;c<n;c++){
		int u=q.front();q.pop();
		vector<int>p;
		ll val=0;
		for(int i=0;i<50;i++) if(res[i][u]!=sz[i][u]){
			val|=(1ll<<i);
			p.emplace_back(i);
		}
		for(int i=1;i<=n;i++) if(i!=u&&!tag[i]){
			int flag=0;
			for(auto x:p) if(res[x][i]!=res[x][u]-sz[x][u]){flag=1;break;}
			if(!flag){
				tag[u]=i;
				if(mp[val]>0) ans[mp[val]]=make_pair(u,i);
				else ans[-mp[val]]=make_pair(i,u);
			}
		}
		int v=tag[u],cnt=0;
		for(int i=0;i<50;i++){
			if(res[i][u]==sz[i][u]) sz[i][v]+=sz[i][u];
			cnt+=res[i][v]==sz[i][v];
		}
		if(cnt==25) q.push(v);
	}
	cout<<"!";
	for(int i=1;i<n;i++) cout<<" "<<ans[i].first<<" "<<ans[i].second;
	cout<<endl;
	return 0;
}