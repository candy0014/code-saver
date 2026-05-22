#include <bits/stdc++.h>
using namespace std;
int n,k,a[300005],sum[300005];
pair<int,int> check(int x){
	int mi=1e9,mik=0;
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1]+(a[i]>=x)-(a[i]<x);
		if(i>=k){
			if(sum[i-k]<mi) mi=sum[i-k],mik=i-k+1;
			if(sum[i]>=mi) return make_pair(mik,i);
		}
	}
	return make_pair(0,0);
}
array<int,3> calc(){
	int l=1,r=n,mid;
	array<int,3>res={0,0,0};
	while(l<=r){
		mid=(l+r)>>1;
		pair<int,int> tmp=check(mid);
		if(tmp.first) l=mid+1,res={mid,tmp.first,tmp.second};
		else r=mid-1;
	}
	return res;
}
pair<int,int>res[300005];
set<int>st;
multiset<int>q1,q2;
void add(int x){
	if(x>*q1.rbegin()) q2.insert(x);
	else q1.insert(x);
}
void del(int x){
	if(q1.find(x)!=q1.end()) q1.erase(q1.find(x));
	else q2.erase(q2.find(x));
}
void update(int l,int r){
	while(q2.size()>q1.size()) q1.insert(*q2.begin()),q2.erase(q2.begin());
	while(q1.size()>q2.size()+1) q2.insert(*q1.rbegin()),q1.erase(prev(q1.end()));
	int L=*q1.rbegin(),R=L;
	if(q1.size()==q2.size()) R=*q2.begin();
	while(1){
		auto it=st.lower_bound(L);
		if(it==st.end()||(*it)>R) break;
		res[*it]=make_pair(l,r),st.erase(it);
	}
}
void solve(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	array<int,3> rs=calc();
	for(int i=1;i<=n;i++) a[i]=n-a[i]+1;
	array<int,3> ls=calc();
	for(int i=1;i<=n;i++) a[i]=n-a[i]+1;
	ls[0]=n-ls[0]+1;
	st.clear();
	for(int i=ls[0];i<=rs[0];i++) st.insert(i);
	q1.clear(),q2.clear();
	for(int i=ls[1];i<=ls[2];i++) q1.insert(a[i]);
	update(ls[1],ls[2]);
	while(ls[1]>rs[1]) add(a[--ls[1]]),update(ls[1],ls[2]);
	while(ls[2]<rs[2]) add(a[++ls[2]]),update(ls[1],ls[2]);
	while(ls[1]<rs[1]) del(a[ls[1]++]),update(ls[1],ls[2]);
	while(ls[2]>rs[2]) del(a[ls[2]--]),update(ls[1],ls[2]);
	cout<<rs[0]-ls[0]+1<<"\n";
	for(int i=ls[0];i<=rs[0];i++) cout<<i<<" "<<res[i].first<<" "<<res[i].second<<"\n";
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}