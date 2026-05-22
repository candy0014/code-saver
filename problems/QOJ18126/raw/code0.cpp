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
void solve(int Ca){
	cin>>s;
	if(s.length()<12) cout<<"NO\n";
	else{
		if(s.substr(0,9)!="ucup-team"||s[9]=='0') cout<<"NO\n";
		else{
			for(int i=9;s[i];i++) if(s[i]<'0'||s[i]>'9'){cout<<"NO\n";return;}
			cout<<"YES\n";
		}
	}
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