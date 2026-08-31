#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
const ll mod=998244353;
const ll inf=2e9;
const int N=2e5+5;
const int M=2e5+5;
const int V=1e9+5;
int n,c;
vector<int>p[500005];
struct node{
	int l,r,w,x;
}s[5000005];
int li[10000005],ln;
int tot;
ll cnt[10000005],sum[10000005];
void solve(int Ca){
	cin>>n>>c;
	for(int i=1;i<=c;i++) p[i].clear();
	for(int i=1;i<=n;i++) sum[i]=0;
	for(int i=1;i<=n;i++){
		int x,u,v;
		cin>>x>>u;
		while(u--){
			cin>>v;
			p[v].emplace_back(x);
		}
	}
	tot=0;
	for(int i=1;i<=c;i++){
		sort(p[i].begin(),p[i].end());
		s[++tot]=node{1,p[i][0],-1,p[i][0]};
		s[++tot]=node{p[i].back(),V,1,-p[i].back()};
		for(int j=1;j<(int)p[i].size();j++){
			int l=p[i][j-1],r=p[i][j],mid=(l+r)>>1;
			s[++tot]=node{l,mid,1,-l};
			s[++tot]=node{mid+1,r,-1,r};
		}
	}
	ln=0;
	for(int i=1;i<=tot;i++) li[++ln]=s[i].l,li[++ln]=s[i].r+1;
	sort(li+1,li+ln+1),ln=unique(li+1,li+ln+1)-li-1;
	for(int i=1;i<=ln;i++) cnt[i]=sum[i]=0;
	for(int i=1;i<=tot;i++){
		s[i].l=lower_bound(li+1,li+ln+1,s[i].l)-li;
		s[i].r=lower_bound(li+1,li+ln+1,s[i].r+1)-li;
		cnt[s[i].l]+=s[i].w,cnt[s[i].r]-=s[i].w;
		sum[s[i].l]+=s[i].x,sum[s[i].r]-=s[i].x;
	}
	for(int i=1;i<=ln;i++) cnt[i]+=cnt[i-1],sum[i]+=sum[i-1];
	ll mi=1e18;
	for(int i=1;i<ln;i++){
		if(cnt[i]>=0) mi=min(mi,1ll*cnt[i]*li[i]+sum[i]);
		else mi=min(mi,1ll*cnt[i]*(li[i+1]-1)+sum[i]);
	}
	cout<<mi<<"\n";
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