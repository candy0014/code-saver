#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m,sum[500005];
string s;
ll dp[500005];
int f[500005];
pair<int,ll> check(int x){
	for(int i=6;i<=n;i++){
		dp[i]=dp[i-1],f[i]=f[i-1];
		ll tmp=dp[i-6]+(s[i-5]!='d')+(s[i-4]!='o')+(s[i-3]!='c')+(s[i-2]!='k')+(s[i-1]!='e')+(s[i]!='r')+x;
		if(tmp<dp[i]) dp[i]=tmp,f[i]=f[i-6]+1;
		else if(tmp==dp[i]) f[i]=max(f[i],f[i-6]+1);
	}
	return make_pair(f[n],dp[n]);
}
int calc(int x){
	int l=-n-1,r=0,mid,res=0;
	ll ans=0;
	while(l<=r){
		mid=l+(r-l)/2;
		pair<int,ll>tmp=check(mid);
		if(tmp.first>=x) l=mid+1,res=mid,ans=tmp.second;
		else r=mid-1;
	}
	return ans-res*x;
}
void solve(){
	cin>>s>>m,n=s.length(),s=" "+s;
	for(int i=1;i<=n;i++) sum[i]=0;
	int cnt=0;
	for(int i=6;i<=n;i++) cnt+=(s[i-5]=='d'&&s[i-4]=='o'&&s[i-3]=='c'&&s[i-2]=='k'&&s[i-1]=='e'&&s[i]=='r');
	for(int i=1,l,r;i<=m;i++){
		cin>>l>>r,r=min(r,n/6);
		if(l<=r) sum[l]++,sum[r+1]--;
	}
	int ma=0;
	for(int i=1;i<=n/6;i++) sum[i]+=sum[i-1],ma=max(ma,sum[i]);
	if(ma==0){cout<<"0\n";return;}
	int res=n;
	for(int i=cnt;i<=n/6;i++) if(sum[i]==ma){res=min(res,calc(i));break;}
	for(int i=cnt;i>=1;i--) if(sum[i]==ma){res=min(res,cnt-i);break;}
	cout<<res<<"\n";
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}