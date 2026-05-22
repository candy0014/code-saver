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
int n,c[200005];
void solve(int Ca){
	cin>>n;
	ll sum=0,cnt=0,t=0,tt=0,al=0;
	for(int i=1;i<=n;i++){
		cin>>c[i],al+=c[i];
		if(c[i]>1) sum+=c[i],t+=c[i]/2-1,tt++;
		else cnt++;
	}
	if(al<3||!tt){cout<<"0\n";return;}
	if(tt==1) t++;
	ll res=sum+min(cnt,t);
	cout<<res<<"\n";
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