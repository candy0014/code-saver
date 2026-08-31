#include <bits/stdc++.h>
using namespace std;
int n,ca,a[100005],mi[100005][20];
int getmi(int u,int v){return a[u]<a[v]?u:v;}
int query(int l,int r){
	if(l>r) return 0;
	int t=__lg(r-l+1);
	return getmi(mi[l][t],mi[r-(1<<t)+1][t]);
}
int _query(int l,int r){
	int x=query(l,r);
	if(!x) return 1e9+5;
	return a[x];
}
set<pair<int,int> >st;
set<int>p;
int tag[100005];
int rt[100005],tt[100005],cnt;
int ls[10000005],rs[10000005],sum[10000005],tot;
int change(int p,int l,int r,int x){
	int q=++tot,mid=(l+r)>>1;
	sum[q]=sum[p]+1;
	if(l==r) return q;
	ls[q]=ls[p],rs[q]=rs[p];
	if(x<=mid) ls[q]=change(ls[p],l,mid,x);
	else rs[q]=change(rs[p],mid+1,r,x);
	return q; 
}
int query(int p,int l,int r,int L,int R){
	if(r<L||l>R||!p) return 0;
	if(L<=l&&r<=R) return sum[p];
	int mid=(l+r)>>1;
	return query(ls[p],l,mid,L,R)+query(rs[p],mid+1,r,L,R);
}
void update(int tim,int pos){
	cnt++,tt[cnt]=tim,tag[pos]=1;
	rt[cnt]=change(rt[cnt-1],1,n,pos);
}
int calc(int l,int r,int x){
	int t=upper_bound(tt+1,tt+cnt+1,x)-tt-1;
	int _l,_r,mid,L=-1,R=-1;
	_l=l,_r=r;
	while(_l<=_r){
		mid=(_l+_r)>>1;
		if(_query(l,mid)<=x/2) _r=mid-1,L=mid;
		else _l=mid+1;
	}
	if(L==-1) return 0;
	_l=l,_r=r;
	while(_l<=_r){
		mid=(_l+_r)>>1;
		if(_query(mid,r)<=x/2) _l=mid+1,R=mid;
		else _r=mid-1;
	}
	int res=query(rt[t],1,n,L,R);
	if((l!=L||r!=R)&&min(_query(l,L-1),_query(R+1,r))+max(a[L],a[R])<=x) res++;
	return res;
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>ca;
	for(int i=1;i<=n;i++) cin>>a[i],mi[i][0]=i;
	for(int j=1;j<20;j++) for(int i=1;i+(1<<j)-1<=n;i++) mi[i][j]=getmi(mi[i][j-1],mi[i+(1<<(j-1))][j-1]);
	for(int i=1;i<=n;i++) st.insert(make_pair(a[i]*2,i));
	while(st.size()){
		pair<int,int>t=*st.begin();st.erase(st.begin());
		if(t.second>0){
			if(!tag[t.second]) update(t.first,t.second);
			auto it=p.lower_bound(t.second);
			if(it!=p.end()){
				int l=t.second+1,r=(*it)-1,x;
				if(l<=r) x=query(l,r),st.insert(make_pair(a[x]+a[t.second],-x));
			}
			if(it!=p.begin()){
				int l=(*prev(it)+1),r=t.second-1,x;
				if(l<=r) x=query(l,r),st.insert(make_pair(a[x]+a[t.second],-x));
			}
			p.insert(t.second);
		}
		else update(t.first,-t.second);
	}
	while(ca--){
		int L,R,k;
		cin>>L>>R>>k;
		int l=0,r=2e9,mid,res=0;
		while(l<=r){
			mid=l+(r-l)/2;
			if(calc(L,R,mid)>=k) res=mid,r=mid-1;
			else l=mid+1;
		}
		cout<<res<<"\n";
	}
	return 0;
}