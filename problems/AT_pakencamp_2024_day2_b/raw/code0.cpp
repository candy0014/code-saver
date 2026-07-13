#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1000005;
int ID,n,k,mod,inv2,ipw[1000005];
ll ksm(ll u,ll v=mod-2){ll tmp=1;u%=mod;while(v) tmp=tmp*((v&1)?u:1)%mod,u=u*u%mod,v>>=1;return tmp;}
ll jie[N],inv[N];
void init(int n=N-3){
    jie[0]=1,ipw[0]=1;
    for(int i=1;i<=n;i++) jie[i]=1ll*jie[i-1]*i%mod,ipw[i]=1ll*ipw[i-1]*inv2%mod;
    inv[n]=ksm(jie[n],mod-2);
    for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
ll A(ll u,ll v){
    if(v<0||v>u) return 0;
    return 1ll*jie[u]*inv[u-v]%mod;
}
ll C(ll u,ll v){
    if(v<0||v>u) return 0;
    return 1ll*jie[u]*inv[v]%mod*inv[u-v]%mod;
}
vector<int>e[1000005];
int du[1000005],dp[1000005];
int calc(int u,int fa=0){
    int cnt=0;
    for(auto v:e[u]) if(v!=fa) cnt++;
    if(cnt<k) return inv2;
    vector<int>f(k,0);
    cnt=0,f[0]=1;
    for(auto v:e[u]) if(v!=fa){
        if(dp[v]==inv2){cnt++;continue;}
        for(int i=k-1;i>=1;i--) f[i]=(1ll*f[i]*(1-dp[v]+mod)+1ll*f[i-1]*dp[v])%mod;
        f[0]=1ll*f[0]*(1-dp[v]+mod)%mod;
    }
    int res=0;
    for(int i=k-1,now=0;i>=0;i--){
        now=(now+C(cnt,k-i-1))%mod;
        res=(res+1ll*f[i]*now%mod*ipw[cnt])%mod;
    }
    return (inv2+1ll*inv2*(1-res+mod)%mod)%mod;
}
void dfs(int u,int fa){
    int cnt=0;
    for(auto v:e[u]) if(v!=fa) dfs(v,u),cnt++;
    dp[u]=calc(u,fa);
}
int ans;
void dfs2(int u,int fa){
    ans=(ans+dp[u])%mod;
    unordered_map<int,int>mp;
    for(auto v:e[u]) if(v!=fa){
        int tv=dp[v],tu=dp[u];
        if(du[v]<k) dp[v]=inv2;
        else{
            if(du[u]<=k) dp[u]=inv2;
            else{
                if(mp.count(dp[v])) dp[u]=mp[dp[v]];
                else dp[u]=mp[dp[v]]=calc(u,v);
            }
            dp[v]=calc(v);
        }
        dfs2(v,u),dp[v]=tv,dp[u]=tu;
    }
}
int main(){
    // freopen("virus.in","r",stdin);
    // freopen("virus.out","w",stdout);
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>/*ID>>*/n>>k>>mod,inv2=(mod+1)/2;
    init();
    if(k==1){cout<<1ll*n*(ksm(2,n)-1)%mod<<"\n";return 0;}
    for(int i=1,u,v;i<n;i++) cin>>u>>v,e[u].emplace_back(v),e[v].emplace_back(u),du[u]++,du[v]++;
    dfs(1,0);
    dfs2(1,0);
    cout<<1ll*ans*ksm(2,n)%mod<<"\n";
    return 0;
}