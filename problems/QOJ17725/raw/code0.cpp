#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m,ca;
ll b[300005],a[300005],sum[300005];
ll res[300005];
int st[300005],top;
bool cmp(ll x0,ll y0,ll x1,ll y1){return y0*x1<y1*x0;}
void solve(int l,int r){
	if(l>r) return;
	int mid=(l+r)>>1;
	if(l!=r) solve(l,mid),solve(mid+1,r);
	vector<pair<ll,ll> >p;
	top=0;
	for(int i=1;i<=mid-l+1;i++){
		while(top&&cmp(st[top]-st[top-1],sum[mid-st[top-1]]-sum[mid-st[top]],i-st[top],sum[mid-st[top]]-sum[mid-i])) top--;
		st[++top]=i;
	}
	for(int i=1;i<=top;i++) p.emplace_back(st[i]-st[i-1],sum[mid-st[i-1]]-sum[mid-st[i]]);
	top=0;
	for(int i=1;i<=r-mid;i++){
		while(top&&cmp(st[top]-st[top-1],sum[mid+st[top]]-sum[mid+st[top-1]],i-st[top],sum[mid+i]-sum[mid+st[top]])) top--;
		st[++top]=i;
	}
	for(int i=1;i<=top;i++) p.emplace_back(st[i]-st[i-1],sum[mid+st[i]]-sum[mid+st[i-1]]);
	sort(p.begin(),p.end(),[&](pair<int,ll>u,pair<int,ll>v){return cmp(v.first,v.second,u.first,u.second);});
	ll tx=0,ty=0;
	for(auto [dx,dy]:p) tx+=dx,ty+=dy,res[tx-1]=max(res[tx-1],ty);
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>m>>ca;
	for(int i=1;i<=m;i++) cin>>b[i];
	for(int i=1;i<=m;i++){
		int j=i-1;n++;
		while(j<m&&b[j+1]!=-1) a[n]+=b[++j];
		i=j+1;
	}
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];
	for(int i=1;i<=n;i++) res[i]=-1;
	solve(1,n);
	st[top=1]=0;
	for(int i=1;i<n;i++) if(res[i]!=-1){
		while(top>1&&cmp(st[top]-st[top-1],res[st[top]]-res[st[top-1]],i-st[top],res[i]-res[st[top]])) top--;
		st[++top]=i;
	}
	while(ca--){
		int x;
		cin>>x;
		int l=2,r=top,mid,ans=1;
		while(l<=r){
			mid=(l+r)>>1;
			if(res[st[mid-1]]-1ll*st[mid-1]*x<=res[st[mid]]-1ll*st[mid]*x) ans=mid,l=mid+1;
			else r=mid-1;
		}
		cout<<res[st[ans]]-1ll*st[ans]*x<<"\n";
	}
	return 0;
}