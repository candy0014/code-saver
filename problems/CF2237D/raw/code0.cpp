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
int n;
string s;
void solve(int Ca){
	cin>>n>>s;
	int now=0,cnt[3]={1,0,0};
	ll res=0;
	for(int i=0,la=0;i<n;i++){
		if(i&&s[i]==s[i-1]) la=i;
		if(s[i]=='0') now=(now+1)%3;
		else now=(now+2)%3;
		res+=i+1-cnt[now]-(i-la)/2,cnt[now]++;
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
	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}