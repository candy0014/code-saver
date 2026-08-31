#include <bits/stdc++.h>
using namespace std;
int n,res[60005],vis[60005],mi,ma;
int ask(int x,int y,int z){cout<<"? 1 "<<x<<" "<<y<<" "<<z<<endl,cin>>x;return x;}
int ask(int x,int y){cout<<"? 2 "<<x<<" "<<y<<endl;int z;cin>>z;return z==x;}
int main(){
	cin>>n;
	int a,b,c,d,L,R,r1=ask(2,3,4),r2=ask(1,3,4),r3=ask(1,2,4),r4=ask(1,2,3);
	L=min({r1,r2,r3,r4}),R=max({r1,r2,r3,r4});
	if(r1==R&&r2==R) a=1,b=2,c=3,d=4;
	if(r1==R&&r3==R) a=1,b=3,c=2,d=4;
	if(r1==R&&r4==R) a=1,b=4,c=2,d=3;
	if(r2==R&&r3==R) a=2,b=3,c=1,d=4;
	if(r2==R&&r4==R) a=2,b=4,c=1,d=3;
	if(r3==R&&r4==R) a=3,b=4,c=1,d=2;
	for(int i=5;i<=n;i++){
		int x=ask(a,c,i);
		if(x<L) res[b]=L,b=i,L=x;
		else if(x>R) res[d]=R,d=i,R=x;
		else if(L<x&&x<R) res[i]=x;
		else if(x==L) res[a]=L,a=i,L=ask(a,b,c);
		else if(x==R) res[c]=R,c=i,R=ask(b,c,d);
	}
	for(int i=1;i<=n;i++) vis[res[i]]=1;
	for(int i=1;i<=n;i++) if(!vis[i]){
		if(!mi) mi=i;
		ma=i;
	}
	if(ask(a,b)) res[a]=mi,res[b]=L;
	else res[a]=L,res[b]=mi;
	if(ask(c,d)) res[c]=R,res[d]=ma;
	else res[c]=ma,res[d]=R;
	cout<<"!";
	for(int i=1;i<=n;i++) cout<<" "<<res[i];
	cout<<endl;
	return 0;
}