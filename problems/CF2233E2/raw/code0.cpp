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
int n,d,cnt[20],id[20],x[200005];
ll jie[20];
string s[20];
map<int,int>mp;
void solve(int Ca){
	cin>>n,d=__lg(n),mp.clear();
	for(int i=0;i<n;i++) x[i]=0;
	for(int i=0;i<=d;i++){
		cin>>s[i],cnt[i]=0,id[i]=i;
		for(int j=0;j<n;j++) cnt[i]+=s[i][j]-'0';
		mp[cnt[i]]++;
	}
	sort(id,id+d+1,[&](int u,int v){return cnt[u]>cnt[v];});
	for(int i=0;i<n;i++) for(int j=0;j<=d;j++) x[i]|=(s[id[j]][i]-'0')<<j;
	sort(x,x+n);
	for(int i=0;i<n;i++) if(x[i]!=i+1){cout<<"0\n";return;}
	ll res=1;
	for(auto x:mp) res*=jie[x.second];
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
	jie[0]=1;
	for(int j=1;j<20;j++) jie[j]=1ll*jie[j-1]*j;
	int Ca=1;
	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}