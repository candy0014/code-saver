#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int len=350;
int n,ca,a[100005],l[100005],r[100005],th[100005],id[100005];
ll res[100005];
int L,R,cnt[2][1200005];
ll now;
void add(int x){
	now+=cnt[x&1][a[x]],cnt[x&1][a[x]]++;
}
void del(int x){
	cnt[x&1][a[x]]--,now-=cnt[x&1][a[x]];
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>ca;
	for(int i=1;i<=n;i++) cin>>a[i],a[i]=a[i-1]^(a[i]-1);
	for(int i=1;i<=ca;i++) cin>>l[i]>>r[i],l[i]--,id[i]=i;
	for(int i=0;i<=n;i++) th[i]=i/len;
	sort(id+1,id+ca+1,[&](int u,int v){return th[l[u]]==th[l[v]]?r[u]<r[v]:l[u]<l[v];});
	L=1,R=0;
	for(int ii=1;ii<=ca;ii++){
		int i=id[ii];
		while(L>l[i]) add(--L);
		while(R<r[i]) add(++R);
		while(L<l[i]) del(L++);
		while(R>r[i]) del(R--);
		res[i]=1ll*(r[i]-l[i]+1)*(r[i]-l[i])/2-now;
	}
	for(int i=1;i<=ca;i++) cout<<res[i]<<"\n";
	return 0;
}