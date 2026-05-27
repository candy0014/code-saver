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
vector<int>G[15];
int n,a[1100],ca;
void solve(int Ca){
	cin>>n>>ca;
	for(int i=0;i<(1<<n);i++) a[i]=i;
	G[0]={0};
	for(int i=1;i<=n;i++){
		G[i]=G[i-1];
		for(int j=G[i-1].size()-1;j>=0;j--) G[i].emplace_back(G[i-1][j]+(1<<(i-1)));
	}
	while(ca--){
		int op;
		cin>>op;
		if(op==1){
			int m;
			cin>>m;
			while(m--){
				int k;
				cin>>k;
				for(int i=0;i<(1<<n);i++) if(a[i]<(1<<k)) a[i]=G[k][a[i]];
			}
		}
		else{
			string xx;
			int x=0;
			cin>>xx;
			for(int i=0;xx[i];i++) x=x*2+xx[i]-'0';
			int flag=0;
			for(int i=n-1;i>=0;i--){
				int y=(a[x]>>i)&1;
				if(y) flag=1;
				if(flag) cout<<y;
			}
			if(!flag) cout<<"0";
			cout<<"\n";
		}
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