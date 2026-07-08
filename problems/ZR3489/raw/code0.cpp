#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
multiset<int>q;
ll solve(int n,int a[],int b[]){
    // for(int i=1;i<=n;i++) cout<<a[i]<<" \n"[i==n];
    // for(int i=1;i<=n;i++) cout<<b[i]<<" \n"[i==n];
    q.clear();
    ll Lp=-2e9,Lk=0,Ls=0;
    for(int i=1;i<=n;i++){
        if(i>1){
            if(b[i-1]==1){
                while(q.size()>Lk) q.erase(prev(q.end()));
            }
            else{
                ll la=Lp;
                while(Lk){
                    int t=*q.begin();
                    Ls-=(t-la)*Lk,la=t;
                    q.erase(q.begin()),Lk--;
                }
            }
        }
        q.insert(a[i]),q.insert(a[i]),Lk++,Ls+=a[i]-Lp;
    }
    ll la=Lp;
    while(Lk){
        int t=*q.begin();
        Ls-=(t-la)*Lk,la=t;
        q.erase(q.begin()),Lk--;
    }
    // cout<<Ls<<"\n";
    return Ls;
}
int ID,n,A[1000005],B[1000005],a[500005],b[500005];
int main(){
    freopen("array.in","r",stdin);
    freopen("array.out","w",stdout);
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>ID>>n;
    int flag=0;
    for(int i=1;i<=n;i++) cin>>A[i],A[i+n]=A[i];
    for(int i=1;i<=n;i++) cin>>B[i],flag|=B[i],B[i+n]=B[i];
    A[1+n+n]=A[1],B[1+n+n]=B[1],A[0]=A[n],B[0]=B[n];
    if(flag!=3){
        sort(A+1,A+n+1);
        ll res=0;
        for(int i=1;i<=n;i++) res+=abs(A[i]-A[(n+1)/2]);
        cout<<res<<"\n";
        return 0;
    }
    int pos=0;
    for(int i=1;i<=n;i++) if(B[i]==2&&B[i+1]==1) pos=i+1;
    for(int i=1;i<=n;i++) a[i]=A[pos+i],b[i]=B[pos+i];
    ll res1=solve(n,a,b);
    pos+=n;
    for(int i=1;i<=n;i++) a[i]=A[pos-i],b[i]=3-B[pos-i-1];
    ll res2=solve(n,a,b);
    cout<<max(res1,res2)<<"\n";
    return 0;
}