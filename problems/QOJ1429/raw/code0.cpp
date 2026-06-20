#include <bits/stdc++.h>
using namespace std;
int n,li[1000005],tot,pre[1000005],L[1000005];
struct node{int l,r;}s[500005];
int to[1000005][20];
bool check(int x){
	vector<int>p;p.emplace_back(0);
	for(int i=1;i<=tot;i++){
		if(p.back()<pre[i-1]) return 0;
		to[i][0]=*lower_bound(p.begin(),p.end(),pre[i-1]);
		for(int j=1;j<20;j++) to[i][j]=to[to[i][j-1]][j-1];
		int u=i;
		for(int j=0;j<20;j++) if((x>>j)&1) u=to[u][j];
		if(u<L[i]) p.emplace_back(i);
	}
	return 1;
}
void solve(){
	cin>>n,tot=0;
	for(int i=1;i<=n;i++) cin>>s[i].l>>s[i].r,li[++tot]=s[i].l,li[++tot]=s[i].r+1;
	sort(li+1,li+tot+1),tot=unique(li+1,li+tot+1)-li-1;
	for(int i=1;i<=tot;i++) pre[i]=0,L[i]=1e9;
	for(int i=1;i<=n;i++){
		s[i].l=lower_bound(li+1,li+tot+1,s[i].l)-li,s[i].r=lower_bound(li+1,li+tot+1,s[i].r+1)-li-1;
		pre[s[i].r]=max(pre[s[i].r],s[i].l),L[s[i].r]=min(L[s[i].r],s[i].l);
	}
	for(int i=2;i<=tot;i++) pre[i]=max(pre[i-1],pre[i]);
	for(int i=tot-1;i>=1;i--) L[i]=min(L[i+1],L[i]);
	int l=1,r=n,mid,res=1;
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid)) r=mid-1,res=mid;
		else l=mid+1;
	}
	check(res);
	vector<int>ans;
	for(int i=to[tot][0];i;i=to[i][0]) ans.emplace_back(i);
	cout<<res<<" "<<ans.size()<<"\n";
	for(auto x:ans) cout<<li[x]<<" ";cout<<"\n";
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}