#include <bits/stdc++.h>
using namespace std;
int n,k,a[400005];
bool check(int x){
	vector<int>p;
	for(int i=1;i<=n;i++) if(a[i]+a[i]<=x) p.emplace_back(i);
	if(p.size()<=1) return 0;
	p.emplace_back(p[0]+n);
	int cnt=p.size()-1;
	for(int i=1;i<(int)p.size();i++){
		int mi=2e9;
		for(int j=p[i-1]+1;j<p[i];j++) mi=min(mi,a[j]);
		cnt+=(mi<=x-a[p[i-1]]&&mi<=x-a[p[i]]);
	}
	return cnt>=k;
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i],a[i+n]=a[i];
	int l=2,r=2e9,mid,res=0;
	while(l<=r){
		mid=l+(r-l)/2;
		if(check(mid)) r=mid-1,res=mid;
		else l=mid+1;
	}
	cout<<res<<"\n";
	return 0;
}