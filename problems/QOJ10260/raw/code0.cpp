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
string s,t;
void solve(int Ca){
	cin>>s>>t;
	int c1=0,c2=0;
	for(int i=1;s[i];i++) c1+=s[i]!=s[i-1];
	for(int i=1;t[i];i++) c2+=t[i]!=t[i-1];
	if(s[0]!=t[0]&&c1==c2) c1++;
	cout<<max(c1,c2)<<"\n";
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