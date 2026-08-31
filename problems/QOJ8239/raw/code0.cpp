#include <bits/stdc++.h>
using namespace std;
int ask(int u,int v){cout<<"? "<<u<<" "<<v<<endl;cin>>u;return u;}
int n;
void solve(){
	cin>>n;
	int u=0,v=0,x=0,y=0;
	for(int i=1;i<=n;i+=2){
		int j=i+1;
		if(i==n) j=i-1;
		if(ask(i,j)){u=i,v=j;break;}
	}
	if(!u){cout<<"! 1"<<endl;return;}
	for(int i=1;i<=n;i++) if(i!=u&&i!=v){
		if(!x) x=i;
		else if(!y) y=i;
	}
	int p=ask(u,x),q=ask(v,x);
	if(!p&&!q){cout<<"! 1"<<endl;return;}
	if(!p) swap(u,v);
	if(ask(u,y)) cout<<"! 2"<<endl;
	else cout<<"! 1"<<endl;
}
int main(){
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}