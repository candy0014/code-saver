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
int n,v;
int L[200005],R[200005];
set<int>st;
map<int,int>mp;
vector<int>p,q;
void solve(int Ca){
	cin>>n>>v,st.clear(),mp.clear(),p.clear(),q.clear();
	st.insert(1),st.insert(v+1);
	int flag=0;
	for(int i=1;i<=n;i++){
		cin>>L[i]>>R[i];
		if(L[i]!=-1&&mp[L[i]]) flag=1;
		if(R[i]!=-1&&mp[R[i]]) flag=1;
		if(L[i]!=-1) st.insert(L[i]),mp[L[i]]=1;
		if(R[i]!=-1) st.insert(R[i]+1),mp[R[i]]=1;
		if(L[i]!=-1&&R[i]==-1) p.emplace_back(L[i]);
		if(R[i]!=-1&&L[i]==-1) q.emplace_back(R[i]+1);
	}
	if(flag){cout<<"NIE\n";return;}
	sort(p.begin(),p.end()),sort(q.begin(),q.end());
	int now=0;
	for(auto x:p){
		while(now<(int)q.size()&&q[now]<=x) now++;
		if(now<(int)q.size()){
			auto it=st.lower_bound(x+1);
			if((*it)==q[now]){
				if(q[now]-1==x){cout<<"NIE\n";return;}
				st.insert(q[now]-1);
			}
		}
	}
	if(st.size()>n+1){cout<<"NIE\n";return;}
	int tmp=v+1;
	for(int i=1;i<=n;i++) if(L[i]!=-1&&R[i]!=-1){
		auto it=st.lower_bound(L[i]+1);
		if((*it)!=R[i]+1){cout<<"NIE\n";return;}
		tmp-=R[i]-L[i];
	}
	if(n+1>tmp){cout<<"NIE\n";return;}
	cout<<"TAK\n";
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