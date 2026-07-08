#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,k,du[100005];
mt19937 rd(time(0));
void solve(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) du[i]=0;
	for(int i=1,u,d;i<=k/2-1;i++){
		cin>>u>>d;
		if(!du[u]) du[u]=-d;
		cout<<"W"<<endl;
		cin>>u>>d,du[u]=d;
		cout<<"T "<<rd()%n+1<<endl;
	}
	int a;cin>>a>>a;
	ll sum1=0,sum2=0,cnt1=0,cnt2=0;
	for(int i=1;i<=n;i++){
		if(du[i]>0) sum1+=du[i],cnt1++;
		if(du[i]<0) sum2-=du[i],cnt2++;
	}
	cout<<"E "<<(ll)(sum1+(!cnt2?0:(1.0*sum2*(n-cnt1)/cnt2)))/2<<endl;
}
int main(){
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}