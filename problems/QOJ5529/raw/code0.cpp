#include <bits/stdc++.h>
#include <cassert>
using namespace std;
int n,k;
int F(int x){return x*(x-1)/2-(x!=3)*(x-1)/2;}
namespace solve1{
	int a[15],s[15][15];
	int calc(int n){
		for(int i=1;i<=n;i++) for(int j=i+1;j<=n;j++) s[i][j]=a[i]>a[j];
		for(int i=n-1;i>=1;i--) for(int j=i+1;j<=n;j++) s[i][j]^=s[i][j-1]^s[i+1][j]^s[i+1][j-1];
		int res=0;
		for(int i=1;i<=n;i++) for(int j=i+1;j<=n;j++) res+=s[i][j];
		return res;
	}
	vector<int> solve(int n,int k){
		for(int i=1;i<=n;i++) a[i]=i;
		do{
			int t=calc(n);
			if(t!=k) continue;
			vector<int>res;
			for(int i=1;i<=n;i++) res.emplace_back(a[i]);
			return res;
		}while(next_permutation(a+1,a+n+1));
		return {};
	}
}
namespace solve3{
	vector<int> solve(int n,int k){
		vector<int>res;
		if(k==0){
			for(int i=1;i<=n;i++) res.emplace_back(i);
		}
		else{
			for(int i=1;i<=n-k-2;i++) res.emplace_back(i);
			res.emplace_back(n-k);
			res.emplace_back(n-k+1);
			res.emplace_back(n-k-1);
			for(int i=n-k+2;i<=n;i++) res.emplace_back(i);
		}
		return res;
	}
}
namespace solve2{
	int res[1005];
	vector<int> solve(int n){
		if(n==1) return {1};
		if(n==3) return {3,2,1};
		res[1]=2,res[2]=1;
		for(int i=4;i<=n;i+=2) res[i-3]++,res[i-1]=i,res[i]=i-2;
		if(n&1) res[n]=n;
		vector<int>ress;
		for(int i=1;i<=n;i++) ress.emplace_back(res[i]);
		return ress;
	}
}
int s[1005][1005];
vector<int> solve(int n,int k){
	if(n<=6) return solve1::solve(n,k);
	if(k<=n-2) return solve3::solve(n,k);
	if(k==F(n)) return solve2::solve(n);
	if(k-(n-1)<=F(n-2)){
		vector<int>res=solve(n-2,k-(n-1));
		res.emplace_back(n),res.emplace_back(n-1);
		return res;
	}
	vector<int>res=solve2::solve(n-2);
	k-=F(n-2);
	for(int i=0;i<n-2;i++) for(int j=i+1;j<n-2;j++) s[i][j]=(res[i]>res[j]);
	for(int i=n-3;i>=0;i--) for(int j=i+1;j<=n;j++) s[i][j]^=s[i+1][j]^s[i][j-1]^s[i+1][j-1];
	vector<int>pre(n+1),suf(n+1);
	for(int i=1;i<n;i++) for(int j=0,cnt=0;j<n-2;j++) cnt^=(res[j]<i),pre[i]+=s[0][j]^cnt;
	for(int i=1;i<n;i++) for(int j=n-3,cnt=0;j>=0;j--) cnt^=(res[j]>=i),suf[i]+=s[j][n-3]^cnt;
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if(i!=j){
		if(i<j){
			if(pre[i]+suf[j-1]+(s[0][n-3]^((i-1)&1)^((n-j)&1))!=k) continue;
		}
		else{
			if(pre[i-1]+suf[j]+(s[0][n-3]^(i&1)^((n-j+1)&1)^1)!=k) continue;
		}
		vector<int>ress;
		ress.emplace_back(i);
		for(int x=0;x<n-2;x++) ress.emplace_back(res[x]+(res[x]>=min(i,j))+(res[x]+(res[x]>=min(i,j))>=max(i,j)));
		ress.emplace_back(j);
		return ress;
	}
	return {};
}
void solve(){
	cin>>n>>k;
	if(k>F(n)){cout<<"NO\n";return;}
	cout<<"YES\n";
	vector<int>res=solve(n,k);
	for(auto x:res) cout<<x<<" ";cout<<"\n";
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}