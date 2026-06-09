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
int n,k;
string s1,s2;
int c1,c2,c3;
ll a1,a2,a3,b1,b2,b3;
void solve(int Ca){
	cin>>n>>k>>s1>>s2;
	c1=c2=c3=0;
	for(int i=0;i<n;i++) c1+=s1[i]-'0',c2+=s2[i]-'0',c3+=s1[i]!=s2[i];
	a1=1,a2=a3=0;
	ll d3=1;
	for(int i=1;i<k;i++){
		b1=b2=b3=0;
		b2+=a1,b3+=a1;
		b1+=a2,b3+=a2;
		b1+=a3,b2+=a3;
		a1=b1,a2=b2,a3=b3;
		d3+=a1;
	}
	ll d1=((1<<k)+1-d3)/2,d2=d1;
	cout<<1ll*c1*(n-c1)*d1+1ll*c2*(n-c2)*d2+1ll*c3*(n-c3)*d3<<"\n";
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