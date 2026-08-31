#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
const ll mod=998244353;
const ll inf=2e9;
const int N=2e5+5;
const int M=2e5+5;
const int V=2e6+5;
int n,a[300005],pre[300005],nex[300005];
int st[300005],top;
int mi[300005][20];
int getmi(int u,int v){return a[u]<a[v]?u:v;}
map<pair<int,int>,int>mp;
vector<pair<int,int> >g;
int tot;
int query(int l,int r){
	if(l>r) return 0;
	int t=__lg(r-l+1);
	return getmi(mi[l][t],mi[r-(1<<t)+1][t]);
}
int query_(int l,int r){
	return a[query(l,r)];
}
pair<int,int> get_(int l,int r){
	if(l>=r) return make_pair(0,0);
	int mik=query(l,r);
	int mik1=query(l,mik-1),mik2=query(mik+1,r);
	if(a[mik1]<a[mik2]) return make_pair(mik1,mik);
	return make_pair(mik,mik2);
}
int get(int l,int r){
	auto tmp=get_(l,r);
	if(tmp.first==0) return -1;
	return mp[make_pair(tmp.first,tmp.second)];
}
int res[600005];
ll ans[300005];
void solve(int Ca){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],mi[i][0]=i;
	for(int j=1;j<20;j++) for(int i=1;i+(1<<j)-1<=n;i++) mi[i][j]=getmi(mi[i][j-1],mi[i+(1<<(j-1))][j-1]);
	a[0]=1e9;
	for(int i=1;i<=n;i++){
		while(top&&a[st[top]]>a[i]) top--;
		pre[i]=st[top],st[++top]=i;
		if(pre[i]) g.emplace_back(pre[i],i);
	}
	top=0,st[0]=n+1;
	for(int i=n;i>=1;i--){
		while(top&&a[st[top]]>a[i]) top--;
		nex[i]=st[top],st[++top]=i;
		if(nex[i]!=n+1) g.emplace_back(i,nex[i]);
	}
	sort(g.begin(),g.end(),[&](pair<int,int>u,pair<int,int>v){
		return u.second-u.first<v.second-v.first;
	});
	for(int i=0;i<(int)g.size();i++) mp[g[i]]=i;
	for(int i=0;i<(int)g.size();i++){
		int id=get(g[i].first+1,g[i].second-1);
		if(id==-1) res[i]=1;
		else res[i]=res[id]+1;
		int x=g[i].first,y=g[i].second;
		int L,R;
		if(a[x]<a[y]){
			R=nex[y]-1;
			int l=1,r=x,mid;
			while(l<=r){
				mid=(l+r)>>1;
				if(query_(mid,x-1)>=a[y]) L=mid,r=mid-1;
				else l=mid+1;
			}
		}
		else{
			L=pre[x]+1;
			int l=y,r=n,mid;
			while(l<=r){
				mid=(l+r)>>1;
				if(query_(y+1,mid)>=a[x]) R=mid,l=mid+1;
				else r=mid-1;
			}
		}
		ans[res[i]]+=1ll*(x-L+1)*(R-y+1);
	}
	for(int i=1;i<=n;i++) cout<<ans[i]<<"\n";
}
int main(){
	#ifdef ONLINE_JUDGE
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	#endif
	#ifndef ONLINE_JUDGE
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	
	int Ca=1;
//	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}