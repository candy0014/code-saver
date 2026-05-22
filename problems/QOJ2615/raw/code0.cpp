#include <bits/stdc++.h>
using namespace std;
int dis(int x,int y){
	if(x>=0&&y>=0) return max(x,y);
	if(x<=0&&y<=0) return -min(x,y);
	return abs(x)+abs(y);
}
map<int,map<int,int> >mp;
int main(){
	int gp[6][2]={-1,-9,8,-1,9,8,1,9,-8,1,-9,-8};
	int x,y,lax,lay;
	for(int i=0;i<6;i++){
		cin>>x>>y,lax=x,lay=y;
		cout<<gp[i][0]<<" "<<gp[i][1]<<endl,mp[gp[i][0]][gp[i][1]]=1;
	}
	while(cin>>x>>y){
		int dir[12][2]={1,0,0,1,1,1,-1,0,0,-1,-1,-1,1,-1,2,1,1,2,-1,1,-2,-1,-1,-2},flag=0;
		for(int i=0;i<12;i++){
			int tx=x+dir[i][0],ty=y+dir[i][1];
			if(dis(tx,ty)==9&&!mp[tx][ty]){cout<<tx<<" "<<ty<<endl,mp[tx][ty]=1,flag=1;break;}
		}
		if(!flag) cout<<lax<<" "<<lay<<endl;
		lax=x,lay=y;
	}
	return 0;
}