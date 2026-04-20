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
const int lim=400;
int n,ca;
ll a[150005],res[150005],ress[150005];
struct node{int l,r,x,id;}s[150005];
void solve(int Ca){
	cin>>n>>ca;
	for(int i=1;i<=n;i++) cin>>a[i],a[i]+=a[i-1];
	for(int i=1;i<=ca;i++) cin>>s[i].l>>s[i].r>>s[i].x,s[i].id=i,res[i]=ress[i]=0;
	sort(s+1,s+ca+1,[&](node u,node v){return u.x>v.x;});
	for(int i=1;i<=lim;i++){
		for(int j=1,k=i-1;j<=ca;j++){
			while(k<n&&a[k+1]-a[k+1-i]>=s[j].x) k++;
			if(s[j].l+i-1<=min(k,s[j].r)){
				int tmp=(min(k,s[j].r)-s[j].l+1)/i;
				s[j].l+=tmp*i,res[s[j].id]+=tmp;
			}
		}
	}
	for(int i=1;i<=ca;i++){
		while(1){
			int it=lower_bound(a+s[i].l,a+s[i].r+1,a[s[i].l-1]+s[i].x)-a;
			if(it>s[i].r) break;
			s[i].l=it+1,res[s[i].id]++;
		}
		ress[s[i].id]=a[s[i].r]-a[s[i].l-1];
	}
	for(int i=1;i<=ca;i++) cout<<res[i]<<" "<<ress[i]<<"\n";
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