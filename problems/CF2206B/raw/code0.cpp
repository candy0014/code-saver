#include <bits/stdc++.h>
using namespace std;
int n,fa[500005],vis[500005],p[500005];
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=2;i<=n;i++) cin>>fa[i],vis[fa[i]]=1;
	int l=1,r=n,mid,res=1;
	while(l<=r){
		mid=(l+r)>>1;
		for(int i=1;i<=n;i++) p[i]=!vis[i]?(i<=mid?1:-1):0;
		for(int i=n;i>=1;i--){
			if(p[i]<0) p[i]=-1;
			if(p[i]>0) p[i]=1;
			p[fa[i]]+=p[i];
		}
		if(p[1]<0) l=mid+1,res=mid+1;
		else r=mid-1;
	}
	cout<<res<<"\n";
	return 0;
}