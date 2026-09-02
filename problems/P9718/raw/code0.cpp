#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
string s;
int k,n;
int dp[25][25][2];
void solve(){
	cin>>s>>k;
	if(k==0){
		ll res=1;
		s="0"+s;
		for(int i=s.length()-1;i>=0;i--){
			if(s[i]!='9') break;
			res*=10;
		}
		cout<<res<<"\n";
		return;
	}
	int cnt=0;
	for(int i=s.length()-1;s[i]=='0';i--) cnt++;
	s=s.substr(0,s.length()-cnt);	
	while(s.length()<k) s="0"+s;
	s="0"+s;reverse(s.begin(),s.end()),s=" "+s;
	n=s.length()-1;
	memset(dp,0,sizeof(dp));
	dp[0][0][0]=1;
	for(int i=0;i<=n;i++){
		for(int j=0;j<=k;j++){
			if(dp[i][j][0]){
				dp[i+1][j][0]=1;
				if(s[i+1]!='0') dp[i+1][j+1][1]=1;
			}
			if(dp[i][j][1]){
				dp[i+1][j+1][1]=1;
				if(s[i+1]!='9') dp[i+1][j][0]=1;
			}
		}
	}
	if(!dp[n][k][0]){cout<<"-1\n";return;}
	ll res=0,op=0;
	for(int i=n;i>=1;i--){
		if(op==0){
			res*=10;
			if(!dp[i-1][k][0]) op=1;
		}
		else{
			k--;
			if(dp[i-1][k][1]) res=res*10+'9'-s[i];
			else res=res*10+'9'+1-s[i],op=0;
		}
	}
	cout<<res;
	for(int i=1;i<=cnt;i++) cout<<"0";
	cout<<"\n";
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}
