#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
ll x[200005],res[200005];
struct BIT{
	int n,sum[200005],st[2000005],top;
	void add(int x,int k){st[++top]=x;while(x<=n)sum[x]+=k,x+=(x&(-x));}
	int query(int x){int t=0;while(x)t+=sum[x],x-=(x&(-x));return t;}
	void clear(int x){while(x<=n)sum[x]=0,x+=(x&(-x));}
	void clear(){while(top)clear(st[top--]);}
	int get(int x){
		int now=0;
		for(int i=19;i>=0;i--) if(now+(1<<i)<n&&sum[now+(1<<i)]<x) now+=(1<<i),x-=sum[now];
		return now+1;
	}
	int get2(int x){
		int now=0;
		for(int i=19;i>=0;i--) if(now+(1<<i)<n&&sum[now+(1<<i)]+(1<<i)<x) now+=(1<<i),x-=sum[now]+(1<<i);
		return now+1;
	}
}b1,b2;
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++){
		char g;
		cin>>g>>x[i];
		if(g=='p') res[i]=x[i],x[i]=-x[i];
	}
	b1.clear(),b1.n=n;
	for(int i=1;i<=n;i++) b1.add(i,1);
	for(int i=n;i>=1;i--){
		if(x[i]<0){b1.add(-x[i],-1);continue;}
		ll t=i-x[i];
		b2.clear(),b2.n=i;
		for(int j=i-1;;j--){
			if(x[j]>=0){t+=x[j];break;}
			int tmp=b1.query(-x[j]);
			t+=i-tmp-(b2.query(i)-b2.query(tmp)),b2.add(tmp,1);
		}
		res[i]=b1.get(b2.get2(t)),b1.add(res[i],-1);
	}
	for(int i=1;i<=n;i++) cout<<res[i]<<" \n"[i==n];
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}