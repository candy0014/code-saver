#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 LL;
const ll mod=998244353;
int n;
struct EDGE{int u,v;ll w;}e[250005];
int fa[1000005],fat[1000005],sz[1000005],son[1000005][2];
int Find(int u){return fa[u]==u?u:(fa[u]=Find(fa[u]));}
LL val[1000005];
int id[1000005];
void dfs(int u,LL c=0){
    val[u]=sz[u]*c;
    if(u>n) for(int i:{0,1}) dfs(son[u][i],c+(sz[u]-sz[son[u][i]])*e[u-n].w);
}
void solve(){
    cin>>n;
    for(int i=1;i<n;i++) cin>>e[i].u>>e[i].v>>e[i].w;
    sort(e+1,e+n,[&](EDGE u,EDGE v){return u.w>v.w;});
    for(int i=1;i<=n*2;i++) fa[i]=i,sz[i]=1;
    for(int i=1;i<n;i++){
        int u=Find(e[i].u),v=Find(e[i].v);
        fa[u]=fa[v]=fat[u]=fat[v]=i+n,son[i+n][0]=u,son[i+n][1]=v,sz[i+n]=sz[u]+sz[v];
    }
    dfs(n*2-1);
    int m=n*2-1;
    for(int i=1;i<m;i++) id[i]=i;
    sort(id+1,id+m,[&](int u,int v){return val[u]>val[v];});
    for(int i=1;i<=m*2;i++) fa[i]=i,sz[i]=(i<=n);
    for(int i=1;i<m;i++){
        int u=Find(id[i]),v=Find(fat[id[i]]);
        fa[u]=fa[v]=i+m,son[i+m][0]=u,son[i+m][1]=v,sz[i+m]=sz[u]+sz[v];
    }
    LL res=0;
    for(int i=m+1;i<=m*2-1;i++) res=(res+(LL)sz[son[i][0]]*sz[son[i][1]]*val[id[i-m]])%mod;
    cout<<(ll)res<<"\n";
}
int main(){
    // freopen("test.in","r",stdin);
    // freopen("test.out","w",stdout);
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int Ca;cin>>Ca;while(Ca--)solve();
    return 0;
}