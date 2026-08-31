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
int cnt[26];
void solve(int Ca){
	memset(cnt,0,sizeof(cnt));
	cin>>s;
	for(int i=0;s[i];i++) cnt[s[i]-'a']++;
	int ma=0;
	for(int i=0;i<26;i++) ma=max(ma,cnt[i]);
	cout<<s.length()-ma<<"\n";
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