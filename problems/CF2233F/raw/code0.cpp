#include <bits/stdc++.h>
using namespace std;
void get(int a,vector<int>&d,vector<vector<pair<int,int> > >&t){
	for(int i=1;i*i<=a;i++) if(a%i==0) d.emplace_back(i);
	for(int i=(int)d.size()-1;i>=0;i--) if(d[i]*d[i]!=a) d.emplace_back(a/d[i]);
	t.resize(d.size());
	for(int i=0;i<(int)d.size();i++){
		for(int j=0,k=0;j<(int)d.size();j++) if((a/d[i])%d[j]==0){
			while(d[k]<d[i]*d[j]) k++;
			t[i].emplace_back(d[j],k);
		}
	}
}
int a,b;
vector<int>da,db;
vector<vector<pair<int,int> > >ta,tb;
int dp[1405][1405];
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>a>>a>>b;
	int g=__gcd(a,b);
	a/=g,b/=g;
	get(a,da,ta),get(b,db,tb);
	memset(dp,0x3f3f3f3f,sizeof(dp)),dp[0][0]=0;
	for(int i=0;i<(int)da.size();i++) for(int j=0;j<(int)db.size();j++){
		for(auto [pa,qa]:ta[i]) for(auto [pb,qb]:tb[j]){
			dp[qa][qb]=min(dp[qa][qb],dp[i][j]+max(pa,pb));
		}
	}
	cout<<dp[da.size()-1][db.size()-1]<<"\n";
	return 0;
}