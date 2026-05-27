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
string s;
int n;
int s1[200005],s2[200005],s3[200005];
map<tuple<int,int,int>,int>mp;
void solve(int Ca){
	cin>>s,n=s.length(),s=" "+s;
	ll res=0;
	mp[make_tuple(0,0,0)]=1;
	for(int i=1;i<=n;i++){
		s1[i]=s1[i-1],s2[i]=s2[i-1],s3[i]=s3[i-1];
		if(s[i]=='s') s1[i]++;
		else s1[i]--;
		if(s[i]=='y') s2[i]+=3;
		else s2[i]--;
		if(s[i]=='u') s3[i]+=3;
		else s3[i]--;
		res+=mp[make_tuple(s1[i],s2[i],s3[i])];
		mp[make_tuple(s1[i],s2[i],s3[i])]++;
	}
	cout<<res<<"\n";
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