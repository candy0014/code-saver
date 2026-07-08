#include <bits/stdc++.h>
using namespace std;
const int mod=1e9+7,inv2=(mod+1)/2;
string s;
int n,ca,sum[10005],cnt,al=1;
int dp[10005],f[10005][10005],g[10005];
void add(int x){
    for(int j=cnt-1;j>=0;j--) dp[j+1]=(dp[j+1]+1ll*dp[j]*x)%mod;
}
void del(int x){
    for(int j=0;j<cnt;j++) dp[j+1]=(dp[j+1]-1ll*dp[j]*x%mod+mod)%mod;
}
int calc(){
    int res=0;
    for(int i=0;i<=cnt;i++) res=(res+1ll*g[i]*dp[cnt-i])%mod;
    return 1ll*res*al%mod;
}
int main(){
    // freopen("test.in","r",stdin);
    // freopen("test.out","w",stdout);
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>s>>ca,n=s.length(),s=" "+s;
    for(int i=1;i<=n;i++) sum[i]=sum[i-1]+s[i]-'0';
    dp[0]=1;
    for(int i=1;i<=n;i++) if(s[i]=='0'){
        for(int j=cnt;j>=0;j--) dp[j+1]=(dp[j+1]+1ll*dp[j]*sum[i])%mod;
        cnt++,al=1ll*al*inv2%mod;
    }
    f[0][0]=1,g[0]=1;
    for(int i=1;i<=cnt;i++){
        for(int j=1;j<=i;j++){
            f[i][j]=(1ll*f[i-1][j]*j+f[i-1][j-1])%mod,g[i]=(g[i]+f[i][j])%mod;
        }
    }
    cout<<calc()<<"\n";
    while(ca--){
        int x;cin>>x;
        if(s[x]!=s[x+1]){
            if(s[x]=='0') del(sum[x]),add(++sum[x]);
            else del(sum[x]),add(--sum[x]);
            swap(s[x],s[x+1]);
        }
        cout<<calc()<<"\n";
    }
    return 0;
}