#include <bits/stdc++.h>
using namespace std;
const int lim=500,V=1e9+1;
int n,m,mm,sum,s,ca,a[100005],ia[100005],b[10000005],c[10000005],t[10000005];
int g[505][505],res[200005];
vector<pair<int,int> >as[10000005];
vector<pair<pair<int,int>,int> >as2[100005];
struct BIT{
	int sum[100005];
	void add(int x,int k){while(x<=n)sum[x]+=k,x+=(x&(-x));}
	int query(int x){int t=0;while(x)t+=sum[x],x-=(x&(-x));return t;}
	void clear(){memset(sum,0,sizeof(sum));}
}tr;
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>s>>ca,s--;
	for(int i=1;i<=n;i++) cin>>a[i],ia[a[i]]=i;
	if(!s){
		while(ca--){
			int a,k;
			cin>>a>>k;
			cout<<(ia[a]<=k)<<"\n";
		}
		return 0;
	}
	for(int i=1;i<=n&&sum<=V;i++) b[++m]=a[i],sum+=a[i];
	for(int i=1;i<=min(n,lim);i++){
		int tot=0;
		for(int j=1;j<=n;j++) if(a[j]<=i) g[i][++tot]=a[j];
	}
	for(int i=1;i<s;i++){
		mm=sum=0;
		for(int j=1;j<=m&&sum<=V;j++){
			if(b[j]<=lim) for(int k=1;k<=b[j]&&sum<=V;k++) c[++mm]=g[b[j]][k],sum+=g[b[j]][k];
			else for(int k=1;k<=n&&sum<=V;k++) if(a[k]<=b[j]) c[++mm]=a[k],sum+=a[k];
		}
		for(int j=1;j<=mm;j++) b[j]=c[j];m=mm;
	}
	for(int i=1;i<=m;i++) t[i]=t[i-1]+b[i];
	for(int i=1,k,a;i<=ca;i++){
		cin>>a>>k;
		int tmp=upper_bound(t+1,t+m+1,k)-t-1;
		as[tmp].emplace_back(a,i);
		if(k-t[tmp]&&a<=b[tmp+1]) as2[b[tmp+1]].emplace_back(make_pair(a,k-t[tmp]),i);
	}
	for(int i=1;i<=m;i++){
		tr.add(b[i],1);
		for(auto [x,id]:as[i]) res[id]+=tr.query(n)-tr.query(x-1);
	}
	tr.clear();
	for(int i=1;i<=n;i++){
		tr.add(ia[i],1);
		for(auto [x,id]:as2[i]) res[id]+=tr.query(ia[x.first])<=x.second;
	}
	for(int i=1;i<=ca;i++) cout<<res[i]<<"\n";
	return 0;
}