#include <bits/stdc++.h>
using namespace std;
int n,x[100005],y[100005],tag[100005],vis[100005];
map<pair<int,int>,int>mp;
map<int,int>c1,c2;
bool check(int x,int y){
	return mp.count(make_pair(x,y))&&mp.count(make_pair(x-1,y))&&mp.count(make_pair(x+1,y))&&mp.count(make_pair(x,y-1))&&mp.count(make_pair(x,y+1));
}
int num=0;
int xl,xr,yl,yr;
void solve(){
	num++;
	cin>>n,mp.clear(),c1.clear(),c2.clear();
	for(int i=0;i<=n;i++) cin>>x[i]>>y[i],mp[make_pair(x[i],y[i])]=i,tag[i]=vis[i]=0,c1[x[i]]++,c2[y[i]]++;
	int tmp=1,dir[4][2]={1,0,0,1,-1,0,0,-1},cnt=0;
	xl=xr=x[0],yl=yr=y[0];
	for(int i=0;i<4;i++) if(check(x[0]+dir[i][0],y[0]+dir[i][1])) xl=xr=x[0]+dir[i][0],yl=yr=y[0]+dir[i][1],cnt|=1<<i;
	if((cnt&5)==5||(cnt&10)==10){cout<<"YES\n";return;}
	if(xl!=x[0]||yl!=y[0]){
		if(check(xl-1,yl+1)||check(xl+1,yl-1)){
			while(check(xl-1,yr+1)) xl--,yr++;
			while(check(xr+1,yl-1)) xr++,yl--;
		}
		else{
			while(check(xl-1,yl-1)) xl--,yl--;
			while(check(xr+1,yr+1)) xr++,yr++;
		}
		xl--,yl--,xr++,yr++;
	}
	for(int i=xl;i<=xr;i++) if(c1[i]!=(i!=xl&&i!=xr)*2+1){cout<<"YES\n";return;}
	for(int i=yl;i<=yr;i++) if(c2[i]!=(i!=yl&&i!=yr)*2+1){cout<<"YES\n";return;}
	cout<<"NO\n";
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}