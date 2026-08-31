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
int n,m;
int a[1000005],b[1000005],tot;
int d[30];
void insert(int x){
	for(int i=29;i>=0;i--) if((x>>i)&1){
		if(!d[i]){
			for(int j=i-1;j>=0;j--) if(d[j]) x=min(x,d[j]^x);
			d[i]=x;
			for(int j=i+1;j<=29;j++) if(d[j]) d[j]=min(d[j],d[j]^x);
			return;
		}
		x^=d[i];
	}
}
void solve(int Ca){
	cin>>n,m=(1<<n);
	memset(d,0,sizeof(d));
	for(int i=1;i<m;i++) cin>>a[i],insert(a[i]);
	sort(a,a+m);
	vector<int>p;
	for(int i=0;i<=29;i++) if(d[i]) p.emplace_back(d[i]);
	if(p.size()>n){cout<<"-1\n";return;}
	while(p.size()<n) p.emplace_back(0);
	tot=0;
	for(int i=0;i<m;i++){
		int x=0;
		for(int j=0;j<n;j++) if((i>>j)&1) x^=p[j];
		b[tot++]=x;
	}
	sort(b,b+m);
	for(int i=0;i<m;i++) if(b[i]!=a[i]){cout<<"-1\n";return;}
	sort(p.begin(),p.end());
	for(auto x:p) cout<<x<<" ";
	cout<<"\n";
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