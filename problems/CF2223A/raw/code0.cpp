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
string s,t;
void solve(int Ca){
	cin>>n>>s>>t;
	int s1=0,s2=0,flag=0;
	for(int i=0;i<n;i++){
		if(s[i]==t[i]){
			if(s[i]=='(') s1++,s2++;
			else s1--,s2--;
		}
		else if(flag){
			s1++,s2--,flag^=1;
		}
		else s1--,s2++,flag^=1;
		if(s1<0||s2<0){cout<<"NO\n";return;}
	}
	if(s1||s2){cout<<"NO\n";return;}
	cout<<"YES\n";
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