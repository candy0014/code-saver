#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
int ksm(int u,int v=mod-2){int t=1;while(v)t=1ll*t*((v&1)?u:1)%mod,u=1ll*u*u%mod,v>>=1;return t;}
int jie[10000005],inv[10000005],iv[10000005];
void init(int n=10000000){
    jie[0]=1;
    for(int i=1;i<=n;i++) jie[i]=1ll*jie[i-1]*i%mod;
    inv[n]=ksm(jie[n]);
    for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
    for(int i=1;i<=n;i++) iv[i]=1ll*inv[i]*jie[i-1]%mod;
}
int C(int u,int v){
    if(v<0||u<v) return 0;
    return 1ll*jie[u]*inv[v]%mod*inv[u-v]%mod;
}
void work(int s,int c1[],int c2[],int c12[],int c0[]){
    for(int n=1;n<=s;n++){
        c0[n]=C(s-1,n-1);
        c1[n]=1ll*s*iv[n]%mod*C(s-1,n-1)%mod;
        c2[n]=((1ll*(s-n+1)*(s-n+1)%mod*C(s-1,n-1)+1ll*(n-1)*(2*n-2*s-1)%mod*C(s-1,n)+1ll*n*(n-1)%mod*C(s-1,n+1))%mod+mod)%mod;
        c12[n]=(1ll*s*s%mod*C(s-1,n-1)-1ll*c2[n]*n%mod+mod)%mod*iv[n]%mod*iv[n-1]%mod;
        c2[n]=1ll*(c2[n]+c1[n])*iv[2]%mod;
    }
}
int ID,n,m;
int c1[5000005],c2[5000005],c12[5000005],c0[5000005];
int d1[5000005],d2[5000005],d12[5000005],d0[5000005];
int res1_a[5000005],res1_b[5000005];
int res2_a[5000005],res2_b[5000005];
int res3_a[5000005],res3_b[5000005];
int res4_a[5000005],res4_b[5000005];
int solve(int k){
    if(k==1){
        return 1ll*C(n+m-2,n-1)*(n+m-1)%mod;
    }
    if(k&1){
        int t=min(n,m)-1;
        ll res=0;
        if(t>=(k-3)/2){
            res+=(res1_a[t]-1ll*res1_b[t]*((k-3)/2)%mod)-(res1_a[(k-3)/2]-1ll*res1_b[(k-3)/2]*((k-3)/2)%mod);
        }
        if(t>=(k-1)/2){
            res+=(res2_a[t]-1ll*res2_b[t]*((k-1)/2)%mod)-(res2_a[(k-1)/2]-1ll*res2_b[(k-1)/2]*((k-1)/2)%mod);
        }
        res=(res%mod+mod)%mod;
        return res;
    }
    if(k==2){
        ll res=0;
        if(n==1) return 1ll*m*(m-1)/2%mod;
        if(m==1) return 1ll*n*(n-1)/2%mod;
        for(int i=1;i<n;i++) res+=1ll*c2[i]*i%mod*(1ll*d0[i-1]+d0[i]*2+d0[i+1])%mod;
        for(int i=1;i<m;i++) res+=1ll*d2[i]*i%mod*(1ll*c0[i-1]+c0[i]*2+c0[i+1])%mod;
        return res%mod;
    }
    ll res=0;
    int t=max(n,m)-1;
    res+=(res3_a[t]-1ll*res3_b[t]*((k-2)/2)%mod)-(res3_a[(k-2)/2]-1ll*res3_b[(k-2)/2]*((k-2)/2)%mod);
    res=(res%mod+mod)%mod;
    return res;
}
string str;
int main(){
    freopen("count.in","r",stdin);
    freopen("count.out","w",stdout);
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>ID>>n>>m>>str,str=" "+str;
    init(),work(n-1,c1,c2,c12,c0),work(m-1,d1,d2,d12,d0);
    int t=min(n,m)-1;
    for(int i=1;i<=t;i++){
        int tmp=2ll*(1ll*c1[i]*d1[i]%mod+1ll*c1[i]*d1[i+1]%mod+1ll*c1[i+1]*d1[i]%mod)%mod;
        res1_a[i]=(res1_a[i-1]+1ll*tmp*i)%mod,res1_b[i]=(res1_b[i-1]+tmp)%mod;
        tmp=2ll*c1[i]*d1[i]%mod;
        res2_a[i]=(res2_a[i-1]+1ll*tmp*i)%mod,res2_b[i]=(res2_b[i-1]+tmp)%mod;
    }
    t=max(n,m)-1;
    for(int i=1;i<=t;i++){
        int tmp=(1ll*c12[i]*(1ll*d0[i-1]+d0[i]*2+d0[i+1])+1ll*d12[i]*(1ll*c0[i-1]+c0[i]*2+c0[i+1]))%mod;
        res3_a[i]=(res3_a[i-1]+1ll*tmp*i)%mod,res3_b[i]=(res3_b[i-1]+tmp)%mod;
    }
    ll res=0;
    for(int i=1;i<=n+m-1;i++) if(str[i]=='1') res+=solve(i)^i;
    cout<<res<<"\n";
    return 0;
}