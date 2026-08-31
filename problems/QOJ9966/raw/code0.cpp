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
int n;
double p[500005];
double dp[500005];
int st[500005],head,tail;
double F(int id,int x){return dp[id]+(1-p[id])*x;}
double calc(int a,int b){return (dp[a]-dp[b])/(p[a]-p[b]);}
void solve(int Ca){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>p[i];
	double res=0;
	head=1,tail=0;
	for(int i=n,r=n;i>=1;i--){
		dp[i]=i;
		while(head<tail&&F(st[head],i)<=F(st[head+1],i)) head++;
		if(head<=tail) dp[i]=max(dp[i],F(st[head],i));
		dp[i]*=p[i],res=max(res,dp[i]);
		while(head<tail&&calc(i,st[tail-1])>=calc(st[tail],st[tail-1])) tail--;
		st[++tail]=i;
	}
	cout<<fixed<<setprecision(13)<<res<<"\n";
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