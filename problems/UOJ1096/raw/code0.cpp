#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
int ID,n,ca,_ca;
ull x,seed,pw[200005],w[200005];
mt19937 rng;
ull rnd(ull L, ull R){
    ull range = (ull)R - L + 1;
    ull bucket = (1ULL << 32) / range;
    ull limit = bucket * range;
    ull v;
    do {
      v = rng();
    } while ((ull)v >= limit);
    return L + (ull)((ull)v / bucket);
};
vector<pair<int,int> >as[200005];
struct node{
    int cnt;
    ull res;
    node(ull pos=0){
        if(pos) cnt=1,res=pos;
        else cnt=res=0;
    }
    node operator+(const node &rs)const{
        node ress;
        ress.cnt=cnt+rs.cnt,ress.res=res+rs.res*pw[cnt];
        return ress;
    }
}res[2000005];
struct TREE{
    node sum[800005];
    void init(){for(int i=1;i<=n*4;i++) sum[i]=node();}
    void change(int p,int l,int r,int x){
        if(l==r){sum[p]=node(w[x]);return;}
        int mid=(l+r)>>1;
        if(x<=mid) change(p*2,l,mid,x);
        else change(p*2+1,mid+1,r,x);
        sum[p]=sum[p*2]+sum[p*2+1];
    }
    node query(int p,int l,int r,int L,int R){
        if(L<=l&&r<=R) return sum[p];
        int mid=(l+r)>>1;
        if(R<=mid) return query(p*2,l,mid,L,R);
        if(L>mid) return query(p*2+1,mid+1,r,L,R);
        return query(p*2,l,mid,L,R)+query(p*2+1,mid+1,r,L,R);
    }
}tr;
string str,_str;
int s[400005],sa[400005],cnt[400005],g[400005],V=128;
int p[400005];
int main(){
    // freopen("test.in","r",stdin);
    // freopen("test.out","w",stdout);
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>ID>>n>>x>>ca>>_ca>>seed>>str,rng.seed(seed);
    _str=str,reverse(_str.begin(),_str.end()),str=" "+str+_str+" ";
    for(int i=1;i<=n+n;i++) s[i]=str[i],cnt[s[i]]++;
    for(int i=1;i<=V;i++) cnt[i]+=cnt[i-1];
    for(int i=n+n;i>=1;i--) sa[cnt[s[i]]--]=i;
    for(int i=1;i<=n;i++) cin>>w[i],w[i]*=x;
    pw[0]=1;
    for(int i=1;i<=n;i++) pw[i]=pw[i-1]*x;
    for(int i=1;i<=ca;i++){
        int l,r;
        if(i<=_ca) cin>>l>>r;
        else{
            l=rnd(1,n),r=rnd(1,n);
            if(l>r) swap(l,r);
        }
        as[l].emplace_back(r,i);
    }
    for(int i=1,len=1;i<20&&len<=n+n;i++,len<<=1){
        int tot=0;
        for(int j=n+n-len+1;j<=n+n;j++) g[++tot]=j;
        for(int j=1;j<=n+n;j++) if(sa[j]>len) g[++tot]=sa[j]-len;
        for(int j=1;j<=V;j++) cnt[j]=0;
        for(int j=1;j<=n+n;j++) cnt[s[j]]++;
        for(int j=1;j<=V;j++) cnt[j]+=cnt[j-1];
        for(int j=n+n;j>=1;j--) sa[cnt[s[g[j]]]--]=g[j];
        V=0;
        for(int j=1;j<=n+n;j++){
            if(j==1||s[sa[j]]!=s[sa[j-1]]||(s[sa[j]]==s[sa[j-1]]&&s[sa[j]+len]!=s[sa[j-1]+len])) V++;
            g[sa[j]]=V;
        }
        for(int j=1;j<=n+n;j++) s[j]=g[j];
        tr.init();
        tot=0;
        for(int j=n+n;j>=1;j--) if(sa[j]-(sa[j]>n)*n+(1<<i)-1<=n) p[++tot]=sa[j];
        for(int j=1;j<=tot;j++){
            int k=j;
            while(k<tot&&s[p[j]]==s[p[k+1]]) k++;
            for(int t=j;t<=k;t++) if(p[t]<=n){
                node tmp;
                int flag=0;
                for(auto [r,id]:as[p[t]]){
                    r=min(r,p[t]+(1<<(i+1))-2);
                    if(p[t]+(1<<i)-1>r) continue;
                    node h;
                    if(r==p[t]+(1<<(i+1))-2&&flag) h=tmp;
                    else h=tr.query(1,1,n,p[t]+(1<<i)-1,r);
                    if(r==p[t]+(1<<(i+1))-2) tmp=h,flag=1;
                    res[id]=res[id]+h;
                }
            }
            for(int t=j;t<=k;t++) if(p[t]>n) tr.change(1,1,n,n+n+1-p[t]);
            j=k;
        }
    }
    ull ress=0;
    for(ull i=1;i<=ca;i++) ress^=res[i].res+i*i*i;
    cout<<ress<<"\n";
    cerr<<clock()*1.0/CLOCKS_PER_SEC<<"\n";
    return 0;
}