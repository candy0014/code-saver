#include <bits/stdc++.h>
using namespace std;
int n,m;
vector<pair<int,int> >pp,p;
int ask(int l,int r){cout<<"? "<<l<<" "<<r<<endl,cin>>l;return l;}
void solve(){
	cin>>n>>m,pp.resize(m),p.clear();
	for(int i=0;i<m;i++) cin>>pp[i].first>>pp[i].second;
	sort(pp.begin(),pp.end(),[&](pair<int,int>u,pair<int,int>v){return u.first<v.first||u.first==v.first&&u.second>v.second;});
	for(int i=0;i<m;i++) if(!p.size()||pp[i].second>p.back().second) p.emplace_back(pp[i]);
	int l=0,r=p.size()-1,mid,res=-1,la=-1;
	while(l<=r){
		mid=(l+r)>>1;
		int pre=ask(p[mid].first,n),suf=ask(1,p[mid].second);
		if(pre>=suf) l=mid+1,res=mid,la=min(pre,suf);
		else r=mid-1;
	}
	if(res+1<p.size()) la=max(la,ask(p[res+1].first,p[res+1].second));
	cout<<"! "<<la<<endl;
}
int main(){
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}