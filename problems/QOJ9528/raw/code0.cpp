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
ll a[100005],x[100005],t[100005],nex[100005],vis[100005];
multiset<pair<int,int> >st;
void solve(int Ca){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i],vis[i]=m+1;
	for(int i=1;i<=m;i++) cin>>x[i]>>t[i];
	for(int i=m;i>=1;i--) nex[i]=vis[t[i]],vis[t[i]]=i;
	st.clear();
	for(int i=1;i<=n;i++) st.insert(make_pair(vis[i],a[i]));
	ll res=0;
	for(int i=1;i<=m;i++){
		if(st.empty()) break;
		pair<int,int> u=*st.begin();st.erase(st.begin());
		ll tmp=x[i]-res;
		if(tmp>u.second){res+=u.second,i--;continue;}
		tmp=u.second-tmp,res=x[i];
		st.insert(make_pair(u.first,tmp));
		auto it=st.lower_bound(make_pair(i,0));
		if(it!=st.end()&&(*it).first==i) st.erase(it);
		st.insert(make_pair(nex[i],a[t[i]]));
	}
	for(auto x:st) res+=x.second;
	cout<<res<<"\n";
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