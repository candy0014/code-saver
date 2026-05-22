#include <bits/stdc++.h>
using namespace std;
int n,cnt[105][105];
vector<int>f,t;
vector<vector<int> >ans;
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n,f.resize(n+1),t.resize(n+1);
	for(int i=1;i<=n;i++) for(int j=1,x;j<=n;j++) cin>>x,cnt[i][x]++,t[i-1]=x;
	while(1){
		int flag=0;
		for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if(cnt[i][j]^1){flag=i;break;}
		if(!flag) break;
		for(int j=1,i=flag;j<=n;j++,i=i%n+1){
			f[i]=t[i-1];
			for(int j=1;j<=n;j++) if(cnt[i][j]>=2){f[i]=j,flag=1;break;}
			cnt[i][f[i]]--,cnt[i%n+1][f[i]]++;
		}
		ans.emplace_back(f),swap(t,f),t[0]=t[n];
	}
	for(int i=n;i>=2;i--){
		for(int j=1;j<=n;j++) f[j]=(i+j-1)%n;
		for(int j=1;j<=n-i+1;j++) ans.emplace_back(f);
	}
	cout<<ans.size()<<"\n";
	for(auto x:ans){
		for(int i=1;i<=n;i++){
			if(!x[i]) x[i]=n;
			cout<<x[i]<<" \n"[i==n];
		}
	}
	return 0;	
}