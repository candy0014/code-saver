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
string s;
map<string,vector<string> >mp;
map<string,string>res;
void solve(int Ca){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s;
		mp[s.substr(0,4)].emplace_back(s);
	}
	for(int i=1;i<=n;i++){
		cin>>s;
		string t=s.substr(0,4);
		if(mp[t].size()) res[mp[t].back()]=s,mp[t].pop_back();
		else{cout<<"NO\n";return;}
	}
	cout<<"YES\n";
	for(auto [x,y]:res) cout<<x<<" "<<y<<"\n";
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