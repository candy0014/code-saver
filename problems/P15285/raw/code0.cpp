#include "towns.h"
#include <bits/stdc++.h>
using namespace std;
int n,dis[115][115];
int ask(int u,int v){
	if(u==v) return 0;
	if(dis[u][v]!=-1) return dis[u][v];
	return dis[u][v]=dis[v][u]=getDistance(u,v);
}
int dt[115],de[115],fa[115],sz[115];
int Find(int u){return fa[u]==u?u:(fa[u]=Find(fa[u]));}
void merge(int u,int v){u=Find(u),v=Find(v);if(u!=v)fa[u]=v,sz[v]+=sz[u];}
bool check(int x){
	int cc=0;
	for(int i=0;i<n;i++) if(dt[i]<x) cc++;
	if(cc>n/2) return 0;
	for(int i=0;i<n;i++) if(dt[i]==x) cc++;
	if(n-cc>n/2) return 0;
	for(int i=0;i<n;i++) fa[i]=i,sz[i]=1;
	int cnt=0,now=-1;
	for(int i=0;i<n;i++) if(dt[i]==x){
		if(cnt==0){now=i,cnt=1;continue;}
		if(ask(i,now)==de[i]+de[now]) cnt--;
		else cnt++,merge(i,now);
	}
	cc=0;
	for(int i=0;i<n;i++) if(dt[i]==x&&fa[i]==i) if(ask(i,now)!=de[i]+de[now]) cc+=sz[i];
	if(cc>n/2) return 0;
	return 1;
}
int hubDistance(int N,int ID){
	n=N;
	memset(dis,-1,sizeof(dis));
	int ma=0,U=0,V=0,mi=1e9;
	for(int i=1;i<n;i++) if(ask(0,i)>ma) ma=ask(0,i),U=i;
	for(int i=0;i<n;i++) if(ask(U,i)>ma) ma=ask(U,i),V=i;
	int len=ask(U,V);
	for(int i=0;i<n;i++) dt[i]=(ask(0,i)+ask(U,i)+ask(0,U))/2-ask(0,i),de[i]=ask(U,i)-dt[i];
	mi=1e9,ma=0;
	for(int i=0;i<n;i++){
		if(i!=U) mi=min(mi,dt[i]);
		if(i!=0) ma=max(ma,dt[i]);
	}
	dt[U]=de[U]=mi,de[0]=ask(0,U)-ma,dt[0]=ma;
	mi=1e9;
	set<int>p;
	// cerr<<U<<" "<<V<<"\n";
	for(int i=0;i<n;i++) mi=min(mi,max(dt[i],len-dt[i]));
	for(int i=0;i<n;i++) if(max(dt[i],len-dt[i])==mi) p.insert(dt[i]);
	for(auto x:p) if(check(x)) return mi;
	return -mi;
}