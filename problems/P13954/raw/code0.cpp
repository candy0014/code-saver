#include <bits/stdc++.h>
using namespace std;
priority_queue<int>dp[100005];
int n;
string str;
vector<int>e[100005];
int dp0[100005],g[100005];
void solve(){
    cin>>n>>str,str=" "+str;
    for(int i=1;i<=n;i++) e[i].clear();
    for(int i=2,u;i<=n;i++) cin>>u,e[u].emplace_back(i);
    for(int u=n;u>=1;u--){
        dp0[u]=g[u]=0;
        while(!dp[u].empty()) dp[u].pop();
        for(auto v:e[u]){
            dp0[u]+=dp0[v];
            if(dp[u].empty()) swap(dp[v],dp[u]),g[u]=g[v];
            else{
                priority_queue<int>q;
                g[u]=0;
                while(!dp[u].empty()&&!dp[v].empty()){
                    int t=-dp[u].top()-dp[v].top();dp[u].pop(),dp[v].pop();
                    g[u]-=min(t,0),q.push(-t);
                }
                swap(dp[u],q);
            }
        }
        if(str[u]=='1') dp[u].push(1),g[u]++,dp0[u]++;
        else dp[u].push(-1);
    }
    for(int i=1;i<=n;i++) cout<<dp0[i]-g[i]<<" \n"[i==n];
}
int main(){
    // freopen("test.in","r",stdin);
    // freopen("test.out","w",stdout);
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int Ca;cin>>Ca;while(Ca--)solve();
    return 0;
}