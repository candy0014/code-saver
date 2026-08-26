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
int cnt[100005],a[100005],id[100005];
void solve(int Ca){
	cin>>n;
	for(int i=1;i<=n;i++) cnt[i]=0;
	for(int i=1;i<=n;i++) cin>>a[i],cnt[a[i]]++,id[i]=i;
	if(n==1){cout<<"1\n";return;}
	sort(id+1,id+n+1,[&](int u,int v){return cnt[u]>cnt[v];});
	if(cnt[id[2]]==0){cout<<n<<"\n";return;}
	int ans=0;
	for(int i=1;i<=n;i++) if(i!=id[1]){
		int x=cnt[id[1]],y=cnt[i],res=x|y;
		x&=y;
		if(x) res|=(1<<(__lg(x)+1))-1;
		ans=max(ans,res);
	}
	cout<<ans<<"\n";
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