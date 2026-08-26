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
int n,a[100005],b[100005];
set<pair<int,int> >res;
int id[100005],st[100005],top;
int mi[100005][20];
int query(int l,int r){
	int t=__lg(r-l+1);
	return min(mi[l][t],mi[r-(1<<t)+1][t]);
}
void work(){
	for(int i=1;i<=n;i++) id[b[i]]=i;
	for(int i=1;i<=n;i++) mi[i][0]=id[abs(a[i])];
	for(int j=1;j<20;j++) for(int i=1;i+(1<<j)-1<=n;i++) mi[i][j]=min(mi[i][j-1],mi[i+(1<<(j-1))][j-1]);
	st[top=0]=0;
	for(int i=1;i<=n;i++){
		while(top&&a[st[top]]<a[i]) top--;
		if(top){
			int u=query(st[top],i-1);
			if(u>id[abs(a[i])]){cout<<"No\n";exit(0);}
			res.insert(make_pair(b[u],abs(a[i])));
		}
		st[++top]=i;
	}
}
void solve(int Ca){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	work();
	for(int i=1;i<=n;i++) swap(a[i],b[i]),a[i]=-a[i];
	work();
	cout<<"Yes\n";
	cout<<res.size()<<"\n";
	for(auto [x,y]:res) cout<<x<<" "<<y<<"\n";
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