#include <bits/stdc++.h>
using namespace std;
int n,m,a[100005],b[100005];
void solve(){
    cin>>n>>m;
    priority_queue<int>q;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1,u;i<=m;i++) cin>>u,q.push(u);
    sort(a+1,a+n+1);
    int now=n;
    while(!q.empty()){
        int u=q.top();q.pop();
        if(a[now]>=u&&(now==1||q.size())) now--;
        else q.push(max(1,u/2)),q.push((u+1)/2),m++;
        if(m>n){cout<<"No\n";return;}
    }
    cout<<"Yes\n";
}
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int Ca;cin>>Ca;while(Ca--)solve();
    return 0;
}