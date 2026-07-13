#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,ca,a[1000005],b[1000005],c[1000005];
int vis[1000005];
int q[1000005],head,tail;
ll solve(int l,int r){
    if(l>r) return 0;
    head=1,tail=0;
    for(int i=l-1;i<=r+1;i++) c[i]=a[i],vis[i]=0;
    for(int i=max(2,l);i<=min(n-1,r);i++) if(a[i]<a[i-1]&&a[i]<a[i+1]) q[++tail]=i,vis[i]=1;
    while(head<=tail){
        int x=q[head++];
        c[x]=max(c[x-1],c[x+1]);
        if(x+1<=min(n-1,r)&&!vis[x+1]&&c[x+1]<c[x]&&c[x+1]<c[x+2]) q[++tail]=x+1,vis[x+1]=1;
        if(x-1>=max(2,l)&&!vis[x-1]&&c[x-1]<c[x]&&c[x-1]<c[x-2]) q[++tail]=x-1,vis[x-1]=1;
    }
    ll res=0;
    for(int i=l;i<=r;i++) res+=c[i];
    return res;
}
vector<pair<int,ll> >p;
ll sump[1000005],sum[1000005];
int pre[1000005],suf[1000005];
ll workL(int l,int r){
    if(l==r) return a[l];
    if(a[r]>=a[r-1]||a[r]>=a[r+1]) return sum[r]-sum[l-1];
    int x=max(a[r-1],a[r+1]);
    int _l=max(l,pre[r])+1,_r=r;
    int it=upper_bound(a+_l,a+_r+1,x,[&](int x,int y){return x>y;})-a;
    return 1ll*(r-it)*x+max(a[it-1],x)+sum[it-1]-sum[l-1];
}
ll workR(int l,int r){
    if(l==r) return a[l];
    if(a[l]>=a[l-1]||a[l]>=a[l+1]) return sum[r]-sum[l-1];
    int x=max(a[l-1],a[l+1]);
    int _l=l,_r=min(r,suf[l])-1;
    int it=lower_bound(a+_l,a+_r+1,x)-a-1;
    return 1ll*(it-_l)*x+max(a[it+1],x)+sum[r]-sum[it];
}
int main(){
    // freopen("test.in","r",stdin);
    // freopen("test.out","w",stdout);
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n>>ca;
    for(int i=1;i<=n;i++) cin>>a[i],b[i]=a[i],sum[i]=sum[i-1]+a[i];
    for(int i=1;i<=n;i++){
        if(i>=2&&a[i]<a[i-1]) pre[i]=pre[i-1];
        else pre[i]=i;
    }
    for(int i=n;i>=1;i--){
        if(i<n&&a[i]<a[i+1]) suf[i]=suf[i+1];
        else suf[i]=i;
    }
    for(int i=2;i<n;i++) if(a[i]<a[i-1]&&a[i]<a[i+1]) b[i]=max(a[i-1],a[i+1]);
    for(int i=1;i<=n;i++){
        int j=i;
        while(j<n&&b[j+1]!=b[j]) j++;
        ll tmp=solve(i,j);
        p.emplace_back(i,tmp),i=j;
    }
    sump[0]=p[0].second;
    for(int i=1;i<(int)p.size();i++) sump[i]=sump[i-1]+p[i].second;
    while(ca--){
        int l,r;
        cin>>l>>r;
        if(l==r){cout<<a[l]<<"\n";continue;}
        if(l+1==r){cout<<a[l]+a[r]<<"\n";continue;}
        int L=lower_bound(p.begin(),p.end(),make_pair(l+1,0ll))-p.begin();
        int R=(int)(lower_bound(p.begin(),p.end(),make_pair(r+1,0ll))-p.begin())-2;
        if(L==p.size()||p[L].first>r){cout<<sum[r]-sum[l-1]<<"\n";continue;}
        ll res=0;
        if(L<=R){
            res=sump[R];
            if(L) res-=sump[L-1];
        }
        // cout<<l<<" "<<p[L].first-1<<" "<<workL(l,p[L].first-1)<<"\n";
        res+=workL(l,p[L].first-1);
        res+=workR(p[R+1].first,r);
        // res+=solve(l+1,p[L].first-1)+a[l];
        // res+=solve(p[R+1].first,r-1)+a[r];
        cout<<res<<"\n";
    }
    return 0;
}