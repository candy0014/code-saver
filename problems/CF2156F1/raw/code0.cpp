#include <bits/stdc++.h>
using namespace std;
int n,a[300005],b[300005];
void solve(){
	cin>>n;
	for(int i=1,u;i<=n;i++) cin>>u,a[u]=i;
	for(int i=1;i<=n;i++){
		int mik=0;
		for(int j=i,mi=a[i];j<=n;j++){
			mi=min(mi,a[j]);
			if(a[j]==mi&&(j-i)%2==0) mik=j; 
		}
		for(int j=mik;j>i;j--) swap(a[j],a[j-1]);
		b[a[i]]=i;
	}
	for(int i=1;i<=n;i++) cout<<b[i]<<" \n"[i==n];
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}