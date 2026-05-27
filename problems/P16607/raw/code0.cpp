#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
const ll mod=998244353;
const ll inf=2e9;
const int N=2e5+5;
const int M=2e5+5;
const int V=2e6+5;
const int len=1800;
int th[500005],ed[500005];
int n,ca,a[500005],pos[500005];
int head[500005],tot;
struct node{int nex,val;}e[10000005];
int headg[500005],totg;
struct T{int nex,val,to,id;}g[8000005];
void add(int u,int v){e[++tot].nex=head[u],e[tot].val=v,head[u]=tot;}
void addg(int u,int v,int to){g[++totg].nex=headg[u],g[totg].val=v,g[totg].to=to,g[totg].id=u,headg[u]=totg;}
struct ASK{int pos,r,x,res;}ask[500005];
void work(int &x,int &cnt,int y){
	if(x<y){
		if(y%x==0) x=y/x,cnt++;
	}
	else{
		if(x%y==0) x/=y,cnt++;
	}
}
int f1[500005],f2[500005],_f1[500005],_f2[500005];
vector<int>as[500005],ass[500005];
int vis[500005];
void solve(int Ca){
	cin>>n>>ca;
	for(int i=1;i<=n;i++){
		th[i]=(i-1)/len+1,ed[th[i]]=i;
		cin>>a[i],pos[a[i]]=i;
	}
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j+=i) add(pos[j],i);
	}
	for(int i=1,l,r,x,cnt;i<=ca;i++){
		cin>>l>>r>>x,cnt=0;
		if(th[l]!=th[r]){
			as[l].emplace_back(i);
		}
		ask[i].pos=l,ask[i].r=r,ask[i].x=x,ask[i].res=cnt;
	}
	for(int i=1;i<=th[n];i++){
		totg=n;
		for(int j=1;j<=n;j++) vis[j]=j;
		for(int j=1;j<=ca;j++) if(ask[j].pos<=ask[j].r&&ask[j].r<=ed[i])
			ass[ask[j].pos].emplace_back(j);
		for(int j=ed[i];j>ed[i-1];j--){
			for(int k=head[j];k;k=e[k].nex) addg(j,e[k].val,vis[a[j]/e[k].val]);
			for(int k=a[j]+a[j];k<=n;k+=a[j]) addg(j,k,vis[k/a[j]]);
			for(int k=headg[j];k;k=g[k].nex) vis[g[k].val]=k;
			for(auto x:ass[j]){
				// cout<<ask[x].res<<"\n";
				int t=vis[ask[x].x];
				while(t>n&&g[t].id<=ask[x].r) g[t].val,ask[x].res++,t=g[t].to;
				ask[x].pos=n+1;
				if(t<=n) ask[x].x=t;
				else ask[x].x=g[t].val;
			}
		}
		// for(int j=1;j<=ca;j++) if(ask[j].pos<=ask[j].r&&ask[j].r<=ed[i]){
		// 	int x=ask[j].x,l=ask[j].pos,r=ask[j].r,cnt=ask[j].res;

		// 	while(l<=r) work(x,cnt,a[l++]);
		// 	ask[j].pos=l,ask[j].x=x,ask[j].res=cnt;
		// }
		for(int j=1;j<=n;j++) f1[j]=j,f2[j]=0;
		for(int j=ed[i];j>ed[i-1];j--){
			for(int k=head[j];k;k=e[k].nex){
				_f1[e[k].val]=f1[a[j]/e[k].val];
				_f2[e[k].val]=f2[a[j]/e[k].val]+1;
			}
			for(int k=a[j]+a[j],kk=2;k<=n;k+=a[j],kk++){
				_f1[k]=f1[kk];
				_f2[k]=f2[kk]+1;
			}
			for(int k=head[j];k;k=e[k].nex){
				f1[e[k].val]=_f1[e[k].val];
				f2[e[k].val]=_f2[e[k].val];
			}
			for(int k=a[j]+a[j],kk=2;k<=n;k+=a[j],kk++){
				f1[k]=_f1[k];
				f2[k]=_f2[k];
			}
			for(auto x:as[j]){
				ask[x].pos=ed[i]+1;
				ask[x].res+=f2[ask[x].x];
				ask[x].x=f1[ask[x].x];
			}
		}
		for(int j=1;j<=ca;j++) if(ask[j].pos<=ask[j].r&&ask[j].pos==ed[i-1]+1){
			ask[j].pos=ed[i]+1;
			ask[j].res+=f2[ask[j].x];
			ask[j].x=f1[ask[j].x];
		}
	}
	for(int i=1;i<=ca;i++) cout<<ask[i].x<<" "<<ask[i].res<<"\n";
}
int main(){
	#ifdef ONLINE_JUDGE
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	#endif
	#ifndef ONLINE_JUDGE
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	
	int Ca=1;
//	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	cerr<<clock()*1.0/CLOCKS_PER_SEC<<"\n";
	return 0;
}