#include <bits/stdc++.h>
using namespace std;
int n,c[2005],d[2005];
string s[2005];
void work(int x){
	for(int i=0;i<n;i++) if(i!=x){
		if(s[i][x]=='0') s[i][x]='1',c[i]++;
		else s[i][x]='0',c[i]--;
		if(s[x][i]=='0') s[x][i]='1',c[x]++;
		else s[x][i]='0',c[x]--;
	}
}
bool check(vector<int>p){
	for(auto x:p) work(x);
	for(int i=0;i<n;i++) d[i]=c[i];
	sort(d,d+n);
	int flag=1;
	for(int i=0,sum=0;i<n-1;i++){
		sum+=d[i];
		if(sum==i*(i+1)/2){flag=0;break;}
	}
	for(auto x:p) work(x);
	return flag;
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=0;i<n;i++) cin>>s[i];
	for(int i=0;i<n;i++) for(int j=0;j<n;j++) c[i]+=s[i][j]-'0';
	if(check({})){cout<<"0 1\n";return 0;}
	if(n<=6){
		int mi=1e9,cnt=0;
		for(int i=0;i<(1<<n);i++){
			vector<int>p;
			for(int j=0;j<n;j++) if((i>>j)&1) p.emplace_back(j);
			if(check(p)){
				if(p.size()<mi) mi=p.size(),cnt=0;
				if(p.size()==mi) cnt++;
			}
		}
		if(!cnt) cout<<"-1\n";
		else{
			for(int i=1;i<=mi;i++) cnt*=i;
			cout<<mi<<" "<<cnt<<"\n";
		}
	}
	else{
		int cnt=0;
		for(int i=0;i<n;i++) cnt+=check({i});
		cout<<"1 "<<cnt<<"\n";
	}
	return 0;
}