#include <bits/stdc++.h>
using namespace std;
int n,a[5005],b[5005],p[5005];
int solve(int l,int r){
	if(l==r) return 0;
	for(int i=l;i<=r;i++) p[a[i]]=i;
	int mi=n,ma=0,t=1e9;
	for(int i=l;i<r;i++){
		mi=min(mi,p[i]),ma=max(ma,p[i]);
		if(ma-mi==i-l) t=min(t,(r-mi+1)%(r-l+1));
	}
	mi=n,ma=0;
	for(int i=r;i>l;i--){
		mi=min(mi,p[i]),ma=max(ma,p[i]);
		if(ma-mi==r-i) t=min(t,r-ma);
	}
	int tot=l;
	for(int i=r-t+1;i<=r;i++) b[tot++]=a[i];
	for(int i=l;i<=r-t;i++) b[tot++]=a[i];
	ma=0;
	int la=l,res=0;
	for(int i=l;i<=r;i++){
		a[i]=b[i],ma=max(ma,a[i]);
		if(ma==i) res=max(res,solve(la,i)),la=i+1;
	}
	return res+t;
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1,u;i<=n;i++) cin>>u,a[u]=i;
	cout<<solve(1,n)<<"\n";
	return 0;
}