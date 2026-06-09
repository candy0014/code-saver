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
int n,m,a[100005],b[100005],l[100005],r[100005],tot;
pair<int,int>t[200005];
void solve(int Ca){
	cin>>n>>m,tot=0;
	for(int i=1;i<=n;i++) cin>>a[i],t[++tot]=make_pair(a[i],0);
	for(int i=1;i<=m;i++) cin>>b[i],t[++tot]=make_pair(b[i],1);
	sort(t+1,t+tot+1);
	ll res=t[tot].first-t[1].first;
	for(int i=1;i<=tot;i++) if(t[i].second==0){
		int j=i+1;
		while(j<=tot&&t[j].second) j++;
		if(j>tot) break;
		int ma=0;
		for(int k=i;k<j;k++) ma=max(ma,t[k+1].first-t[k].first);
		res-=ma;
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
	
	int ID,Ca=1;
	cin>>ID>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}