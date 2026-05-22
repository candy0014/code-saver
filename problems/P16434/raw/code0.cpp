#include <bits/stdc++.h>
using namespace std;
int compare_tastiness(std::vector<int> S1, std::vector<int> S2);
vector<int> bake_cakes(int N,int W,int K){
	vector<int>res;
	if(K==100) for(int i=1;i<=100;i++) res.emplace_back(i);
	if(K==1) res={1,2,3};
	if(K==30){
		res.emplace_back(1);
		for(int i=1;i<=W;i*=2) res.emplace_back(i);
	}
	if(K==7) for(int i=1;i<=2187;i++) res.emplace_back(i);
	return res;
}
int find_tastiness(int m,int W,int K){
	if(K==100){
		for(int i=1;i<=100;i++) if(compare_tastiness({i},{i-1})==0) return i;
		return 0;
	}
	if(K==1) return compare_tastiness({1,2},{0,3})+2;
	if(K==30){
		int pos=0;
		for(int i=m-1;i>=0;i--){
			vector<int>tmp;
			for(int j=0;j<i;j++) tmp.emplace_back(j);
			if(compare_tastiness(tmp,{i})==0){pos=i+1;break;}
		}
		int res=0;
		for(int i=pos-1;i>=2;i--){
			int x=res|(1<<(i-1));
			vector<int>tmp;
			for(int j=0;j<pos;j++) if((x>>j)&1) tmp.emplace_back(j+1);
			int t=compare_tastiness(tmp,{pos});
			if(!t) return x;
			if(t<0) res=x;
		}
		return res+1;
	}
	if(K==7){
		int l=0,r=m;
		while(l+1<r){
			int d=(r-l)/3;
			int t=compare_tastiness({l+d,r-d},{l,r});
			if(t==-1) r=l+d;
			if(t==0) l+=d,r-=d;
			if(t==1) l=r-d;
		}
		return r;
	}
	return 0;
}