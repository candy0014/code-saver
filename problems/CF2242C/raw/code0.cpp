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
int n,k,a[300005];
vector<pair<int,int> >p,q;
void solve(int Ca){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	p.clear();
	for(int i=1,j;i<=n;i=j+1){
		j=i;
		while(j<n&&a[i]==a[j+1]) j++;
		p.emplace_back(j-i+1,a[i]);
	}
	int res=0;
	while(p.size()){
		int mi=1e9;
		for(auto [x,y]:p) mi=min(mi,x);
		int t=n-(mi-1)*p.size();
		if(k>=t&&(k-t)%p.size()==0) res++;
		n-=mi*p.size();
		q.clear();
		for(auto [x,y]:p){
			x-=mi;
			if(!x) continue;
			if(q.size()&&q.back().second==y) q.back().first+=x;
			else q.emplace_back(x,y);
		}
		p=q;
	}
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