#include <bits/stdc++.h>
using namespace std;
int n,m,cnt;
vector<int>e[1000005];
int dfn[500005],low[500005],st[500005],tot,num;
void tarjan(int u){
    dfn[u]=low[u]=++num,st[++tot]=u;
    int flag=0;
    for(auto v:e[u]){
        if(v!=u) flag=1;
        if(!dfn[v]){
            tarjan(v),low[u]=min(low[u],low[v]);
            if(low[v]==dfn[u]){
                ++cnt;
                while(1){
                    int tmp=st[tot--];
                    e[cnt].emplace_back(tmp);
                    if(tmp==v) break;
                }
                e[cnt].emplace_back(u);
            }
        }
        else low[u]=min(low[u],dfn[v]);
    }
    if(!flag){++cnt,e[cnt].push_back({u});return;}
}
int main(){
    // freopen("test.in","r",stdin);
    // freopen("test.out","w",stdout);
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n>>m,cnt=n;
    for(int i=1,u,v;i<=m;i++) cin>>u>>v,e[u].emplace_back(v),e[v].emplace_back(u);
    for(int i=1;i<=n;i++) if(!dfn[i]) tot=0,tarjan(i);
    cout<<cnt-n<<"\n";
    for(int i=n+1;i<=cnt;i++){
        cout<<e[i].size()<<" ";
        for(auto x:e[i]) cout<<x<<" ";cout<<"\n";
    }
    return 0;
}