#include <bits/stdc++.h>
using namespace std;
int n,a[2005][2005];
int ask(int x,int y){
	if(!a[x][y]) cout<<"? "<<x<<" "<<y<<endl,cin>>a[x][y];
	return a[x][y];
}
void Max(pair<int,int>&u,pair<int,int>v){if(ask(v.first,v.second)>ask(u.first,u.second))u=v;}
void solve(int x,int xx,int y,int yy,pair<int,int>la){
	if(xx-x>yy-y){
		int mid=(x+xx)>>1;
		for(int i=y;i<=yy;i++) Max(la,{mid,i});
		int _x=la.first,_y=la.second;
		if(la.first==mid) for(int tx:{-1,1}) for(int ty:{-1,0,1}) if(x<=_x+tx&&_x+tx<=xx&&y<=_y+ty&&_y+ty<=yy) Max(la,{_x+tx,_y+ty});
		if(la.first<mid) solve(x,mid-1,y,yy,la);
		else if(la.first>mid) solve(mid+1,xx,y,yy,la);
		else{cout<<"! "<<la.first<<" "<<la.second<<endl;exit(0);}
	}
	else{
		int mid=(y+yy)>>1;
		for(int i=x;i<=xx;i++) Max(la,{i,mid});
		int _x=la.first,_y=la.second;
		if(la.second==mid) for(int tx:{-1,0,1}) for(int ty:{-1,1}) if(x<=_x+tx&&_x+tx<=xx&&y<=_y+ty&&_y+ty<=yy) Max(la,{_x+tx,_y+ty});
		if(la.second<mid) solve(x,xx,y,mid-1,la);
		else if(la.second>mid) solve(x,xx,mid+1,yy,la);
		else{cout<<"! "<<la.first<<" "<<la.second<<endl;exit(0);}
	}
}
int main(){
	cin>>n;
	solve(1,n,1,n,make_pair(1,1));
	return 0;
}