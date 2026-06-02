#include <bits/stdc++.h>
using namespace std;
int n,m,mod,cnt[500005];
struct node{int sz,ty;}s[500005];
int mul[2000005];
int la[500005],id[500005],idd[500005];
vector<int>pos[500005];
void change(int p,int l,int r,int x,int k){
	if(r<x||l>x) return;
	if(l==r){mul[p]=k%mod;return;}
	int mid=(l+r)>>1;change(p*2,l,mid,x,k),change(p*2+1,mid+1,r,x,k),mul[p]=mul[p*2]*mul[p*2+1]%mod;
}
int query(int p,int l,int r,int L,int R){
	if(r<L||l>R||L>R) return 1;
	if(L<=l&&r<=R) return mul[p];
	int mid=(l+r)>>1;return query(p*2,l,mid,L,R)*query(p*2+1,mid+1,r,L,R)%mod;
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>mod;
	for(int i=1;i<=n;i++) cin>>s[i].sz>>s[i].ty;
	for(int i=1;i<=m;i++) cnt[i]=1,id[i]=i;
	for(int i=1;i<=m*4;i++) mul[i]=1;
	sort(s+1,s+n+1,[&](node u,node v){return u.sz<v.sz;});
	for(int i=1;i<=n;i++) la[s[i].ty]=i,pos[s[i].ty].emplace_back(i);
	sort(id+1,id+m+1,[&](int u,int v){return la[u]<la[v];});
	for(int i=1;i<=m;i++) idd[id[i]]=i;
	int res=0;
	for(int ii=1,i,r=0;ii<=m;ii++){
		i=id[ii];
		while(r<n&&s[r+1].sz*2<=s[la[i]].sz) r++,cnt[s[r].ty]++,change(1,1,m,idd[s[r].ty],cnt[s[r].ty]);
		int it=upper_bound(pos[i].begin(),pos[i].end(),r)-pos[i].begin();
		int nex=lower_bound(id+1,id+m+1,s[pos[i][it]].sz*2,[&](int u,int v){return s[la[u]].sz<v;})-id;
		int tmp=query(1,1,m,1,ii-1);
		res=(res+1ll*tmp*(cnt[i]-1)+1ll*tmp*query(1,1,m,ii+1,nex-1))%mod;
	}
	cout<<res<<"\n";
	return 0;
}