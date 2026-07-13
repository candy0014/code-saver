#include <bits/stdc++.h>
using namespace std;
int n,a[1000005];
struct BIT{
    int mi[1000005];
    void init(){for(int i=1;i<=n;i++) mi[i]=1e9;}
    void add(int x,int k){while(x<=n)mi[x]=min(mi[x],k),x+=(x&(-x));}
    int query(int x){int t=1e9;while(x)t=min(t,mi[x]),x-=(x&(-x));return t;}
}b;
int pre[1000005],suf[1000005],res[1000005];
void solve(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    b.init(),suf[n+1]=0;
    for(int i=1;i<=n;i++) b.add(a[i],pre[i-1]+1),pre[i]=b.query(a[i]);
    b.init();
    for(int i=n;i>=1;i--) b.add(n-a[i]+1,suf[i+1]+1),suf[i]=b.query(n-a[i]+1);
    for(int i=1;i<=n;i++) res[a[i]]=pre[i]+suf[i]-2;
    for(int i=1;i<=n;i++) cout<<res[i]<<" \n"[i==n];
}
int main(){
    // freopen("test.in","r",stdin);
    // freopen("test.out","w",stdout);
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int Ca;cin>>Ca;while(Ca--)solve();
    return 0;
}