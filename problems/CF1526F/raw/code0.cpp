#include <bits/stdc++.h>
using namespace std;
int n;
int pp[25]={0,9,10,19,7,16,18,11,14,15,6,20,8,17,4,5,3,12,2,13,1};
int ask(int a,int b,int c){
	cout<<"? "<<a<<" "<<b<<" "<<c<<endl;
	cin>>a;
	// int x=abs(pp[a]-pp[b]),y=abs(pp[a]-pp[c]),z=abs(pp[b]-pp[c]);
	// a=x+y+z-min({x,y,z})-max({x,y,z});
	// cout<<a<<"\n";
	return a;
}
mt19937 rd(time(0));
int id[100005],g[100005],res[100005];
bool check(int ca,int t,int u,int v){
	int tot=0;
	for(int i=1;i<=n;i++) if(i!=u&&i!=v) id[++tot]=i;
	shuffle(id+1,id+tot+1,rd);
	ca=min(ca,tot);
	int cnt=0;
	for(int i=1;i<=ca;i++) cnt+=(ask(u,v,id[i])==t);
	return cnt>=3;
}
void solve(){
	cin>>n;
	int bu=0,bv=0,len=0;
	int ca=420;
	while(1){
		int u=rd()%n+1,v=rd()%n+1,w=rd()%n+1;
		while(u==v) v=rd()%n+1;
		while(w==u||w==v) w=rd()%n+1;
		int t=ask(u,v,w);ca--;
		if(t%2==0&&t*2>=n&&t*4<=n*3){
			len=t;
			if(check(ca/2,t,u,v)) bu=u,bv=v;
			else if(check(ca/2,t,u,w)) bu=u,bv=w;
			else bu=v,bv=w;
			break;
		}
	}
	for(int i=1;i<=n;i++) res[i]=1e9;
	res[bu]=0,res[bv]=len;
	int rt=0,rt2=0;
	for(int i=1;i<=n;i++) if(res[i]==1e9){
		g[i]=ask(i,bu,bv);
		if(g[i]==len/2) res[i]=len/2,rt=i;
	}
	for(int i=1;i<=n;i++) if(res[i]==1e9&&g[i]<len){
		if(ask(bu,i,rt)==len/2) res[i]=g[i];
		else res[i]=len-g[i];
		if(res[i]==1) rt2=i;
	}
	for(int i=1;i<=n;i++) if(res[i]==1e9){
		int t=ask(bu,i,rt2);
		if(t>=len) res[i]=t+1;
		else res[i]=-t;
	}
	if(res[1]>res[2]) for(int i=1;i<=n;i++) res[i]=-res[i];
	int mi=1e9;
	for(int i=1;i<=n;i++) mi=min(mi,res[i]);
	for(int i=1;i<=n;i++) res[i]-=mi-1;
	cout<<"!";
	for(int i=1;i<=n;i++) cout<<" "<<res[i];
	cout<<endl;
	int sb;cin>>sb;
}
int main(){
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}