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
int n,m,ca;
struct EDGE{int u,v;}e[1000005];
pair<int,int>ee[1000005];
int tag[1000005],fa[1000005];
map<pair<int,int>,bool>mp;
int cnt;
int Find(int u){return fa[u]==u?u:(fa[u]=Find(fa[u]));}
void merge(int u,int v){u=Find(u),v=Find(v);if(u!=v)fa[u]=v,cnt--;}
int ans;
void solve(int Ca){
	mp.clear();
	cin>>n>>m>>ca;
	for(int i=1;i<=m;i++){
		cin>>e[i].u>>e[i].v;
		if(e[i].u>e[i].v) swap(e[i].u,e[i].v);
		mp[make_pair(e[i].u,e[i].v)]=1;
	}
	int now0=0,now1=0;
	for(int i=1;i<=ca;i++){
		int u,v;
		cin>>u>>v;
		u=(u+now0)%n,v=(v+now1)%n;
		if(u>v) swap(u,v);
		ee[i]=make_pair(u,v);
		now0=(now0*2+1)%n,now1=(now1*3+1)%n;
		if(!mp.count(make_pair(u,v))) tag[i]=1;
		else mp.erase(make_pair(u,v)),tag[i]=0;
	}
	for(int i=0;i<n;i++) fa[i]=i;
	cnt=n;
	for(auto x:mp) merge(x.first.first,x.first.second);
	if(cnt==1) ans=ca;
	else{
		ans=0;
		for(int i=ca;i>=1;i--){
			if(!tag[i]){
				merge(ee[i].first,ee[i].second);
				if(cnt==1){ans=i-1;break;}
			}
		}
	}
	for(int i=1;i<=ans;i++) cout<<"1\n";
	for(int i=ans+1;i<=ca;i++) cout<<"0\n";
}
int main(){
	// #ifdef ONLINE_JUDGE
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	// #endif
	#ifndef ONLINE_JUDGE
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	#endif
	
	int Ca=1;
	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}