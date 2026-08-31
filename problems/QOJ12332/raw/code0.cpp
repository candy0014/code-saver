#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m,k;
ll a[1505][1505];
ll sum[1505][1505],sum1[3005][1505],sum2[3005][1505];
ll p1[3005],q1[3005],p2[3005],q2[3005],p3[3005],q3[3005],p4[3005],q4[3005];
void Max(ll &u,ll v){u=max(u,v);}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin>>a[i][j],sum[j][i]=sum[j][i-1]+a[i][j],sum1[i+j][i]=sum1[i+j][i-1]+a[i][j],sum2[i-j+m][i]=sum2[i-j+m][i-1]+a[i][j];
	for(int i=0;i<=3001;i++) p1[i]=q1[i]=p2[i]=q2[i]=p3[i]=q3[i]=p4[i]=q4[i]=-1e18;
	for(int i=1;i<=n-k+1;i++){
		ll s1=0,s2=0,s3=0,s4=0;
		for(int j=1;j<=k;j++) s1+=sum[j][i+k-j]-sum[j][i-1],s2+=sum[j][i+k-1]-sum[j][i+k-j-1],s3+=sum[j][i+j-1]-sum[j][i-1],s4+=sum[j][i+k-1]-sum[j][i+j-2];
		for(int j=1;j<=m-k+1;j++){
			if(j>1){
				s1+=(sum1[i+j+k-1][i+k-1]-sum1[i+j+k-1][i-1])-(sum[j-1][i+k-1]-sum[j-1][i-1]);
				s2+=(sum[j+k-1][i+k-1]-sum[j+k-1][i-1])-(sum1[i+j+k-2][i+k-1]-sum1[i+j+k-2][i-1]);
				s3+=(sum[j+k-1][i+k-1]-sum[j+k-1][i-1])-(sum2[i-j+1+m][i+k-1]-sum2[i-j+1+m][i-1]);
				s4+=(sum2[i-j+m][i+k-1]-sum2[i-j+m][i-1])-(sum[j-1][i+k-1]-sum[j-1][i-1]);
			}
			ll tmp=max({s1,s2,s3,s4});
			Max(p1[j+k-1],tmp),Max(q1[j],tmp);
			Max(p2[i+k-1],tmp),Max(q2[i],tmp);
			Max(p3[i+j+k-1],s1),Max(p3[i+k-1+j+k-1],max({s2,s3,s4})),Max(q3[i+j+k-1],s2),Max(q3[i+j],max({s1,s3,s4}));
			Max(p4[i-j+m],s3),Max(p4[i+k-1-j+m],max({s1,s2,s4})),Max(q4[i-j+m],s4),Max(q4[i-j-k+1+m],max({s1,s2,s3}));
		}
	}
	for(int i=1;i<=3000;i++) Max(p1[i],p1[i-1]),Max(p2[i],p2[i-1]),Max(p3[i],p3[i-1]),Max(p4[i],p4[i-1]);
	for(int i=2999;i>=1;i--) Max(q1[i],q1[i+1]),Max(q2[i],q2[i+1]),Max(q3[i],q3[i+1]),Max(q4[i],q4[i+1]);
	ll res=-1e18;
	for(int i=1;i<3000;i++) Max(res,max({p1[i]+q1[i+1],p2[i]+q2[i+1],p3[i]+q3[i+1],p4[i]+q4[i+1]}));
	cout<<res<<"\n";
	return 0;
}