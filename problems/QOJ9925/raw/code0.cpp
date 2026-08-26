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
int n,ca;
int nex[1000005][3];
void solve(int Ca){
	cin>>s>>ca,n=s.length(),s=" "+s;
	for(int j:{0,1,2}) nex[n][j]=nex[n+1][j]=n+1;
	for(int i=n;i>=1;i--){
		for(int j:{0,1,2}) nex[i-1][j]=nex[i][j];
		if(s[i]=='L') nex[i-1][0]=i;
		if(s[i]=='R') nex[i-1][1]=i;
		if(i<n&&s[i]=='L'&&s[i+1]=='R') nex[i-1][2]=i+1;
	}
	while(ca--){
		cin>>t;
		if(t[0]=='R'&&s[1]!='R'){cout<<"NO\n";continue;}
		if(t.back()=='L'&&s[n]!='L'){cout<<"NO\n";continue;}
		int now=0;
		for(int i=0;t[i];i++){
			if(t[i+1]&&t[i]=='L'&&t[i+1]=='R'){
				now=nex[now][2],i++;
			}
			else if(t[i]=='L') now=nex[now][0];
			else if(t[i]=='R') now=nex[now][1];
		}
		if(now<=n) cout<<"YES\n";
		else cout<<"NO\n";
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