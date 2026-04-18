#include <bits/stdc++.h>
using namespace std;
vector<int>res[1000005];
int check(int n,int m,int g){
	if(n<m) return 1;
	if(g>=1){
		int tmp=n-(res[m][g]-1);
		if(tmp<=m){
			if(res[m][g]-res[m][g-1]==m+1&&tmp==m) return 1;
			if(res[m][g]-res[m][g-1]==m+2&&tmp==(m+1)/2) return 1;
		}
	}
	if((res[m][g]+n)%2==0){
		if(!check((res[m][g]+n)/2,m,g)) return 1;
	}
	if(g>=1&&(res[m][g-1]+n)%2==0&&n-(res[m][g-1]+n)/2<=m){
		if(!check((res[m][g-1]+n)/2,m,g-1)) return 1;
	}
	return 0;
}
int n,m;
void solve(){
	cin>>n>>m;
	if(m%2==0){
		if(n%(m+1)==0) cout<<"NO\n";
		else cout<<"YES\n";
	}
	else{
		if((*lower_bound(res[m].begin(),res[m].end(),n))==n) cout<<"NO\n";
		else cout<<"YES\n";
	}
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	for(int m=3;m<=1000000;m+=2){
		res[m].emplace_back(0),res[m].emplace_back(m+1);
		while(res[m].back()<1000000) res[m].emplace_back(res[m].back()+m+1+check(res[m].back()+m+1,m,res[m].size()-1));
	}
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}