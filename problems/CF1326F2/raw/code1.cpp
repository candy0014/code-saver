#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
string s[14];
vector<ll>dp[16384][14];
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=0;i<n;i++) cin>>s[i];
	for(int i=1;i<(1<<n);i++){
		int m=1<<(__builtin_popcount(i)-1);
		for(int j=0;j<n;j++) if((i>>j)&1) dp[i][j].resize(m);
	}
	for(int i=1;i<(1<<n)-1;i++){
		int m=__builtin_popcount(i)-1;
		if(m==0){
			dp[i][__lg(i)][0]=1;
		}
		for(int j=0;j<n;j++) if((i>>j)&1){
			for(int p=0;p<n;p++) if(!((i>>p)&1)){
				for(int k=0;k<(1<<m);k++){
					dp[i|(1<<p)][p][k|((s[j][p]-'0')<<m)]+=dp[i][j][k];
				}
			}
		}
	}
	for(int i=0;i<(1<<(n-1));i++){
		ll ans=0;
		for(int j=0;j<n;j++) ans+=dp[(1<<n)-1][j][i];
		cout<<ans<<" ";
	}
	cout<<"\n";
	return 0;
}