#include <bits/stdc++.h>
using namespace std;
int n;
vector<vector<int> >s;
vector<int> F(int l,int r,int u,int v,int w){
	vector<int>res(n+2,v);
	for(int i=l;i<=r;i++) res[i]=u;
	res[0]=w;
	return res;
}
int solve(int l,int r){
	if(l==r) return -l;
	int mid=(l+r-1)>>1,ls=solve(l,mid),rs=solve(mid+1,r);
	s.emplace_back(F(1,n+1,s.size(),0,rs));
	for(int i=1;i<=mid-l+1;i++) s.emplace_back(F(l,mid,s.size()-1,s.size(),ls));
	return s.size()-1;
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	int rt=solve(1,n+1);
	reverse(s.begin(),s.end());
	cout<<rt+1<<"\n";
	for(auto x:s){
		for(auto y:x) cout<<((y<0)?y:(rt-y))<<" ";
		cout<<"\n";
	}
	return 0;
}
