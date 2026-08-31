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
int n,m,k,len;
string s;
int sum[2005][2005];
void solve(int Ca){
	cin>>n>>m>>k>>s,len=s.length();
	int x=1,y=1,xx=n,yy=m,nowx=1,nowy=1;
	for(int i=1;i<=n*2+2;i++) for(int j=1;j<=m*2+2;j++) sum[i][j]=0;
	sum[nowx+n][nowy+m]++;
	for(auto g:s){
		if(g=='U') nowx++;
		if(g=='D') nowx--;
		if(g=='L') nowy++;
		if(g=='R') nowy--;
		x=max(x,nowx),y=max(y,nowy),xx=min(xx,nowx+n-1),yy=min(yy,nowy+m-1);
		if(nowx+n>=1&&nowx+n<=n*2+2&&nowy+m>=1&&nowy+m<=m*2+2) sum[nowx+n][nowy+m]=1;
	}
	if(x>xx||y>yy){
		if(!k) cout<<n*m<<"\n";
		else cout<<"0\n";
		return;
	}
	for(int i=1;i<=n*2+2;i++) for(int j=1;j<=m*2+2;j++) sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
	int res=0;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++){
		int tmp=sum[xx-i+1+n][yy-j+1+m]-sum[x-1-i+1+n][yy-j+1+m]-sum[xx-i+1+n][y-1-j+1+m]+sum[x-1-i+1+n][y-1-j+1+m];
		tmp=(xx-x+1)*(yy-y+1)-tmp;
		res+=tmp==k;
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
	
	int Ca=1;
	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}