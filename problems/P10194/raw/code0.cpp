#include <bits/stdc++.h>
using namespace std;
typedef long long ll;//不开 long long 见祖宗
const ll N=5e5+5;
ll n,a[N<<1];
ll pre[N],nex[N];
ll mi=1e9,mik;
ll st[N],r;
ll p[N];//差分数组
void change(ll l,ll r,ll x,ll d){//将从 l 到 r 的数加上以 x 为首项，d 为公差的等差数列
	if(l>r) return;
	ll y=x+(r-l)*d;
	p[l]+=x,p[l+1]-=x;
	p[l+1]+=d,p[r+1]-=d;
	p[r+1]-=y,p[r+2]+=y;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	cin>>n;
	for(ll i=1;i<=n;i++){
		cin>>a[i],a[i+n]=a[i];
		if(mi>a[i]) mi=a[i],mik=i;
	}
	for(ll i=1;i<=n;i++) a[i]=a[i+mik-1];//将最小值移到第一个

	r=0,st[r]=1;//单调栈求 pre 数组
	for(ll i=2;i<=n;i++){
		while(r>=1&&a[st[r]]>a[i]) r--;
		pre[i]=st[r],st[++r]=i;
	}
	r=0,st[r]=n+1;//单调栈求 nex 数组
	for(ll i=n;i>=2;i--){
		while(r>=1&&a[st[r]]>=a[i]) r--;
		nex[i]=st[r],st[++r]=i;
	}

	change(1,n,a[1],a[1]);
	for(ll i=2;i<=n;i++){
		ll A=i-pre[i],D=nex[i]-i;//平行四边形的底为 A，高为 D
		if(A<=D){//分类讨论
			change(1,A-1,a[i],a[i]);
			change(A,D,a[i]*A,0);
			change(D+1,A+D-1,a[i]*(A-1),-a[i]);
		}
		else{
			change(1,D,a[i],a[i]);
			change(D+1,A-1,a[i]*D,0);
			change(A,A+D-1,a[i]*D,-a[i]);
		}
	}

	for(ll i=1;i<=n;i++) p[i]+=p[i-1];//做两次前缀和还原数组
	for(ll i=1;i<=n;i++) p[i]+=p[i-1];
	for(ll i=2;i<=n;i++) cout<<p[i]<<"\n";
	cout<<p[n]<<"\n";//n 次操作后的结果和 n-1 次操作的结果相同
	return 0;
}