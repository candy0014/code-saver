#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int V=50000;
int n,H;
struct node{int x,v,e;};
vector<node>s[200005];
struct TREE{
	vector<pair<int,ll> >st[800005];
	ll query(int p,int l,int r,int L,int R,int lim){
		if(r<L||l>R) return 0;
		if(L<=l&&r<=R){
			int it=lower_bound(st[p].begin(),st[p].end(),make_pair(lim,0ll))-st[p].begin();
			if(it==st[p].size()) return 0;
			return st[p][it].second;
		}
		int mid=l+(r-l)/2;return max(query(p*2,l,mid,L,R,lim),query(p*2+1,mid+1,r,L,R,lim));
	}
	void change(int p,int l,int r,int x,int y,ll val){
		while(st[p].size()&&st[p].back().second<=val) st[p].pop_back();
		st[p].emplace_back(y,val);
		if(l==r) return;
		int mid=l+(r-l)/2;
		if(x<=mid) change(p*2,l,mid,x,y,val);
		else change(p*2+1,mid+1,r,x,y,val);
	}
}tr;
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>H;
	for(int i=1,x,y,v,e;i<=n;i++) cin>>x>>y>>v>>e,s[y].emplace_back(node{x,v,e});;
	ll res=0;
	for(int i=1;i<=H;i++) if(s[i].size()){
		sort(s[i].begin(),s[i].end(),[&](node u,node v){return u.x<v.x;});
		for(int j=0;j<(int)s[i].size();j++){
			int k=j;
			while(k+1<(int)s[i].size()&&s[i][k+1].x-s[i][k].x<=s[i][k].e) k++;
			ll tmp=tr.query(1,-V,V,s[i][j].x-s[i][j].e,s[i][k].x+s[i][j].e,i-s[i][j].e);
			for(int t=j;t<=k;t++) tmp+=s[i][t].v;
			res=max(res,tmp);
			for(int t=j;t<=k;t++) tr.change(1,-V,V,s[i][t].x,i,tmp);
			j=k;
		}
	}
	cout<<res<<"\n";
	return 0;
}