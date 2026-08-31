#include <bits/stdc++.h>
using namespace std;
int n,a[1100005];
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=0;i<(1<<n);i++) cin>>a[i];
	for(int i=0;i<(1<<n);i++) for(int j=0;j<n;j++) if((i>>j)&1) for(int k=0;k<n;k++) if(!((i>>k)&1)){
		int x=i,y=i^(1<<j)^(1<<k);
		if(a[x]+a[y]<a[x&y]+a[x|y]){cout<<x<<" "<<y<<"\n";return 0;}
	}
	cout<<"-1\n";
	return 0;
}