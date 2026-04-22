#include <bits/stdc++.h>
using namespace std;
int V=2500002;
int n,a[5005],L[5005][5005],id[25000005],dp[5005][5005];
struct TREE{
    int ma[20005],tag[20005];
    void build(int p,int l,int r,int k){
        tag[p]=0;
        if(l==r){ma[p]=dp[l][k];return;}
        int mid=(l+r)>>1;build(p*2,l,mid,k),build(p*2+1,mid+1,r,k),ma[p]=max(ma[p*2],ma[p*2+1]);
    }
    void pushdown(int p){
        ma[p*2]+=tag[p],ma[p*2+1]+=tag[p],tag[p*2]+=tag[p],tag[p*2+1]+=tag[p],tag[p]=0;
    }
    void add(int p,int l,int r,int L,int R){
        if(r<L||l>R||L>R) return;
        if(L<=l&&r<=R){ma[p]++,tag[p]++;return;}
        int mid=(l+r)>>1;pushdown(p),add(p*2,l,mid,L,R),add(p*2+1,mid+1,r,L,R),ma[p]=max(ma[p*2],ma[p*2+1]);
    }
    int get(){
        return ma[1];
    }
}tr;
int main(){
    // freopen("test.in","r",stdin);
    // freopen("test.out","w",stdout);
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i],a[i]+=a[i-1],id[a[i]]=i;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n&&a[j]-a[i]<=a[i];j++){
            L[i][j]=id[2*a[i]-a[j]];
        }
    }
    for(int j=1;j<n;j++){
        for(int i=1;i<=j;i++) dp[j+1][j+1]=max(dp[j+1][j+1],dp[i][j]);
        tr.build(1,1,j,j);
        for(int k=j+2;k<=n;k++){
            if(L[j][k-1]) tr.add(1,1,j,1,L[j][k-1]);
            dp[j+1][k]=tr.get();
        }
    }
    int ma=0;
    for(int i=1;i<=n;i++) ma=max(ma,dp[i][n]);
    cout<<ma<<"\n";
    return 0;
}