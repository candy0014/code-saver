#include <bits/stdc++.h>
using namespace std;
int n,m,a[2005],l[1005],r[1005],fa[4005],res[2005];
int Find(int u){return fa[u]==u?u:(fa[u]=Find(fa[u]));}
void merge(int u,int v){fa[Find(u)]=Find(v);}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n,m=n*2;
	for(int i=1;i<=m+m;i++) fa[i]=i;
	for(int i=1;i<=n+n;i++){
		cin>>a[i];
		if(!l[a[i]]) l[a[i]]=i;
		else r[a[i]]=i;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++) if(l[j]<l[i]&&r[i]<r[j]){merge(l[i],r[i]),merge(l[i]+m,r[i]+m);break;}
		for(int j=l[i]+1;j<r[i];j++) if(j==r[a[j]]&&l[a[j]]<l[i]) merge(l[i],j+m),merge(l[i]+m,j);
	}
	for(int i=1;i<=m;i++) if(Find(i)==Find(i+m)){cout<<"NO\n";return 0;}
	for(int i=1;i<=m;i++) res[i]=(Find(i)<=m);
	cout<<"YES\n";
	for(int i=1;i<=n;i++){
		if(res[l[i]]&&res[r[i]]) cout<<"3 U "<<r[i]-l[i]<<" R "<<r[i]-l[i]<<" D "<<r[i]-l[i]<<"\n";
		if(!res[l[i]]&&!res[r[i]]) cout<<"3 D "<<r[i]-l[i]<<" R "<<r[i]-l[i]<<" U "<<r[i]-l[i]<<"\n";
		if(res[l[i]]&&!res[r[i]]) cout<<"5 U "<<l[i]+m<<" L "<<l[i]+l[i]<<" D "<<l[i]+m+r[i]+m<<" R "<<l[i]+r[i]<<" U "<<r[i]+m<<"\n";
		if(!res[l[i]]&&res[r[i]]) cout<<"5 D "<<l[i]+m<<" L "<<l[i]+l[i]<<" U "<<l[i]+m+r[i]+m<<" R "<<l[i]+r[i]<<" D "<<r[i]+m<<"\n";
	}
	return 0;
}