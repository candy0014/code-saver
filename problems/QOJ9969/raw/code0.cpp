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
int a,b,c,d;
void solve(int Ca){
	cin>>a>>b>>c>>d;
	int m=c-a;
	if(d-b!=m||m<=0){cout<<"-1\n";return;}
	if(b!=a+1||d!=c+1){cout<<"-1\n";return;}
	int n=(d-1)/m+1;
	if((c-1)/m+1!=n||(a-1)/m+1!=n-1||(b-1)/m+1!=n-1){cout<<"-1\n";return;}
	cout<<n<<" "<<m<<"\n"; 
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