#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m;
pair<int,int>pos[2100005];
int a[2005][2005];
int L[2005];
void work(int x,int y){
	for(int i=y;L[i]>x;i--) L[i]=x;
}
vector<int>res[2005];
void solve(int n,vector<vector<int>>val,ll &ans,vector<int>&sol){
	m=n*(n+1)/2;
	for(int j=1;j<=n;j++) for(int i=1;i<=j;i++) pos[val[j-1][i-1]]=make_pair(i,j);
	for(int i=1;i<=n;i++) for(int j=i;j<=n;j++) a[i][j]=j-i+1;
	for(int i=1;i<=n;i++) L[i]=i+1;
	ans=0;
	for(int i=1;i<=n;i++) res[i].clear();
	for(int i=m;i>=1;i--){
		int l=pos[i].first,r=pos[i].second;
		if(l>=L[r]) continue;
		ans+=i;
		res[l].emplace_back(r);
		for(int x=1;x<=l;x++) for(int y=r;y<=n;y++){
			a[x][y]--;
			if(!a[x][y]) work(x,y);
		}
	}
	sol.clear();
	multiset<pair<int,int> >st;
	for(int i=1;i<=n;i++){
		for(auto x:res[i]) st.insert(make_pair(x,val[x-1][i-1]));
		sol.emplace_back((*st.begin()).second),st.erase(st.begin());
	}
}
// int main(){
// 	ll ans;
// 	vector<int>sol;
// 	solve(3,{{4},{3,2},{5,6,1}},ans,sol);
// 	for(auto x:sol) cout<<x<<" ";
// 	return 0;
// }