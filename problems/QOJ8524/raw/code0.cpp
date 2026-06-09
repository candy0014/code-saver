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
double a[200005];
bool check(double x){
	vector<double>p;
	p.emplace_back(0);
	double sum=0;
	for(int i=1;i<=n;i++){
		sum+=a[i]-x;
		if(sum<0) continue;
		if(i==n){
			if(p.size()<k) return 0;
			return p[k-1]<=sum;
		}
		int it=lower_bound(p.begin(),p.end(),sum)-p.begin();
		if(it==p.size()) p.emplace_back(sum);
		else p[it]=sum;
	}
	return 0;
}
void solve(int Ca){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	double l=0,r=1000,mid;
	for(int i=1;i<=40;i++){
		mid=(l+r)/2;
		if(check(mid)) l=mid;
		else r=mid;
	}
	cout<<fixed<<setprecision(10)<<l<<"\n";
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
//	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}