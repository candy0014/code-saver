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
int n,a[200005],li[200005];
vector<int>p[200005];
int vis[200005];
bool check(int x,int y){
	if(x<1||x>n||y<1||y>n) return 0;
	swap(a[x],a[y]);
	for(int i=1;i<=n;i++) vis[i]=0;
	for(int i=1;i<=n;i++){
		if(vis[a[i]]){
			swap(a[x],a[y]);
			return 0;
		}
		int j=i;
		while(j<n&&a[j+1]==a[j]) j++;
		vis[a[i]]=1,i=j;
	}
	swap(a[x],a[y]);
	return 1;
}
void solve(int Ca){
	cin>>n;
	for(int i=1;i<=n;i++) p[i].clear(),cin>>a[i],li[i]=a[i];
	sort(li+1,li+n+1);
	for(int i=1;i<=n;i++) a[i]=lower_bound(li+1,li+n+1,a[i])-li,p[a[i]].emplace_back(i);
	int flag=1;
	if(check(1,1)){cout<<"YES\n";return;}
	for(int i=1;i<=n;i++) if(p[i].size()){
		if(p[i].back()-p[i][0]+1>p[i].size()){
			int pl=0,pr=0;
			for(int j=2;j<(int)p[i].size();j++) if(p[i][j]!=p[i][j-1]+1) pl=p[i][j]-1;
			for(int j=1;j<(int)p[i].size()-1;j++) if(p[i][j]!=p[i][j-1]+1) pr=p[i][j]-1;
			if(!check(p[i][0],p[i][1]-1)&&!check(p[i][0],p[i].back()+1)&&!check(p[i][0],pl)&&
			!check(p[i].back(),p[i][0]-1)&&!check(p[i].back(),p[i][p[i].size()-2]+1)&&!check(p[i].back(),pr))flag=0;
			break;
		}
	}
	if(flag==0) cout<<"NO\n";
	else cout<<"YES\n";
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