#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,L[500005],_R[500005],R[500005];
ll k;
pair<int,int>t[1000005];
int cl[1000005],cr[1000005];
ll sl[1000005],sr[1000005];
bool check(int x){
    for(int i=1;i<=n;i++) R[i]=_R[i]-x;
    int u=1,v=1,tot=0;
    while(u<=n||v<=n){
        if(v>n||(u<=n&&L[u]<=R[v])) t[++tot]=make_pair(L[u],0),u++;
        else t[++tot]=make_pair(R[v],1),v++;
    }
    for(int i=1;i<=tot;i++){
        cl[i]=cl[i-1],sl[i]=sl[i-1];
        if(t[i].second) cl[i]++,sl[i]+=t[i].first;
    }
    for(int i=tot;i>=1;i--){
        cr[i]=cr[i+1],sr[i]=sr[i+1];
        if(!t[i].second) cr[i]++,sr[i]+=t[i].first;
    }
    ll mi=1e18+5;
    for(int i=1;i<=tot;i++) mi=min(mi,1ll*t[i].first*cl[i]-sl[i]+sr[i]-1ll*t[i].first*cr[i]);
    return mi<=k;
}
int plan_vacation(int N,vector<int>L_,vector<int>R_,ll K){
    n=N,k=K;
    int l=0,r=1e9,ans=-1,mid;
    for(int i=1;i<=n;i++) L[i]=L_[i-1],_R[i]=R_[i-1],r=min(r,_R[i]-L[i]);
    sort(L+1,L+n+1),sort(_R+1,_R+n+1);
    while(l<=r){
        mid=(l+r)>>1;
        if(check(mid)) l=mid+1,ans=mid;
        else r=mid-1;
    }
    return ans+1;
}