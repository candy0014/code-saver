#include <bits/stdc++.h>
using namespace std;
const int mod=998244353;
int n;
string s;
int dp[3005][3005],du[3005][3005],cnt[3005],sum[3005];
pair<int,int> to0[3005],to1[3005];
void add(int &u,int v){u=(u+v)%mod;}
queue<pair<int,int> >q;
void solve(){
	cin>>n>>s,s=" "+s;
	for(int i=1;i<=n;i++) cnt[i]=cnt[i-1]+(s[i]=='?'),sum[i]=sum[i-1]+(s[i]=='1');
	for(int i=0;i<=n+1;i++) for(int j=0;j<=n+1;j++) dp[i][j]=du[i][j]=0;
	for(int i=0;i<=n+1;i++){
		to0[i]=to1[i]=make_pair(n+1,n+1);
		for(int j=n;j>i;j--) if(cnt[j-1]-cnt[i]||(sum[j-1]-sum[i])%2==0){
			if(s[j]!='1') ((sum[j]&1)?to0[i].second:to0[i].first)=j;
			if(s[j]!='0') ((sum[j]&1)?to1[i].second:to1[i].first)=j;
		}
	}
	for(int i=0;i<=n+1;i++) for(int j=0;j<=n+1;j++){
		if(i==n+1&&j==n+1) continue;
		du[min(to0[i].first,to0[j].first)][min(to0[i].second,to0[j].second)]++;
		du[min(to1[i].first,to1[j].first)][min(to1[i].second,to1[j].second)]++;
	}
	for(int i=0;i<=n+1;i++) for(int j=0;j<=n+1;j++) if(!du[i][j]) q.push(make_pair(i,j));
	dp[0][0]=1;
	int res=0;
	while(!q.empty()){
		int i=q.front().first,j=q.front().second;q.pop();
		if((i<=n&&(cnt[n]-cnt[i]||(sum[n]-sum[i])%2==0))||(j<=n&&(cnt[n]-cnt[j]||(sum[n]-sum[j])%2==0))) add(res,dp[i][j]);
		int x=min(to0[i].first,to0[j].first),y=min(to0[i].second,to0[j].second);
		add(dp[x][y],dp[i][j]);
		if((!--du[x][y])) q.push(make_pair(x,y));
		x=min(to1[i].first,to1[j].first),y=min(to1[i].second,to1[j].second);
		add(dp[x][y],dp[i][j]);
		if((!--du[x][y])) q.push(make_pair(x,y));
	}
	cout<<res<<"\n";
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}