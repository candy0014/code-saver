#include <bits/stdc++.h>
using namespace std;
int n,m,a[400005],li[200005],d;
vector<int>p;
vector<pair<int,int> >res;
int pre[200005],nex[200005],cnt[200005],tag[200005],now;
bool check(int u){
	if(tag[u]||a[p[u]]==a[p[pre[u]]]||a[p[u]]==a[p[nex[u]]]||a[p[pre[u]]]==a[p[nex[u]]]||(now==3&&cnt[a[p[u]]]==1)) return 0;
	return 1;
}
void solve(){
	cin>>n>>m,m=0;
	for(int i=0;i<n;i++) cin>>a[i],li[++m]=a[i],a[i+n]=a[i];
	sort(li+1,li+m+1),m=unique(li+1,li+m+1)-li-1;
	for(int i=0;i<n;i++) a[i]=lower_bound(li+1,li+m+1,a[i])-li;
	if(m==1){cout<<"0\n";return;}
	d=0;
	while(a[d]==a[0]) d++;
	for(int i=0;i<n;i++) a[i]=a[i+d];
	p.clear(),res.clear();
	for(int i=0;i<n;i++) if(i==0||a[i]!=a[i-1]) p.emplace_back(i);
	for(int i=0;i<(int)p.size();i++){
		int u=p[(i+1)%p.size()];
		for(int j=p[i]+(p.size()==2&&i==1);j<(!u?n:u);j++) res.emplace_back(j,u);
	}
	if(m==2) for(int i=3;i+1<(int)p.size();i+=2) res.emplace_back(p[0],p[i]);
	else{
		queue<int>q;
		for(int i=0;i<(int)p.size();i++) q.push(i),tag[i]=0,pre[i]=(i-1+p.size())%p.size(),nex[i]=(i+1)%p.size();
		for(int i=1;i<=m;i++) cnt[i]=0;
		for(auto x:p) cnt[a[x]]++;
		now=m;
		while(!q.empty()){
			int u=q.front();q.pop();
			if(!check(u)) continue;
			tag[u]=1,cnt[a[p[u]]]--;
			if(!cnt[a[p[u]]]) now--;
			nex[pre[u]]=nex[u],pre[nex[u]]=pre[u],res.emplace_back(p[pre[u]],p[nex[u]]);
			if(check(pre[u])) q.push(pre[u]);
			if(check(nex[u])) q.push(nex[u]);
		}
	}
	cout<<res.size()<<"\n";
	for(auto [x,y]:res){
		x=(x+d)%n,y=(y+d)%n;
		if(x>y) swap(x,y);
		cout<<x+1<<" "<<y+1<<"\n";
	}
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}