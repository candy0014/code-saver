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
string s[4005];
int res[4005][4005];
int a[4005],b[4005],id[4005];
void solve(int Ca){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>s[i],s[i]=" "+s[i];
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	for(int i=1;i<=n;i++){
		if(a[i]>0){
			for(int j=1;j<=n&&a[i];j++){
				if(s[i][j]=='+') s[i][j]='-',res[i][j]=1,a[i]--,b[j]--;
			}
		}
		else{
			for(int j=1;j<=n&&a[i];j++){
				if(s[i][j]=='-') s[i][j]='+',res[i][j]=1,a[i]++,b[j]++;
			}
		}
		if(a[i]){cout<<"No\n";return;}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++) if(s[i][j]=='+') a[i]++,b[j]--,res[i][j]^=1;
	}
	for(int i=1;i<=n;i++) id[i]=i;
	for(int i=1;i<=n;i++){
		sort(id+1,id+n+1,[&](int u,int v){return b[u]<b[v];});
		for(int j=1;j<=a[i];j++) res[i][id[j]]^=1,b[id[j]]++;
	}
	for(int i=1;i<=n;i++) if(b[i]){cout<<"No\n";return;}
	cout<<"Yes\n";
	for(int i=1;i<=n;i++,cout<<"\n") for(int j=1;j<=n;j++) cout<<res[i][j];
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
	// cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}