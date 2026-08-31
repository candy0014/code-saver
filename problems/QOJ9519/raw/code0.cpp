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
int l,r;
vector<pair<int,int> >e[105];
int tot;
map<array<int,3>,int>mp;
int solve(array<int,3>t){
	if(mp.count(t)) return mp[t];
	int p=++tot;
	if(t[2]==-1){
		int l=t[0],r=t[1];
		for(int i=0;i<=20;i++){
			int L=max(l,(1<<i)),R=min(r,(1<<(i+1))-1);
			if(L<=R) e[p].emplace_back(solve({L^(1<<i),R^(1<<i),i}),1);
		}
	}
	else{
		int l=t[0],r=t[1],k=t[2]-1,kk=(1<<k)-1;
		if(((l>>k)&1)==((r>>k)&1)) e[p].emplace_back(solve({l&kk,r&kk,k}),(l>>k)&1);
		else{
			e[p].emplace_back(solve({l,(1<<k)-1,k}),0);
			e[p].emplace_back(solve({0,r&kk,k}),1);
		}
	}
	return mp[t]=p;
}
void solve(int Ca){
	cin>>l>>r;
	mp[{0,0,0}]=++tot;
	solve({l,r,-1});
	cout<<tot<<"\n";
	for(int i=1;i<=tot;i++){
		cout<<e[i].size();
		for(auto [v,w]:e[i]) cout<<" "<<v<<" "<<w;
		cout<<"\n";
	}
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
//	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}