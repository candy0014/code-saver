#include <bits/stdc++.h>
using namespace std;
int n,a[2];
string s;
int cnt[250005];
int t[250005][2];
int dp[250005][2],pre[250005][2];
int st[2][250005],head[2],tail[2];
pair<int,string> get(int k,int op,int fl=0){
	st[0][head[0]=tail[0]=0]=0,st[1][head[1]=tail[1]=0]=0;
	for(int i=1;i<=n;i++){
		dp[i][0]=dp[i][1]=1e9;
		for(int o:{0,1}) while(head[o]<=tail[o]&&(st[o][head[o]]<i-k||st[o][head[o]]<t[i][o])) head[o]++;
		if(head[op]<=tail[op]){
			int pos=st[op][head[op]];
			if(dp[pos][op]<dp[i][op^1]) dp[i][op^1]=dp[pos][op],pre[i][op^1]=pos;
		}
		if(head[op^1]<=tail[op^1]){
			int pos=st[op^1][head[op^1]];
			if(dp[pos][op^1]+cnt[i]-cnt[pos]<dp[i][op]) dp[i][op]=dp[pos][op^1]+cnt[i]-cnt[pos],pre[i][op]=pos;
		}
		if(dp[i][op]<=n){
			while(head[op]<=tail[op]&&dp[i][op]<=dp[st[op][tail[op]]][op]) tail[op]--;
			st[op][++tail[op]]=i;
		}
		if(dp[i][op^1]<=n){
			while(head[op^1]<=tail[op^1]&&dp[i][op^1]-cnt[i]<=dp[st[op^1][tail[op^1]]][op^1]) tail[op^1]--;
			st[op^1][++tail[op^1]]=i;
		}
	}
	if(!fl) return make_pair(min(dp[n][0],dp[n][1]),"");
	int i=n,now=dp[n][0]>dp[n][1];
	string res="";
	while(i){
		int len=i-pre[i][now];
		for(int i=1;i<=len;i++) res+=char(now+'0');
		i-=len,now^=1;
	}
	reverse(res.begin(),res.end());
	return make_pair(min(dp[n][0],dp[n][1]),res);
}
pair<int,string> check(int x,int op=0){
	pair<int,string> t0=get(x,0,op),t1=get(x,1,op);
	if(!op) return make_pair(t0.first<=a[0]&&t1.first<=a[1],"");
	if(t0.first==a[0]) return t0;
	if(t1.first==a[1]) return t1;
	int cnt=t1.first;
	for(int i=0;i<n-1;i++){
		cnt=cnt-t1.second[i]+t0.second[i];
		if(cnt==a[1]&&t0.second[i]!=t1.second[i+1]) return make_pair(1,t0.second.substr(0,i+1)+t1.second.substr(i+1));
	}
	return make_pair(0,"");
}
void solve(){
	cin>>n>>a[0]>>a[1]>>s,s=" "+s;
	for(int i=1;i<=n;i++) cnt[i]=cnt[i-1]+(s[i]=='?');
	for(int i=1;i<=n;i++){
		t[i][0]=t[i-1][0],t[i][1]=t[i-1][1];
		if(s[i]!='?') t[i][s[i]-'0']=i;
	}
	int l=1,r=n,mid,res=0;
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid).first) res=mid,r=mid-1;
		else l=mid+1;
	}
	cout<<res<<"\n"<<check(res,1).second<<"\n";
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;	
}