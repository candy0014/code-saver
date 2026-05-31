#include <bits/stdc++.h>
using namespace std;
int n,m,ca,c[2005];
bitset<2005>b[2005],h[2005],tmp;
set<pair<int,int> >s,t;
bool check(int x,int y){
	return (b[x]&b[y])!=b[x];
}
void del(int x,int y){
	if(t.find(make_pair(x,y))!=t.end()) t.erase(make_pair(x,y));
}
void add(int x,int y){
	if(check(x,y)) t.insert(make_pair(x,y));
}
void erase(int x){
	auto it=s.find(make_pair(c[x],x));
	if(next(it)!=s.end()) del((*it).second,(*next(it)).second);
	if(it!=s.begin()) del((*prev(it)).second,(*it).second);
	it=s.erase(it);
	if(it!=s.end()&&it!=s.begin()) add((*prev(it)).second,(*it).second);
}
void insert(int x){
	auto it=s.lower_bound(make_pair(c[x],x));
	if(it!=s.end()&&it!=s.begin()) del((*prev(it)).second,(*it).second);
	it=s.insert(make_pair(c[x],x)).first;
	if(next(it)!=s.end()) add((*it).second,(*next(it)).second);
	if(it!=s.begin()) add((*prev(it)).second,(*it).second);
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>ca;
	for(int i=1;i<=n;i++) s.insert(make_pair(0,i));
	for(int i=1;i<=m;i++) for(int j=0;j<i;j++) h[i][j]=1;
	while(ca--){
		int p,l,r;
		cin>>p>>l>>r;
		erase(p);
		b[p]^=(h[r-l+1]<<l),c[p]=b[p].count();
		insert(p);
		if(!t.size()){cout<<"-1\n";continue;}
		int x=(*t.begin()).first,y=(*t.begin()).second;
		tmp=b[x]&b[y];
		int xx=(b[x]^tmp)._Find_first(),yy=(b[y]^tmp)._Find_first();
		if(x>y) swap(x,y);
		if(xx>yy) swap(xx,yy);
		cout<<x<<" "<<xx<<" "<<y<<" "<<yy<<"\n";
	}
	return 0;
}