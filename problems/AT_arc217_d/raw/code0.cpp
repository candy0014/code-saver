#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m,a[500005],mi[500005][20],st[500005],pos[500005],tim[500005],top1,top2;
int getmi(int u,int v){return a[u]<=a[v]?u:v;}
int query(int l,int r){
	int t=__lg(r-l+1);
	return getmi(mi[l][t],mi[r-(1<<t)+1][t]);
}
ll res;
int now;
void work(int t){
	t=min(t,m+1);
	for(int i=now;i<t;i++) res^=1ll*now*i;
	now=t;
}
void solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i],mi[i][0]=i;
	for(int j=1;j<20;j++) for(int i=1;i+(1<<j)-1<=n;i++) mi[i][j]=getmi(mi[i][j-1],mi[i+(1<<(j-1))][j-1]);
	now=0,res=0,top1=0,top2=1;
	pos[1]=query(1,n),tim[1]=a[pos[1]],tim[0]=1e9;
	while(top2&&now<=m){
		int p=pos[top2],t=tim[top2];top2--;
		work(t);
		while(st[top1]>p) top1--;
		if(st[top1]+1!=p){
			int _p=query(st[top1]+1,p-1),_t=now+a[_p]-a[p];
			if(_t<tim[top2]) pos[++top2]=_p,tim[top2]=_t;
		}
		if(p!=n){
			int _p=query(p+1,n),_t=now+a[_p];
			if(_t<tim[top2]) pos[++top2]=_p,tim[top2]=_t;
		}
		st[++top1]=p;
	}
	work(m+1);
	cout<<res<<"\n";
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}