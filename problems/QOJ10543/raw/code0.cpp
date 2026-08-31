#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
vector<int>p[3],nex[3][3];
struct node{int a,b,c,dis;}q[40000005];
const ll mod1=1e10+19,mod2=1e9+7,base1=37,base2=131;
bitset<mod1>b1;
bitset<mod2>b2;
int head,tail;
void update(node u){
	ll x1=((p[0][u.a]*base1*base1+p[1][u.b]*base2+p[2][u.c])%mod1+mod1)%mod1;
	ll x2=((p[0][u.a]*base1+p[1][u.b]*base2+p[2][u.c])%mod2+mod2)%mod2;
	if(b1[x1]&&b2[x2]) return;
	b1[x1]=1,b2[x2]=1,q[++tail]=u;
}
int bfs(){
	head=1,tail=0,update({0,0,0,0});
	while(head<=tail){
		node u=q[head++];
		if(p[0][u.a]==2e9&&p[1][u.b]==2e9&&p[2][u.c]==2e9) return u.dis;
		if(p[2][u.c]>=p[0][u.a]||p[2][u.c]>=p[1][u.b]){
			if(p[0][u.a]<=p[1][u.b]) update({nex[0][0][u.a],max(u.b,nex[0][1][u.a]),u.c,u.dis+1});
			else update({max(u.a,nex[1][0][u.b]),nex[1][1][u.b],u.c,u.dis+1});
		}
		if(p[0][u.a]>=p[1][u.b]||p[0][u.a]>=p[2][u.c]){
			if(p[2][u.c]<=p[1][u.b]) update({u.a,max(u.b,nex[2][1][u.c]),nex[2][2][u.c],u.dis+1});
			else update({u.a,nex[1][1][u.b],max(u.c,nex[1][2][u.b]),u.dis+1});
		}
	}
	return 0;
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1,x,y;i<=n;i++) cin>>x>>y,p[(y>=0)+(y>0)].emplace_back(x);
	for(int x:{0,1,2}) sort(p[x].begin(),p[x].end());
	for(int x:{0,1,2}) for(int y:{0,1,2}) for(int i=0,j=0;i<=p[x].size();i++){
		if(i==p[x].size()){nex[x][y].emplace_back();break;}
		while(j<p[y].size()&&p[y][j]<=p[x][i]+10000) j++;
		nex[x][y].emplace_back(j);
	}
	for(int x:{0,1,2}) p[x].emplace_back(2e9);
	cout<<bfs()<<"\n";
	return 0;
}