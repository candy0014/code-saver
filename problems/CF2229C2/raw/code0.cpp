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
int n,a[200005];
ll sum[200005],pre[200005];
vector<int>res;
void solve(int Ca){
	cin>>n,res.clear();
	for(int i=1;i<=n;i++) cin>>a[i],sum[i]=sum[i-1]+a[i],pre[i]=pre[i-1]+abs(a[i]);
	int mak=0;ll ma=sum[n];
	for(int i=1;i<=n;i++) if(a[i]>0&&pre[i-1]-a[i]+sum[n]-sum[i]>ma) ma=pre[i-1]-a[i]+sum[n]-sum[i],mak=i;
	if(!mak){cout<<"0\n\n";return;}
	int flag=0;
	for(int i=mak-1;i>=1;i--){
		if((a[i]>0)^flag) res.emplace_back(i),flag^=1;
	}
	res.emplace_back(mak);
	cout<<res.size()<<"\n";
	for(auto x:res) cout<<x<<" ";cout<<"\n";
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
	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}