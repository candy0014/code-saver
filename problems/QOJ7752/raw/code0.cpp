#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll sum,cnt;
int n,m,k;
vector<pair<int,int> >p[200005];
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>k,sum=1ll*n*m;
	if(n==1){
		vector<int>p;
		while(k--){
			int l,r,y;
			cin>>l>>r>>y,p.emplace_back(y);
		}
		sort(p.begin(),p.end());
		for(int i=0;i<p.size();i++) if(p[i]!=i+1&&p[i]!=m-p.size()+i+1){cout<<"NO\n";return 0;}
		cout<<"YES\n";return 0;
	}
	if(2*k+2<m){cout<<"NO\n";return 0;}
	while(k--){
		int l,r,y;
		cin>>l>>r>>y,sum-=(r-l+1),p[y].emplace_back(l,r);
	}
	for(int i=1;i<=m;i++){
		p[i].emplace_back(0,0),p[i].emplace_back(n+1,n+1);
		sort(p[i].begin(),p[i].end());
		for(int j=1;j<(int)p[i].size();j++){
			cnt+=max(0,p[i][j].first-p[i][j-1].second-2);
		}
		if(i>1){
			vector<pair<int,int> >g;
			for(int j=1;j+1<p[i].size();j++) g.emplace_back(p[i][j]);
			for(int j=1;j+1<p[i-1].size();j++) g.emplace_back(p[i-1][j]);
			sort(g.begin(),g.end());
			int la=0;cnt+=n;
			for(auto [l,r]:g) if(r>la) cnt-=r-max(la,l-1),la=r;
		}
	}
	if(sum==cnt+1) cout<<"YES\n";
	else cout<<"NO\n";
	return 0;
}