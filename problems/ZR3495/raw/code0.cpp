#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,s,t,head[200005],tot=1,de[200005],_head[200005];
struct EDGE{ll nex,to,f;}e[1000005];
void ADD(ll u,ll v,ll f){e[++tot].nex=head[u],e[tot].to=v,e[tot].f=f,head[u]=tot;}
void add(ll u,ll v,ll f){ADD(u,v,f),ADD(v,u,0);cerr<<u<<" "<<v<<" "<<f<<"\n";}
queue<ll>q;
bool bfs(){
    while(!q.empty()) q.pop();
    for(ll i=1;i<=n;i++) de[i]=0,_head[i]=head[i];
    de[s]=1,q.push(s);
    while(!q.empty()){
        ll u=q.front();q.pop();
        for(ll i=head[u];i;i=e[i].nex){
            ll v=e[i].to,f=e[i].f;
            if(de[v]||!f) continue;
            de[v]=de[u]+1,q.push(v);
            if(v==t) return 1;
        } 
    }
    return 0;
}
ll dfs(ll u,ll now){
    ll sum=0;
    if(u==t) return now;
    for(ll i=_head[u];i&&now;i=e[i].nex){
        _head[u]=i;
        ll v=e[i].to,f=e[i].f;
        if(de[v]!=de[u]+1||!f) continue;
        ll tmp=dfs(v,min(f,now));
        if(!tmp) de[v]=0;
        sum+=tmp,now-=tmp,e[i].f-=tmp,e[i^1].f+=tmp;
    }
    return sum;
}
ll dinic(){
    ll ans=0;
    while(bfs()) ans+=dfs(s,3e9);
    return ans;
}
int nn,m,k;
void solve(){
    cin>>nn>>m>>k,s=nn+nn+1,t=n=s+1;
    for(int i=1;i<=n;i++) head[i]=0;
    tot=1;
    for(int i=1,u,v;i<=m;i++) cin>>u>>v,add(u,v+nn,1);
    int st=tot+1;
    for(int i=1;i<=nn;i++) add(s,i,k),add(i+nn,t,k);
    int tmp=dinic();
    if(tmp!=nn*k){cout<<"annihilation\n";return;}
    cout<<k<<"\n";
    for(int i=2;i<=m*2;i+=2){
        if(e[i].f) e[i].f=0;
        else e[i].f=1,e[i^1].f=0;
    }
    for(int i=st;i<=tot;i+=2) e[i].f=1,e[i+1].f=0;
    dinic();
    for(int i=3;i<=m*2+1;i+=2) if(e[i].f) cout<<i/2<<" ";cout<<"\n";
    if(k==2) for(int i=2;i<=m*2;i+=2) if(e[i].f) cout<<i/2<<" ";cout<<"\n";
}
int main(){
    freopen("loop.in","r",stdin);
    freopen("loop.out","w",stdout);
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int Ca;cin>>Ca;while(Ca--)solve();
    return 0;
}