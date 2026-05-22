#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int lim=250;
int n,nn,m,fa[400005],ch[400005],fail[400005],tag[400005],t[400005];
int fat[400005][20];
int getfa(int u,int k){
    for(int i=19;i>=0;i--) if((k>>i)&1) u=fat[u][i];
    return u;
}
unordered_map<int,int>son[400005],_son[400005];
vector<pair<int,int> >e[400005];
vector<int>ee[400005];
queue<int>q;
mt19937 rd(time(0));
int work(int u,int c){
    if(son[u].count(c)) return son[u][c];
    if(!u) return 0;
    int tmp=work(fail[u],c);
    if(rd()%1==0) son[u][c]=tmp;
    return tmp;
}
int de[400005],len[400005];
int _fail[400005];
vector<int>co[400005];
const ll mod=1e16+2137,base=993244853;
ll has[400005],hat[400005],pw[400005];
unordered_map<ll,bool>mpha;
void getfail(){
    for(int i=1;i<=n;i++) de[i]=1e9;
    for(auto [c,v]:e[0]){
        q.push(v),de[v]=1;
        for(int i=0;i<20;i++) fat[v][i]=0;
    }
    while(!q.empty()){
        int u=q.front();q.pop();
        if(tag[u]&2) len[u]=de[u];
        else len[u]=len[fail[u]];
        for(auto [c,v]:e[u]){
            fat[v][0]=u;
            for(int i=1;i<20;i++) fat[v][i]=fat[fat[v][i-1]][i-1];
            de[v]=de[u]+1;
            if(co[c].size()>lim) fail[v]=work(fail[u],c);
            else{
                int ma=0;fail[v]=0;
                for(auto w:co[c]) if(de[w]<de[v]&&de[w]>ma){
                    int ft=getfa(v,de[w]);
                    if((has[v]-(__int128)has[ft]*pw[de[w]]%mod+mod)%mod==has[w]){
                        ma=de[w],fail[v]=w;
                    }
                }
            }
            q.push(v);
        }
    }
    for(int i=0;i<=n;i++){
        if(tag[i]&1) _fail[i]=i;
        else _fail[i]=_fail[fail[i]];
    }
}
int maxlen[400005];
int L[400005],R[400005],num;
void dfs(int u){
    L[u]=num+1;
    if(u&&(tag[u]&1)) num++;
    for(auto v:ee[u]) dfs(v);
    R[u]=num;
}
vector<pair<pair<int,int>,int> >as[400005];
ll res[400005];
struct TREE{
    ll sum[1600010];
    int mi[1600010],smi[1600010],cnt[1600010],tag[1600010];
    void pushup(int p){
        sum[p]=sum[p*2]+sum[p*2+1];
        if(mi[p*2]<mi[p*2+1]) mi[p]=mi[p*2],smi[p]=min(smi[p*2],mi[p*2+1]),cnt[p]=cnt[p*2];
        else if(mi[p*2]>mi[p*2+1]) mi[p]=mi[p*2+1],smi[p]=min(smi[p*2+1],mi[p*2]),cnt[p]=cnt[p*2+1];
        else mi[p]=mi[p*2],smi[p]=min(smi[p*2],smi[p*2+1]),cnt[p]=cnt[p*2]+cnt[p*2+1];
    }
    void update(int p,int t){
        if(t<=mi[p]) return;
        sum[p]+=1ll*(t-mi[p])*cnt[p],mi[p]=tag[p]=t;
    }
    void pushdown(int p){
        update(p*2,tag[p]),update(p*2+1,tag[p]),tag[p]=-1e9;
    }
    void build(int p,int l,int r){
        tag[p]=-1e9,mi[p]=0,smi[p]=1e9,cnt[p]=r-l+1,sum[p]=0;
        if(l==r) return;
        int mid=(l+r)>>1;build(p*2,l,mid),build(p*2+1,mid+1,r);
    }
    void change(int p,int l,int r,int L,int R,int k){
        if(r<L||l>R||L>R) return;
        if(L<=l&&r<=R&&k<smi[p]){update(p,k);return;}
        int mid=(l+r)>>1;pushdown(p),change(p*2,l,mid,L,R,k),change(p*2+1,mid+1,r,L,R,k),pushup(p);
    }
}tr;
void solve(){
    cin>>n>>m,nn=n;
    if(n==1&&m==1){
        int c;cin>>c>>c>>c;
        cout<<1<<"\n";
        return;
    }
    for(int i=0;i<=n+m;i++) fail[i]=_fail[i]=0,tag[i]=0,son[i].clear(),e[i].clear(),co[i].clear();
    for(int i=1;i<=n;i++) cin>>fa[i];
    mpha.clear();
    pw[0]=1;
    for(int i=1;i<=n+m;i++) pw[i]=(__int128)pw[i-1]*base%mod;
    for(int i=1;i<=n;i++){
        cin>>ch[i];
        son[fa[i]][ch[i]]=i,tag[i]=1,has[i]=((__int128)has[fa[i]]*base+ch[i])%mod,mpha[has[i]]=1;
    }
    for(int i=0;i<=n;i++) _son[i]=son[i];
    int now=0;tag[0]=3;
    for(int i=1;i<=m;i++){
        cin>>t[i];
        hat[i]=((__int128)hat[i-1]*base+t[i])%mod;
        if(!son[now].count(t[i])){
            son[now][t[i]]=++n,fa[n]=now;
            has[n]=((__int128)has[now]*base+t[i])%mod;
        }
        now=son[now][t[i]],tag[now]|=2;
    }
    for(int i=0;i<=n;i++) for(auto x:son[i]) e[i].emplace_back(x),co[x.first].emplace_back(x.second);
    getfail();
    for(int i=0;i<=n;i++) maxlen[i]=0;
    // for(int i=0;i<=n;i++){
    //  fat[i][0]=fa[i];
    //  for(int j=1;j<20;j++) fat[i][j]=fat[fat[i][j-1]][j-1];
    // }
    for(int i=0;i<=nn;i++){
        int l=1,r=m,mid,res=0;
        while(l<=r){
            mid=(l+r)>>1;
            ll tmp=((__int128)has[i]*pw[mid]+hat[mid])%mod;
            if(mpha.count(tmp)) res=mid,l=mid+1;
            else r=mid-1;
        }
        maxlen[i]=res;
    }
    // for(int i=0;i<=nn;i++){
    //  int u=getfa(i,len[i]);
    //  maxlen[u]=max(maxlen[u],len[i]);
    // }
    num=0;
    for(int i=0;i<=n;i++) ee[i].clear();
    for(int i=1;i<=n;i++) ee[fail[i]].emplace_back(i);
    dfs(0);
    for(int i=0;i<=m;i++) as[i].clear();
    for(int i=0;i<=nn;i++) as[maxlen[i]].emplace_back(make_pair(L[i],R[i]),de[i]+maxlen[i]);
    now=0;
    for(int i=1;i<=m;i++){
        now=son[now][t[i]],as[i].emplace_back(make_pair(1,nn),de[_fail[now]]);
    }
    tr.build(1,1,nn);
    for(int i=m;i>=1;i--){
        for(auto [p,x]:as[i]) tr.change(1,1,nn,p.first,p.second,x+(m-i));
        res[i]=tr.sum[1]-1ll*(m-i)*nn;
    }
    for(int i=1;i<=m;i++) cout<<res[i]<<" \n"[i==m];
    cerr<<clock()*1.0/CLOCKS_PER_SEC<<"\n";
}
int main(){
    // freopen("test.in","r",stdin);
    // freopen("test.out","w",stdout);
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int ID,Ca;cin>>/*ID>>*/Ca;while(Ca--)solve();
    return 0;
}