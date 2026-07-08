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
int n,k,res[5005];
string s;
void solve(int Ca){
	cin>>n>>k>>s;
	for(int i=0;i<n;i++) res[i]=0;
	int now=0,pos=0;
	for(int i=0;i<n;i++){
		if(s[i]=='(') now++;
		else now--;
		if(now<0) pos=i,now=0;
	}
	for(int i=0;i<pos;i++) if(s[i]=='('&&k) res[i]=1,k--;
	for(int i=n-1;i>=pos;i--) if(s[i]==')'&&k) res[i]=1,k--;
	for(int i=0;i<n;i++) cout<<res[i];
	cout<<"\n";
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