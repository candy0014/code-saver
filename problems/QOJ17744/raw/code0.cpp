#include <bits/stdc++.h>
using namespace std;
int a[15];
int res[8][11][60005],dis[1024],g[1024];
void dfs(int now,int k,int n){
	if(res[k][n][now]!=-1) return;
	int tmp=now;
	for(int i=0;i<n;i++) a[i]=tmp%3,tmp/=3;
	for(int i=1;i<n;i++) if((a[i]|a[i-1])==3){res[k][n][now]=1;return;}
	for(int i=0;i<n;i++) if(!a[i]) tmp|=(1<<i);
	res[k][n][now]=0;
	for(int i=tmp;i;i=(i-1)&tmp) if((__builtin_popcount(i)&1)&&dis[i]<=k){
		dfs(now+g[i],k,n),dfs(now+g[i]*2,k,n);
		if(!res[k][n][now+g[i]]||!res[k][n][now+2*g[i]]) res[k][n][now]=1;
	}
}
int n,k,cnt;
string s;
int solve(int l,int r){
	if(r-l+1<=k+3){
		int x=0;
		for(int i=l;i<=r;i++) x=x*3+(s[i]=='W'?0:(s[i]=='R'?1:2));
		return res[k][r-l+1][x];
	}
	if(s[l]=='W'&&s[l+1]=='W'&&s[r]=='W'&&s[r-1]=='W') return solve(l+2,r-2);
	if((s[l]=='W'&&s[l+1]=='W')||(s[r]=='W'&&s[r-1]=='W')) return 1;
	char gl=s[l],gr=s[r];
	if(gl=='W') gl=s[l+1];
	if(gr=='W') gr=s[r-1];
	return (gl!=gr)^(cnt&1);
}
void solve(){
	cin>>n>>k>>s,s=" "+s,cnt=0;
	for(int i=1;i<=n;i++) cnt+=(s[i]=='W');
	if(solve(1,n)) cout<<"Amy\n";
	else cout<<"Aimee\n";
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	memset(res,-1,sizeof(res));
	for(int i=1;i<1024;i++){
		dis[i]=__lg(i)-__lg(i&(-i));
		for(int j=9;j>=0;j--) g[i]=g[i]*3+((i>>j)&1);
	}
	for(int i=0;i<=7;i++) for(int j=0;j<=i+3;j++) dfs(0,i,j);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}
