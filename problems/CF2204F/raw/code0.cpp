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
ll ksm(ll u,ll v=mod-2){ll tmp=1;u%=mod;while(v) tmp=tmp*((v&1)?u:1)%mod,u=u*u%mod,v>>=1;return tmp;}
int n,m,a[500005],pre[500005],nex[500005],st[500005],top;
pair<int,int> p[500005];
int pr[500005],suf[500005],cnt[500005];
void solve(int Ca){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++){
		while(top&&a[i]<a[st[top]]) top--;
		pr[i]=st[top],st[++top]=i;
	}
	st[top=0]=n+1;
	for(int i=n;i>=1;i--){
		while(top&&a[i]<=a[st[top]]) top--;
		nex[i]=st[top],st[++top]=i;
	}
	ll tmp=0;
	for(int i=1;i<=n;i++) tmp=(tmp+ksm(a[i])*i%mod*(n-i+1))%mod,p[i]=make_pair(a[i],1ll*(i-pr[i])*(nex[i]-i)%mod);
	sort(p+1,p+n+1);
	for(int i=1;i<=n;i++){
		int a=p[i].first,b=p[i].second;
		pre[i]=(pre[i-1]+(1ll*(a-1)*ksm(a)%mod-a)*b%mod+mod)%mod;
		cnt[i]=(cnt[i-1]+b)%mod;
	}
	for(int i=n;i>=1;i--){
		int a=p[i].first,b=p[i].second;
		suf[i]=(suf[i+1]+ksm(a)*b)%mod;
	}
	for(int i=1,r=0,k;i<=m;i++){
		cin>>k;
		while(r<n&&p[r+1].first<=k) r++;
		cout<<(tmp+pre[r]+1ll*suf[r+1]*k%mod+1ll*(k+1)*cnt[r]%mod)%mod<<"\n";
	}
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