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
int a,b,n,s;
void solve(int Ca){
	cin>>a>>b>>n>>s;
	if(a>b) swap(a,b);
	if(s%a!=0||1ll*n*a<s){
		cout<<"YES\n";
		for(int i=1;i<=n;i++) cout<<a<<" \n"[i==n];
	}
	else if(s%b!=0){
		cout<<"YES\n";
		for(int i=1;i<=n;i++) cout<<b<<" \n"[i==n];
	}
	else if(s==b||b==a*2){
		cout<<"NO\n";
	}
	else{
		int t=s/b;
		cout<<"YES\n";
		for(int i=0;i<n;i++){
			if(i%t==0) cout<<a<<" ";
			else cout<<b<<" ";
		}
		cout<<"\n";
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