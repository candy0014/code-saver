#include <bits/stdc++.h>
#include <cassert>
using namespace std;
int n,ca,OP;
uint64_t sd;
uint64_t rnd() {
    sd ^= sd << 13, sd ^= sd >> 7;
    return sd ^= sd << 17;
}
int co[1000005],fat[1000005],c;
int head[1000005],tot;
struct EDGE{int nex,to;}e[1000005];
void add(int u,int v){e[++tot].nex=head[u],e[tot].to=v,head[u]=tot;}
int L[1000005],R[1000005],num,id[1000005];
int to[1000005][20];
vector<int>p[10005];
int lb[1000005],d[1000005];
void dfs1(int u) {
  int p = fat[u], q = lb[p], r = lb[q];
  d[u] = d[p] + 1;
  lb[u] = d[p] - d[q] != d[q] - d[r] ? p : r;
  for(int i=head[u];i;i=e[i].nex) dfs1(e[i].to);
}
int LCA(int u, int v) {
  if (d[u] < d[v]) swap(u, v);
  while (d[u] > d[v])
    if (d[lb[u]] < d[v])
      u = fat[u];
    else
      u = lb[u];
  while (u != v)
    if (lb[u] == lb[v])
      u = fat[u], v = fat[v];
    else
      u = lb[u], v = lb[v];
  return u;
}
void dfs(int u){
    if(p[co[u]].size()) to[u][0]=p[co[u]].back();
    p[co[u]].emplace_back(u);
    L[u]=++num,id[num]=u;
    for(int i=head[u];i;i=e[i].nex) dfs(e[i].to);
    R[u]=num,p[co[u]].pop_back();
}
int _get(int u,int v){
    if(L[u]<=L[v]&&R[v]<=R[u]) return u;
    for(int i=19;i>=0;i--) if(to[u][i]&&!(L[to[u][i]]<=L[v]&&R[v]<=R[to[u][i]])) u=to[u][i];
    u=to[u][0];
    return u;
}
int get(int u,int c){
    int t=lower_bound(p[c].begin(),p[c].end(),L[u])-p[c].begin();
    int ma=0,res=0;
    for(int i=t-1;i<=t+1;i++) if(0<=i&&i<(int)p[c].size()){
        int v=_get(id[p[c][i]],u);
        if(L[v]>ma) ma=L[v],res=v;
    }
    return res;
}
int query(int u,int v){
    if(L[u]<L[v]) return 0;
    int res=1;
    for(int i=19;i>=0;i--) if(L[to[u][i]]>=L[v]) u=to[u][i],res+=(1<<i);
    return res;
}
int F(int u,int k){
    k--;
    for(int i=0;i<20;i++) if((k>>i)&1) u=to[u][i];
    return u;
}
int main(){
    freopen("show.in","r",stdin);
    freopen("show.out","w",stdout);
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n>>ca>>OP>>sd;
    for(int i=1;i<=n;i++) cin>>co[i],c=max(c,co[i]);
    for(int i=2;i<=n;i++) cin>>fat[i],add(fat[i],i);
    dfs(1),dfs1(1);
    for(int i=1;i<=c;i++) p[i].clear();
    for(int i=1;i<=n;i++) p[co[i]].emplace_back(L[i]);
    for(int i=1;i<=n;i++) for(int j=1;j<20;j++) to[i][j]=to[to[i][j-1]][j-1];
    for(int i=1;i<=c;i++) sort(p[i].begin(),p[i].end());
    int lastans=0;
    while(ca--){
        int u,v,c;
        if(OP) u=(rnd()^lastans)%n+1,v=(rnd()^lastans)%n+1,c=co[(rnd()^lastans)%n+1];
        else u=rnd()%n+1,v=rnd()%n+1,c=co[rnd()%n+1];
        int lca=LCA(u,v);
        u=get(u,c),v=get(v,c);
        int ls=query(u,lca),rs=query(v,lca),al=ls+rs-(ls&&rs&&co[lca]==c);
        if(!ls&&!rs){cout<<"-1\n";continue;}
        if(ls>=rs) cout<<(lastans=F(u,(al+1)/2))<<"\n";
        else cout<<(lastans=F(v,al/2+1))<<"\n";
    }
    return 0;
}