#include "puzzle.h"
#include <bits/stdc++.h>
using namespace std;
mt19937 rd(time(0));
vector<int>t;
int n;
int ask(vector<pair<int,int> >p){
	vector<int>res=t;
	for(auto [x,y]:p) swap(res[x],res[y]);
	return query(res);
}
int h[1005][1005],vis[1005],du[1005];
int work(vector<pair<int,int> >&p,int l,int r,int al=-1){
	if(al==-1){
		vector<pair<int,int> >g;
		for(int i=l;i<=r;i++) g.emplace_back(p[i]);
		al=ask(g);
	}
	if(!al) return 0;
	if(l==r){
		h[p[l].first][p[l].second]=h[p[l].second][p[l].first]=al,du[p[l].first]+=al,du[p[l].second]+=al;
		return al;
	}
	int mid=(l+r)>>1,all=al;
	al-=work(p,l,mid),work(p,mid+1,r,al);
	return all;
}
vector<int>e[1005];
vector<int>b;
void dfs(int u,int fa,int rt){
	b.emplace_back(u);
	for(auto v:e[u]) if(v!=fa&&v!=rt){dfs(v,u,rt);break;}
}
void play(int _n){
	memset(h,0,sizeof(h)),memset(vis,0,sizeof(vis)),memset(du,0,sizeof(du));
	for(int i=0;i<n;i++) e[i].clear();
	if(_n==1){query({0});return;}
	n=_n,t.resize(n);
	for(int i=0;i<n;i++) t[i]=i;
	shuffle(t.begin(),t.end(),rd);
	while(query(t)) shuffle(t.begin(),t.end(),rd);
	int nn=n-(n%2==0);
	for(int i=0;i<nn;i++){
		vector<pair<int,int> >p,q;
		for(int j=1;j<=(n-1)/2;j++) p.emplace_back((i-j+nn)%nn,(i+j)%nn);
		if(n%2==0) p.emplace_back(n-1,i);
		for(auto [x,y]:p) if(du[x]<2&&du[y]<2) q.emplace_back(x,y);
		if(!q.size()) continue;
		work(q,0,q.size()-1);
	}
	int now=0;
	for(int i=0;i<n;i++) for(int j=i+1;j<n;j++){
		if(h[i][j]==2) swap(t[i],t[j]),now+=2,vis[i]=vis[j]=1;
		if(h[i][j]==1) e[i].emplace_back(j),e[j].emplace_back(i);
	}
	for(int i=0;i<n;i++) if(!vis[i]){
		b.clear(),dfs(i,0,i);
		vector<int>tmp=t;
		for(int j=0;j<(int)b.size();j++) tmp[b[j]]=t[b[(j+1)%b.size()]];
		if(query(tmp)>now) t=tmp,now+=b.size();
		else{
			for(int j=0;j<(int)b.size();j++) tmp[b[j]]=t[b[(j-1+b.size())%b.size()]];
			t=tmp,now+=b.size();
		}
		for(auto u:b) vis[u]=1;
	}
	check(t);
}