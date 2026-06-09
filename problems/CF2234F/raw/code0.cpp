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
int n;
ll a[200005],pre[200005],suf[200005];
int st[200005],top;
void solve(int Ca){
	cin>>n;
	ll ma=-1,mak=0;
	for(int i=0;i<n;i++){
		cin>>a[i];
		if(a[i]>ma) ma=a[i],mak=i;
	}
	top=0,st[0]=mak,pre[mak]=suf[mak]=0;
	ll now=0;
	for(int j=1,i=(mak+1)%n;j<n;j++,i=(i+1)%n){
		while(top&&a[st[top]]<a[i]) now-=1ll*(st[top]-st[top-1]+n)%n*a[st[top]],top--;
		st[++top]=i,now+=1ll*(st[top]-st[top-1]+n)%n*a[i],pre[i]=now;
	}
	now=0,top=0,st[0]=mak;
	for(int j=1,i=(mak-1+n)%n;j<n;j++,i=(i-1+n)%n){
		while(top&&a[st[top]]<a[i]) now-=1ll*(st[top-1]-st[top]+n)%n*a[st[top]],top--;
		st[++top]=i,now+=1ll*(st[top-1]-st[top]+n)%n*a[i],suf[i]=now;
	}
	for(int i=0;i<n;i++) cout<<suf[i]+pre[(i-1+n)%n]<<" \n"[i==n-1];
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