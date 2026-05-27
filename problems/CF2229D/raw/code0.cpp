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
int n,a[100005],b[100005];
bool check(int x){
	int cnt0=0,cnt1=0,flag=0;
	for(int i=1;i<=n;i++){
		if(a[i]<x&&b[i]<x){
			if(!flag) cnt0++,flag=1;
		}
		if(a[i]>=x&&b[i]>=x) cnt1++,flag=0;
	}
	return cnt1>cnt0;
}
void solve(int Ca){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	int l=1,r=n*2,mid,res=0;
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid)) l=mid+1,res=mid;
		else r=mid-1;
	}
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