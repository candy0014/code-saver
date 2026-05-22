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
	cin>>s,t="";
	int res=0,c=0;
	for(int i=0;s[i];i++){
		if(s[i]=='4') res++;
		else t+=s[i];
		if(s[i]=='2') c++;
	}
	int cnt=0,mi=c,c2=0;
	for(int i=0;t[i];i++){
		if(t[i]=='2') c2++,mi=min(mi,c-c2+cnt);
		else cnt++;
	}
	cout<<res+mi<<"\n";
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