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
ll a[500005];
void solve(int Ca){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	int ma=0,ma1=0,ma2=0;
	for(int i=3;i<=n;i++){
		int it=lower_bound(a+2,a+i,a[i]/2+1)-a;
		if(it==i) continue;
		if(a[it]+a[it-1]<=a[i]) it++;
		if(it==i) continue;
		if(i-it+2>ma) ma=i-it+2,ma1=it-1,ma2=i;
	}
	if(!ma) cout<<ma<<"\n";
	else{
		cout<<ma<<" ";
		for(int i=ma1;i<=ma2;i++) cout<<a[i]<<" \n"[i==ma2];
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