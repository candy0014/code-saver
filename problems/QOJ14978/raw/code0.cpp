#include <bits/stdc++.h>
using namespace std;
mt19937 rd(time(0));
int n,id[305],res[305];
double g[305];
int tag[305];
int ask(vector<int>p){
	cout<<"? "<<p.size();
	for(auto x:p) cout<<" "<<id[x];
	cout<<endl;

	int x=0;
	cin>>x;
	// for(auto y:p) if(tag[id[y]]) x+=rd()%2; 
	// cout<<x<<"\n";

	if(x==p.size()) for(auto x:p) res[id[x]]=1,g[x]=0;
	if(!x) for(auto x:p) g[x]/=2;
	return x;
}
void work(vector<int>p,int lim){
	vector<int>idd(p.size());
	for(int i=0;i<(int)p.size();i++) idd[i]=i;
	while(1){
		int cnt=0;
		for(auto x:p) cnt+=res[id[x]];
		if(cnt>=lim) return;
		sort(idd.begin(),idd.end(),[&](int u,int v){return g[p[u]]>g[p[v]];});
		int len=(p.size()-1)/3+1;
		vector<int>q;
		double tmp=0;
		for(int i=0;i<len;i++){
			q.emplace_back(p[idd[i]]);
			tmp+=g[p[idd[i]]];
			if(tmp>2) break;
		}
		work(q,ask(q));
	}
}
void solve(){
	cin>>n;
	for(int i=1;i<=48;i++) tag[i]=1;
	for(int i=1;i<=n;i++) id[i]=i,res[i]=0,g[i]=1.0/6;
	shuffle(id+1,id+n+1,rd);
	vector<int>p;
	for(int i=1;i<=n;i++) p.emplace_back(i);
	work(p,48);
	cout<<"! ";
	for(int i=1;i<=n;i++) cout<<res[i];
	cout<<endl;
	string ok;cin>>ok;
}
int main(){
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}