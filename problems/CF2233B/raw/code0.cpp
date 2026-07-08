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
int res2[10]={1,2,2,1,2,1,1,2};
int res3[15]={1,1,2,1,2,3,1,3,2,2,3,3};
void solve(int Ca){
	int n;cin>>n;
	for(int i=1;i<n;i+=2){
		if(i==n-2){
			for(int j=0;j<12;j++) cout<<res3[j]+i-1<<" ";
		}
		else{
			for(int j=0;j<8;j++) cout<<res2[j]+i-1<<" ";
		}
	}
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