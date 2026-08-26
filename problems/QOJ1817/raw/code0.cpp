#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
vector<ll>solve(vector<ll>a,int d){
	if(!a.size()) return {};
	if(d==-1) return {0};
	vector<ll>s0,s1,t0,t1,res;res.resize(a.size());
	for(auto x:a){
		if((x>>d)&1) s1.emplace_back(x-(1ll<<d));
		else s0.emplace_back(x);
	}
	t0=solve(s0,d-1),t1=solve(s1,d-1);
	int p0=0,p1=0,p=0;
	for(auto x:a){
		if((x>>d)&1) res[p++]=t1[p1++]+(1ll<<d);
		else res[p++]=t0[p0++];
	}
	map<ll,int>mp;
	for(int i=0;i<(int)a.size();i++) if(!((a[i]>>d)&1)) mp[a[i]]=i;
	for(int i=0;i<(int)a.size();i++) if((a[i]>>d)&1) swap(res[i],res[mp[a[i]-(1ll<<d)]]);
	return res;
}
vector<ll>a;
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;a.resize(n);
	for(int i=0;i<n;i++) cin>>a[i];
	vector<ll>res=solve(a,59);
	for(auto x:res) cout<<x<<"\n";
	return 0;
}