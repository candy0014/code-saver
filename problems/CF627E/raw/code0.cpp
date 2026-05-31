#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m,h,k;
vector<int>p[3005];
int mi[3005],ma[3005],pre[3005],nex[3005],pos[3005],tot;
ll now;
set<int>st;
int g[15];
void insert(int x){
	int p=++tot;
	auto it=st.upper_bound(x);
	int ls=ma[*prev(it)],rs=mi[*it];
	pre[tot]=ls,nex[tot]=rs,pos[tot]=x,nex[ls]=tot,pre[rs]=tot;
	if(st.find(x)!=st.end()) ma[x]=tot;
	else st.insert(x),mi[x]=ma[x]=tot;
	for(int i=0,u=p;i<=k;i++,u=nex[u]) g[i]=pos[u];
	for(int i=k,u=p;i>=1;i--,u=pre[u]) now-=1ll*(pos[u]-pos[pre[u]])*(g[i]-g[i-1]);
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>h>>k;
	for(int i=1,x,y;i<=h;i++) cin>>x>>y,p[x].emplace_back(y);
	ll res=0;
	for(int l=1;l<=n;l++){
		now=1ll*m*m,st.clear(),st.insert(0),st.insert(m+1);
		pos[1]=0,pos[2]=m+1,nex[1]=2,pre[1]=1,pre[2]=1,nex[2]=2,mi[0]=ma[0]=1,mi[m+1]=ma[m+1]=2,tot=2;
		for(int r=l;r<=n;r++){
			for(auto y:p[r]) insert(y);
			res+=now-1ll*m*(m-1)/2;
		}
	}
	cout<<1ll*n*(n+1)/2*m*(m+1)/2-res<<"\n";
	return 0;
}