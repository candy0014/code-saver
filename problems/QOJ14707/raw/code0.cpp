#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
const ll mod=1e9+7;
const ll inf=2e9;
const int N=2e5+5;
const int M=2e5+5;
const int V=2e6+5;
int n,v,k,R;
int m;
ll val[10],c[10];
struct MAT{
	ll a[64][64];
	MAT operator*(const MAT &rs)const{
		MAT res;
		for(int i=0;i<m;i++) for(int j=0;j<m;j++){
			res.a[i][j]=-1e18;
			for(int k=0;k<m;k++) res.a[i][j]=max(res.a[i][j],a[i][k]+rs.a[k][j]);
		}
		return res;
	}
}base;
MAT ksm(MAT u,int v){
	MAT res=u;v--;
	while(v){
		if(v&1) res=res*u;
		u=u*u,v>>=1;
	}
	return res;
}
void solve(int Ca){
	cin>>n>>v>>k>>R;m=1<<n;
	for(int i=0;i<n;i++) cin>>val[i]>>c[i];
	for(int i=0;i<m;i++) for(int j=0;j<m;j++){
		ll sum=0,cc=0;
		for(int k=0;k<n;k++) if((j>>k)&1) sum+=val[k],cc+=c[k];
		cc+=__builtin_popcount(j&i)*k;
		if(cc<=v) base.a[i][j]=sum;
		else base.a[i][j]=-1e18;
	}
	MAT res=ksm(base,R);
	ll ma=0;
	for(int i=0;i<m;i++) ma=max(ma,res.a[0][i]);
	cout<<ma<<"\n";
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
	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}