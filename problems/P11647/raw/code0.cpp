// #include "tanebi.h"
#include <bits/stdc++.h>
using namespace std;
std::vector<long long> ask(std::vector<int> x,std::vector<int> y);
typedef long long ll;
typedef __int128 LL;
vector<int>e[505];
vector<ll> check(int n,vector<ll>p,vector<ll>q,ll tp,ll tq){
	for(auto &x:p) if(x==tp){swap(x,p.back()),p.pop_back();break;}
	for(auto &x:q) if(x==tq){swap(x,q.back()),q.pop_back();break;}
	p.emplace_back(tq),q.emplace_back(tp);
	vector<ll>res(n);
	LL sum=0,summ=0;
	for(auto x:q) sum+=x;
	for(auto x:p) summ+=x;
	if((summ-sum/2)%(n-1)) return {};
	res[0]=(summ-sum/2)/(n-1);
	res[1]=tq-res[0],res[2]=tp-res[1];
	for(int i=3;i<n;i++){
		int f=0;
		for(auto x:p){
			ll y=x-res[0],flag=0;
			if(y==res[i-2]) continue;
			for(auto z:q) if(y+res[i-1]==z){flag=1;break;}
			if(flag){res[i]=y,f=1;break;}
		}
		if(!f) return {};
	}
	return res;
}
vector<ll> game(int n){
	vector<int>px,py;
	vector<ll> p,q,pp;
	for(int i=2;i<n;i++) px.emplace_back(0),py.emplace_back(i);
	px.emplace_back(1),py.emplace_back(2);
	p=ask(px,py);
	px.clear(),py.clear();
	for(int i=2;i<n;i++) px.emplace_back(i),py.emplace_back(i==(n-1)?1:(i+1));
	px.emplace_back(0),py.emplace_back(1);
	q=ask(px,py);
	for(auto x:p) for(auto y:q){
		vector<ll>res=check(n,p,q,x,y);
		if(res.size()) return res;
	}
	return {};
}