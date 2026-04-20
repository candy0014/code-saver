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
int n,k,a[200005];
map<int,int>mp;
void solve(int Ca){
	cin>>n>>k,mp.clear();
	for(int i=1;i<=n;i++) cin>>a[i],mp[a[i]]=1;
	sort(a+1,a+n+1);
	vector<int>res;
	for(int i=1;i<=n;i++) if(mp[a[i]]){
		if(k/a[i]>mp.size()){cout<<"-1\n";return;}
		for(int j=a[i];j<=k;j+=a[i]){
			if(!mp.count(j)){cout<<"-1\n";return;}
			mp[j]=0;
		}
		res.emplace_back(a[i]);
	}
	cout<<res.size()<<"\n";
	for(auto x:res) cout<<x<<" ";
	cout<<"\n";
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