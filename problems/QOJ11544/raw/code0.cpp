#include <bits/stdc++.h>
using namespace std;
int n,a[200005],li[200005],tot,id[200005],ma[200005];
vector<int>p[200005];
vector<pair<int,int> >as[200005];
int res;
vector<int>h[200005];
vector<int>g[200005];
set<int>st;
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],li[i]=a[i];
	sort(li+1,li+n+1),tot=unique(li+1,li+n+1)-li-1;
	for(int i=1;i<=tot+1;i++) p[i].clear(),ma[i]=-1e9,g[i].clear();
	for(int i=1;i<=n;i++) a[i]=lower_bound(li+1,li+tot+1,a[i])-li,p[a[i]].emplace_back(i),id[i]=p[a[i]].size();
	as[n+1].clear(),res=0;
	for(int i=n;i>=1;i--){
		int tmp=id[i]*2-i;ma[a[i]]=max(ma[a[i]],tmp);
		as[i].clear(),as[i].emplace_back(a[i],ma[a[i]]-tmp+1),res=max(res,ma[a[i]]-tmp+1);
		for(auto [x,c]:as[i+1]) if(x!=a[i]&&c) as[i].emplace_back(x,c-1);
	}
	for(int i=1;i<=res;i++) h[i].clear();
	int now=0;
	st.clear();
	for(int i=1;i<=n;i++){
		int tmp=0;
		for(auto [x,c]:as[i]) if(x!=a[i]&&g[x].size()+c==res){tmp=x;break;}
		if(!tmp){
			if(!st.size()||(st.size()==1&&(*st.begin())==a[i])) tmp=(a[i]==1)?2:1;
			else if((*st.begin())==a[i]) tmp=*next(st.begin());
			else tmp=*st.begin();
		}
		int pos;
		if(g[tmp].size()) pos=g[tmp].back();
		else pos=++now;
		h[pos].emplace_back(i);
		if(g[tmp].size()){
			g[tmp].pop_back();
			if(!g[tmp].size()) st.erase(tmp);
		}
		g[a[i]].emplace_back(pos),st.insert(a[i]);
	}
	cout<<res<<"\n";
	for(int i=1;i<=res;i++){
		cout<<h[i].size();
		for(auto x:h[i]) cout<<" "<<x;
		cout<<"\n";
	}
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}