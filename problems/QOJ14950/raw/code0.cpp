#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,s;
ll sum[2][2];
map<pair<ll,ll>,int>mp;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>s;
	for(int i=1,a,b,c,d;i<=n;i++){
		cin>>a>>b>>c>>d,mp[make_pair(c,d)]=i;
		if(i==s) sum[0][0]-=a,sum[0][1]-=b;
		else sum[0][0]+=a,sum[0][1]+=b;
		sum[1][0]+=c,sum[1][1]+=d;
	}
	cout<<mp[make_pair((sum[1][0]-sum[0][0])/2,(sum[1][1]-sum[0][1])/2)]<<"\n";
	return 0;
}