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
int n,a[4005],p[4005];
void work(int x,int y){
	if(x==y) return;
	cout<<"? "<<x<<" "<<y<<endl;
	cin>>x>>y;
	swap(p[a[x]],p[a[y]]),swap(a[x],a[y]);
}
void solve(int Ca){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],p[a[i]]=i;
	if(n&1){
		int x=(n+1)/2;
		while(p[x]!=x) work(p[x],x);
	}
	for(int i=1,j=n;i<j;i++,j--){
		work(p[i],n-p[j]+1);
		int x=0;
		if(a[i]!=i) x=p[i];
		else x=n-p[j]+1;
		while(a[i]!=i||a[j]!=j) work(i,x);
	}
	cout<<"!"<<endl;
}
int main(){
	int Ca=1;
	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}