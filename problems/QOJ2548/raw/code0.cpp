#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,a,b,k;
string s;
ll cnta[200005],cntb[200005],li[200005],V;
int dp[200005];
struct BIT{
	int ma[200005];
	void init(){for(int i=1;i<=V;i++)ma[i]=-1e9;}
	void add(int x,int k){while(x<=V)ma[x]=max(ma[x],k),x+=(x&(-x));}
	int query(int x){int t=-1e9;while(x)t=max(t,ma[x]),x-=(x&(-x));return t;}
	void clear(int x){while(x<=V)ma[x]=-1e9,x+=(x&(-x));}
}p;
void solve(int l,int r){
	if(l==r){if(l)dp[l]=max(dp[l],dp[l-1]);return;}
	int mid=(l+r)>>1;solve(l,mid);
	for(int i=l;i<l+k&&i<=mid;i++){
		vector<int>idl,idr;
		for(int j=i;j<=r;j+=k) (j<=mid?idl:idr).emplace_back(j);
		sort(idl.begin(),idl.end(),[&](int u,int v){return cntb[u]<cntb[v];});
		sort(idr.begin(),idr.end(),[&](int u,int v){return cntb[u]<cntb[v];});
		int t=-1;
		for(auto j:idr){
			while(t+1<(int)idl.size()&&cntb[idl[t+1]]<=cntb[j]) t++,p.add(cnta[idl[t]],dp[idl[t]]-idl[t]);
			dp[j]=max(dp[j],p.query(cnta[j])+j);
		}
		for(int j=0;j<=t;j++) p.clear(cnta[idl[j]]);
	}
	solve(mid+1,r);
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>a>>b>>s,s=" "+s,k=a+b;
	for(int i=1;i<=n;i++) cnta[i]=cnta[i-1]+a-(s[i]=='R')*(a+b),cntb[i]=cntb[i-1]+b-(s[i]=='B')*(a+b);
	for(int i=0;i<=n;i++) li[++V]=cnta[i];
	sort(li+1,li+V+1),V=unique(li+1,li+V+1)-li-1;
	for(int i=0;i<=n;i++) cnta[i]=lower_bound(li+1,li+V+1,cnta[i])-li;
	p.init(),solve(0,n);
	cout<<dp[n]/k<<"\n";
	return 0;
}