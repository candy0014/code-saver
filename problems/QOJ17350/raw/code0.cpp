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
int n,m;
ll a[500005],h[500005],al;
vector<pair<ll,ll> >p;
priority_queue<ll>q;
void solve(int Ca){
	cin>>n>>m,al=0;
	while(!q.empty()) q.pop();
	for(int i=1,u;i<=n;i++) cin>>u,q.push(u),al+=u;
	for(int i=1;i<=m;i++) cin>>h[i];
	p.clear();
	for(int i=1,u;i<=m;i++){
		cin>>u;
		if(h[i]<u) p.emplace_back(u,h[i]);
	}
	sort(p.begin(),p.end(),[&](pair<int,int>u,pair<int,int>v){return u.first>v.first;});
	for(auto [r,l]:p){
		ll R=q.top();q.pop();
		al-=max(0ll,min(R,r)-l);
		q.push(min(l,R));
	}
	cout<<al<<"\n";
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