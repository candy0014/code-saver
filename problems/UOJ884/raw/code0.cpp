#include <bits/stdc++.h>
using namespace std;
const int mod=509;
int C[515][515];
int n,h[300005];
vector<int>p[300005];
int dp[600005],_dp[600005],f[600005];
int calc(int i,int j){
    if(h[j]<h[i]) return 0;
    return C[j-i+h[j]-h[i]][j-i];
}
int main(){
    // freopen("test.in","r",stdin);
    // freopen("test.out","w",stdout);
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    for(int i=0;i<=mod;i++){
        C[i][0]=1;
        for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
    }
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>h[i];
        p[(i+h[i])/mod+1].emplace_back(i);
    }
    if(h[n]==n){cout<<"0\n";return 0;}
    dp[0]=1;
    for(int i=1;i<=n/mod*2;i++){
        int m=(i-1)*mod;
        for(int j=0;j<=i*mod;j++) _dp[j]=(dp[j]+(j>=mod?dp[j-mod]:0))%mod;
        for(int j=0;j<(int)p[i].size();j++){
            int t=p[i][j];
            int l=max(0,m-t),r=min(m,h[t]);
            for(int k=l;k<=r;k++) f[t]=(f[t]-dp[k]*C[t+h[t]-m][h[t]-k])%mod;
            for(int k=j-1;k>=0&&k>=j-mod;k--) f[t]=(f[t]-f[p[i][k]]*calc(p[i][k],t))%mod;
            l=h[t],r=m+mod-t;
            for(int k=l;k<=r;k++) _dp[k]=(_dp[k]+f[t]*C[m+mod-t-h[t]][k-h[t]])%mod;
        }
        for(int j=0;j<=i*mod;j++) dp[j]=_dp[j];
    }
    cout<<(dp[n]+mod)%mod<<"\n";
    return 0;
}
