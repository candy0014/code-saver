#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,a[200005],li[200005];
struct BIT{
	int sum[200005];
	void add(int x,int k){while(x<=n)sum[x]+=k,x+=(x&(-x));}
	int query(int x){int t=0;while(x)t+=sum[x],x-=(x&(-x));return t;}
	void clear(){memset(sum,0,sizeof(sum));}
	int get(int k){
		int now=0;
		for(int i=19;i>=0;i--) if(now+(1<<i)<=n&&k>=sum[now+(1<<i)]) now+=(1<<i),k-=sum[now];
		return now;
	}
}b;
ll res[200005];
int pre[200005];
vector<int>as[200005];
int p[200005];
void work(){
	b.clear();
	for(int i=1;i<=n;i++) p[a[i]]=i,as[i].clear();
	for(int i=1;i<=n;i++) pre[p[i]]=b.query(p[i]),as[b.get(pre[p[i]]*2)].emplace_back(p[i]),b.add(p[i],1);
	b.clear();
	ll now=0;
	for(int i=1;i<=n;i++){
		now+=b.query(n)-b.query(a[i]),res[i]=min(res[i],now);
		b.add(a[i],1);
		for(auto x:as[i]) b.add(a[x],-1);
	}
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],li[i]=a[i];
	sort(li+1,li+n+1);
	for(int i=1;i<=n;i++) a[i]=lower_bound(li+1,li+n+1,a[i])-li;
	for(int i=1;i<=n;i++) res[i]=1e18;
	work();
	for(int i=1;i<=n;i++) a[i]=n-a[i]+1;
	work();
	for(int i=1;i<=n;i++) cout<<res[i]<<"\n";	
	return 0;
}
