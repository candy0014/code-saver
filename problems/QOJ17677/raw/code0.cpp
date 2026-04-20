#include <bits/stdc++.h>
using namespace std;
vector<int>e[505];
int n,w[505][505],res[505][505],d[505][505];
queue<int>q;
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++){
		e[i].clear();
		for(int j=i+1;j<=n;j++) cin>>w[i][j],w[j][i]=w[i][j];
	}
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) res[i][j]=0;
	for(int i=1;i<=n;i++) for(int j=2;j<=n;j++) if(w[i][j]==1){
		int flag=1;
		for(int k=1;k<=n;k++) if(w[i][k]!=w[j][k]&&w[i][k]!=(w[j][k]+1)%5&&w[j][k]!=(w[i][k]+1)%5){flag=0;break;}
		if(flag) res[i][j]=res[j][i]=1;
	}
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++){
		if(i==j) d[i][j]=0;
		else if(res[i][j]) d[i][j]=1;
		else d[i][j]=1000;
	}
	for(int k=1;k<=n;k++) for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if(d[i][j]>=1000||d[i][j]%5!=w[i][j]){cout<<"NO\n";return;}
	cout<<"YES\n";
	for(int i=1;i<n;i++,cout<<"\n") for(int j=i+1;j<=n;j++) cout<<res[i][j]<<" ";
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}