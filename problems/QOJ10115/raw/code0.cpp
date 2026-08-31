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
ll n,k,m;
char tran1(int x){
	if(x<10) return x+'0';
	return x-10+'A';
}
int tran2(char x){
	if(x<='9') return x-'0';
	return x-'A'+10;
}
int vis[40];
void solve(int Ca){
	cin>>n>>k>>m,memset(vis,0,sizeof(vis));
	for(int i=1;i<=m;i++){
		char g;cin>>g;vis[tran2(g)]=1;
	}
	vector<int>t;
	for(int i=0;i<n;i++) if(!vis[i]) t.emplace_back(i);
	string res="";
	while(k) res=tran1(t[k%t.size()])+res,k/=t.size();
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