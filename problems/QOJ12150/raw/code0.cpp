#include <bits/stdc++.h>
using namespace std;
int n,id[500005],res[500005];
pair<int,int>p[500005];
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>p[i].first>>p[i].second,id[i]=i,res[i]=0;
	sort(id+1,id+n+1,[&](int u,int v){return p[u].first<p[v].first||p[u].first==p[v].first&&p[u].second>p[v].second;});
	for(int i=1;i<n-1;i+=2) res[id[i+(p[id[i+1]].second>p[id[i]].second)]]=1;
	for(int i=1;i<=n;i++) cout<<"NT"[res[i]];cout<<"\n";
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}