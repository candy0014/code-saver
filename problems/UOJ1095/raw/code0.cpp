#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=998244353;
ll ksm(ll u,ll v=mod-2){ll tmp=1;u%=mod;while(v) tmp=tmp*((v&1)?u:1)%mod,u=u*u%mod,v>>=1;return tmp;}
int n,m,k,a[205];
vector<int>p;
int val1[205][205][205];
int f1[205][205][205],f2[205][205][205];
int c0[205][205],c1[205][205],tag[205][205];
inline void add(int &u,ll v){u=(u+v)%mod;}
namespace solve1{
    int dp[205][205];
    int calc(int l,int r,int x){
        if(a[r]){
            if(!tag[l][r]) return 0;
            return f2[c1[l][r-1]][c0[l][r-1]][x-1];
        }
        return 1ll*f1[c1[l][r-1]][c0[l][r-1]][x-1]*(m-(x-1))%mod;
    }
    int solve(int x){
        memset(dp,0,sizeof(dp));
        dp[0][0]=1;
        for(int i=0;i<k;i++){
            for(int j=0;j<n;j++) if(dp[i][j]){
                for(int t=j+1;t<=n;t++) add(dp[i+1][t],1ll*dp[i][j]*calc(j+1,t,x));
            }
        }
        int res=0;
        for(int i=1;i<=n;i++) add(res,1ll*dp[k][i]*ksm(m,c0[i+1][n]));
        return res;
    }
}
vector<int>va;
int vm;
int vis[205][205][205];
namespace solve2{
    int suf[205][205];
    int calcn(int l,int x,int p){
        if(suf[l][p]!=-1) return suf[l][p];
        int cnt=c1[l+1][n],g=c0[l+1][n];
        if(!vis[p][l+1][n]) cnt++;
        int res=0;
        for(int i=cnt;i<=x;i++) add(res,f1[cnt][g][i]);
        return suf[l][p]=res;
    }
    int dp[205][205][205];
    int solve(int x){
        memset(suf,-1,sizeof(suf));
        for(int i=0;i<=k;i++) for(int j=0;j<=n;j++) for(int p=0;p<=vm;p++) dp[i][j][p]=0;
        for(int i=0;i<=vm;i++){
            if(a[1]&&(i==vm||va[i]!=a[1])) continue;
            if(i==vm) dp[0][0][i]=m-vm;
            else dp[0][0][i]=1;
        }
        for(int i=1;i<=k;i++){
            for(int j=(i==k?n:(i*x));j<=n;j++){
                if(j==n){
                    add(dp[i][j][vm],dp[i-1][j][vm]);
                    for(int t=0;t<j;t++){
                        for(int p=0;p<=vm;p++){
                            add(dp[i][j][vm],1ll*dp[i-1][t][p]*calcn(t+1,x,p));
                        }
                    }
                    continue;
                }
                if(!a[j+1]){
                    for(int t=j-1;t>=(i-1)*x;t--){
                        add(dp[i][j][vm],1ll*dp[i-1][t][vm]*f2[c1[t+2][j]+1][c0[t+2][j]][x]%mod*(m-vm-1));
                        int h[2]={(int)(1ll*f2[c1[t+2][j]+1][c0[t+2][j]][x]*(m-vm)%mod),(int)(1ll*f2[c1[t+2][j]][c0[t+2][j]][x]*(m-vm)%mod)};
                        for(int p=0;p<vm;p++){
                            add(dp[i][j][vm],1ll*dp[i-1][t][p]*h[vis[p][t+2][j]]);
                        }
                    }
                }
                for(int t=j-1,flag=1;t>=(i-1)*x&&flag;t--){
                    int tmp=0,h[2]={f2[c1[t+2][j]+1][c0[t+2][j]][x],f2[c1[t+2][j]][c0[t+2][j]][x]};
                    for(int p=0;p<=vm;p++) if(dp[i-1][t][p]){
                        add(tmp,1ll*dp[i-1][t][p]*h[vis[p][t+2][j]]);
                    }
                    flag=0;
                    for(int p=0;p<vm;p++){
                        if(!vis[p][t+1][j]&&(!a[j+1]||a[j+1]==va[p])){
                            add(dp[i][j][p],tmp-1ll*dp[i-1][t][p]*h[vis[p][t+2][j]]);
                            flag=1;
                        }
                    }
                }
            }
        }
        return dp[k][n][vm];
    }
}
int main(){
    // freopen("test.in","r",stdin);
    // freopen("test.out","w",stdout);
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n>>m>>k;
    int cnt=0;
    for(int i=1;i<=n;i++){
        cin>>a[i],cnt+=a[i]==0;
        if(a[i]) va.emplace_back(a[i]);
    }
    sort(va.begin(),va.end()),vm=unique(va.begin(),va.end())-va.begin();
    for(int i=0;i<vm;i++){
        for(int j=1;j<=n;j++){
            int tmp=0;
            for(int k=j;k<=n;k++){
                if(a[k]==va[i]) tmp=1;
                vis[i][j][k]=tmp;
            }
        }
    }
    for(int i=0;i<=n;i++){
        f1[i][0][i]=1;
        for(int j=0;i+j<=n;j++) for(int t=i;t<=min(m,i+j);t++) if(f1[i][j][t]){
            add(f1[i][j+1][t],1ll*f1[i][j][t]*t);
            add(f1[i][j+1][t+1],1ll*f1[i][j][t]*(m-t));
        }
    }
    for(int i=0;i<=n;i++){
        f2[i][0][i]=1;
        for(int j=0;i+j<=n;j++) for(int t=i;t<=min(m-1,i+j);t++) if(f2[i][j][t]){
            add(f2[i][j+1][t],1ll*f2[i][j][t]*t);
            add(f2[i][j+1][t+1],1ll*f2[i][j][t]*(m-1-t));
        }
    }
    for(int i=1;i<=n;i++){
        set<int>st;
        int cnt=0;
        for(int j=i;j<=n;j++){
            if(a[j]) st.insert(a[j]);
            else cnt++;
            c1[i][j]=st.size(),c0[i][j]=cnt;
            tag[i][j]=c1[i][j]>c1[i][j-1];
        }
    }
    ll res=0;
    for(int i=1;i<=n/k;i++) res=(res+solve1::solve(i)+solve2::solve(i))%mod;
    res=(res-1ll*(n/k)*ksm(m,cnt)%mod+mod*2)%mod;
    cout<<res<<"\n";
    return 0;
}