#include <bits/stdc++.h>
using namespace std;
int n,ca,a[200005];
vector<int>p[105];
int sum[200005];
int L[200005],R[200005],V[200005],res[200005];
int mi[20][200005];
int query(int l,int r){
	int t=__lg(r-l+1);
	return min(mi[t][l],mi[t][r-(1<<t)+1]);
}
int cc[200005];
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=100;i++) p[i].emplace_back(0);
	for(int i=1;i<=n;i++) cin>>a[i],p[a[i]].emplace_back(i);
	cin>>ca;
	for(int i=1;i<=ca;i++) cin>>L[i]>>R[i];
	for(int c=1;c<=100;c++){
		for(int i=1;i<=n;i++){
			cc[i]=cc[i-1]+(a[i]==c);
			sum[i]=sum[i-1]+((a[i]<=c)?-a[i]:a[i]),mi[0][i]=sum[i];
		}
		for(int j=1;j<20;j++) for(int i=1;i+(1<<j)-1<=n;i++) mi[j][i]=min(mi[j-1][i],mi[j-1][i+(1<<(j-1))]);
		for(int i=1;i<=ca;i++){
			int l=cc[L[i]-1]+1,_l=l,r=cc[R[i]],mid,ans=r+1;
			if(l>r) continue;
			while(l<=r){
				mid=(l+r)>>1;
				if(V[i]+query(p[c][mid],R[i])-sum[L[i]-1]+2*c*(mid-_l)>=0) r=mid-1,ans=mid;
				else l=mid+1;
			}
			res[i]+=cc[R[i]]-ans+1;
			if(p[c][ans-1]>=L[i]){
				V[i]+=sum[p[c][ans-1]]-sum[L[i]-1]+2*c*(ans-_l);
				L[i]=p[c][ans-1]+1;
			}
		}
	}
	for(int i=1;i<=ca;i++) cout<<res[i]<<"\n";
	return 0;
}