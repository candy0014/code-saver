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
ll a[100005],b[100005],c[100005];
int n;
int pre[100005],suf[100005],pp[100005],ss[100005];
bool check(ll x){
	int cnt=0;
	for(int i=0;i<=n+1;i++) pre[i]=suf[i]=pp[i]=ss[i]=0;
	for(int i=1;i<=n;i++){
		if(a[i]==0){
			if(b[i]>=x) cnt++;
			continue;
		}
		if(a[i]>0){
			int l=1,r=n,mid,res=n+1;
			while(l<=r){
				mid=(l+r)>>1;
				if(a[i]*c[mid]+b[i]>=x) res=mid,r=mid-1;
				else l=mid+1;
			}
			suf[res]++;
		}
		else{
			int l=1,r=n,mid,res=0;
			while(l<=r){
				mid=(l+r)>>1;
				if(a[i]*c[mid]+b[i]>=x) res=mid,l=mid+1;
				else r=mid-1;
			}
			pre[res]++;
		}
	}
	pre[0]=suf[n+1]=0;
	for(int i=n;i>=1;i--) pp[i]=pp[i+1]+pre[i];
	for(int i=1;i<=n;i++) ss[i]=ss[i-1]+suf[i];
	for(int i=1;i<=n;i++) pre[i]=min(i,pre[i-1]+pre[i]);
	for(int i=n;i>=1;i--) suf[i]=min(n-i+1,suf[i+1]+suf[i]);
	int ma=0;
	for(int i=1;i<=n+1;i++) ma=max(ma,min(i-1,pre[i-1]+pp[i])+min(n-i+1,suf[i]+ss[i-1]));
	return ma+cnt>=(n+1)/2;
}
void solve(int Ca){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	for(int i=1;i<=n;i++) cin>>c[i];
	sort(c+1,c+n+1);
	ll l=-3e18,r=3e18,mid,res=0;
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid)) l=mid+1,res=mid;
		else r=mid-1;
	}
	cout<<res<<"\n";
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