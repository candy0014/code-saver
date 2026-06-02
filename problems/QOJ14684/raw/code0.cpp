#include <bits/stdc++.h>
using namespace std;
int n,m,k;
int id1[5][10],id2[5][10],pre[10],suf[10],tot=1;
vector<pair<int,int> >e;
void add(int u,int v){e.emplace_back(u,v);}
int main(){
	cin>>n>>m>>k;
	if(n==5){
		cout<<"1 2\n1 3\n2 4\n3 5\n2 5\n3 4\n1 1\n1 2\n1 3\n1 4\n1 5\n2 2 3\n";
		return 0;
	}
	for(int i=1;i<=3;i++) for(int j=1;j<=7;j++) id1[i][j]=++tot;
	for(int i=1;i<=3;i++) for(int j=1;j<=7;j++) id2[i][j]=++tot;
	for(int j=2;j<=6;j++) pre[j]=++tot,suf[j]=++tot;
	suf[7]=id1[1][7],pre[1]=id1[1][1];
	for(int i:{1,2}) for(int j=1;j<=7;j++) add(id1[i][j],id1[i+1][j]),add(id2[i][j],id2[i+1][j]);
	for(int j=2;j<=6;j++) add(pre[j],id1[1][j]),add(suf[j],id1[1][j]),add(pre[j],pre[j-1]),add(suf[j],suf[j+1]);
	for(int j=1;j<=7;j++){
		if(j!=7) add(id2[3][j],suf[j+1]);
		if(j!=1) add(id2[3][j],pre[j-1]);
		add(id2[2][j],id1[3][j]),add(id2[1][j],id1[2][j]);
	}
	for(int j=1;j<=7;j++) add(1,id2[1][j]);
	while(tot<100) add(1,++tot);
	for(auto x:e) cout<<x.first<<" "<<x.second<<"\n";
	for(int i=1;i<=k;i++){
		vector<int>p;
		for(int j=0;j<7;j++){
			int t=(i>>(j*2))&3;
			if(t) p.emplace_back(id2[t][j+1]);
		}
		cout<<p.size();
		for(auto x:p) cout<<" "<<x;
		cout<<"\n";
	}
	return 0;
}