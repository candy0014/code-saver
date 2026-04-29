#include <bits/stdc++.h>
using namespace std;
int n,a[200005];
vector<int>p[2];
bool work(int op){
	int mi=1e9,ma=-1e9;
	for(auto x:p[op^1]) mi=min(mi,x),ma=max(ma,x);
	int now=-1;
	for(auto x:p[op]){
		if(x>=now){now=x;continue;}
		if(x<=mi&&ma<=now) return 0; 
	}
	return 1;
}
void solve(){
	cin>>n,p[0].clear(),p[1].clear();
	for(int i=1;i<=n;i++) cin>>a[i],p[a[i]&1].emplace_back(a[i]);
	if(work(0)&&work(1)) cout<<"YES\n";
	else cout<<"NO\n";
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}