#include <bits/stdc++.h>
using namespace std;
int n,id[505],tag[505];
int ask(int u,int l=-1,int r=-1){
	vector<int>p;
	if(l==-1) for(int i=2;i<=n;i++) p.emplace_back(i);
	else for(int i=l;i<=r;i++) if(!tag[i]) p.emplace_back(id[i]);
	if(!p.size()) return 0;
	cout<<"1\n1\n"<<p.size()<<"\n";
	for(auto x:p) cout<<x<<" ";
	cout<<"\n"<<u<<endl;
	int t;cin>>t;return t;
}
int sz[505];
vector<pair<int,int> >res;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) id[i]=i,sz[i]=(i==1?n:ask(i));
	sort(id+1,id+n+1,[&](int u,int v){return sz[u]<sz[v];});
	for(int i=2;i<=n;i++){
		int g=ask(id[i],1,i-1),la=0;
		while(g--){
			int l=la+1,r=i-1,mid,son=0;
			while(l<=r){
				mid=(l+r)>>1;
				if(ask(id[i],la+1,mid)) son=mid,r=mid-1;
				else l=mid+1;
			}
			tag[son]=1,res.emplace_back(id[i],id[son]);
		}
	}
	cout<<"ANSWER"<<endl;
	for(auto [u,v]:res) cout<<u<<" "<<v<<endl;
	return 0;
}