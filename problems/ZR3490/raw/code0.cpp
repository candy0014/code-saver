#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=1e16+2137,base=233;
ll pw[200005];
int n;
vector<int>e[200005];
string val;
int nex[200005][20];
ll ha[200005][20];
struct node{
    int st,ed,len;
    bool operator<(const node &rs)const{
        int t=min(len,rs.len),su=st,sv=rs.st;
        for(int i=19;i>=0;i--) if((1<<i)<=t&&ha[su][i]==ha[sv][i]) t-=(1<<i),su=nex[su][i],sv=nex[sv][i];
        return val[su]>val[sv];
    }
    node operator+(const node &rs)const{
        int rlen=rs.len;
        node res;res.st=st,res.ed=rs.ed,res.len=len+rlen;
        nex[ed][0]=rs.st;
        for(int i=1;i<20;i++){
            int L=max(0,len-(1<<i)),R=min(len-1,len+rlen-(1<<i));
            int now=st;
            for(int j=0;j<20;j++) if((L>>j)&1) now=nex[now][j];
            for(int j=L;j<=R;j++){
                nex[now][i]=nex[nex[now][i-1]][i-1];
                ha[now][i]=((__int128)ha[now][i-1]*pw[1<<(i-1)]+ha[nex[now][i-1]][i-1])%mod;
                now=nex[now][0];
            }
        }
        return res;
    }
};
priority_queue<node>q[200005];
void solve(){
    cin>>n;
    for(int i=1;i<=n;i++) e[i].clear();
    for(int i=1;i<=n;i++) for(int j=0;j<20;j++) nex[i][j]=ha[i][j]=0;
    for(int i=2,u;i<=n;i++) cin>>u,e[u].emplace_back(i);
    cin>>val,val="|"+val;
    for(int i=n;i>=1;i--){
        while(!q[i].empty()) q[i].pop();
        node tmp={i,i,1};ha[i][0]=val[i];
        for(auto v:e[i]){
            if(q[v].size()>q[i].size()) swap(q[v],q[i]);
            while(q[v].size()) q[i].push(q[v].top()),q[v].pop();
        }
        while(q[i].size()){
            node x=q[i].top();
            if(tmp<x) q[i].pop(),tmp=tmp+x;
            else break;
        }
        q[i].push(tmp);
    }
    while(!q[1].empty()){
        node x=q[1].top();q[1].pop();
        int now=x.st,len=x.len;
        for(int i=1;i<=len;i++) cout<<val[now],now=nex[now][0];
    }
    cout<<"\n";
}
int main(){
    // freopen("test.in","r",stdin);
    // freopen("test.out","w",stdout);
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    pw[0]=1;for(int i=1;i<=200000;i++) pw[i]=pw[i-1]*base%mod;
    int ID,Ca;cin>>ID>>Ca;while(Ca--)solve();
    return 0;
}