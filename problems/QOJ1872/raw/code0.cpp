#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,ca;
vector<pair<pair<int,int>,int> >as;
unordered_map<int,int>mp;
unordered_map<ll,int>vis;
void insert(int l,int r,int x){
	mp[l+r]=x,vis[l*(ll)(2e9)+r]=1;
}
int get(int l,int r){
	if(!mp.count(l+r)) return (l+r)&1;
	return mp[l+r];
}
int res[1000005];
void solve(){
	cin>>n>>ca,as.clear();
	for(int i=1,l,r,x;i<=n;i++){
		cin>>l>>r>>x;
		as.emplace_back(make_pair(l,r),x);
		for(int a=0;a<=2;a++) for(int b=0;a+b<=2;b++) if(a||b) as.emplace_back(make_pair(l-a,r+b),-1);
	}
	for(int i=1,l,r;i<=ca;i++){
		cin>>l>>r;
		as.emplace_back(make_pair(l,r),-i-1);
	}
	sort(as.begin(),as.end(),[&](auto u,auto v){
		int tu=u.first.second-u.first.first,tv=v.first.second-v.first.first;
		if(tu!=tv) return tu<tv;
		return u.second>v.second;
	});
	mp.clear(),vis.clear();
	for(auto x:as){
		if(x.second>=0) insert(x.first.first,x.first.second,x.second);
		else if(x.second==-1){
			if(!vis.count(x.first.first*(ll)(2e9)+x.first.second)){
				int tmp=!(get(x.first.first+1,x.first.second)&get(x.first.first,x.first.second-1));
				insert(x.first.first,x.first.second,tmp);
			}
		}
		else res[-x.second-1]=get(x.first.first,x.first.second);
	}
	for(int i=1;i<=ca;i++) cout<<res[i];
	cout<<"\n";
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}
