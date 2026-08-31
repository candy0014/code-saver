#include <bits/stdc++.h>
using namespace std;
string s;
int n,la[26],mi[3000005][22],res;
int query(int l,int r){
	if(!r) return 0;
	int t=__lg(r-l+1);
	return min(mi[l][t],mi[r-(1<<t)+1][t]);
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>s,n=s.length(),s=" "+s;
	for(int i=n;i>=1;i--){
		mi[i][0]=query(i+1,la[s[i]-'a'])+1,la[s[i]-'a']=i,res=max(res,mi[i][0]);
		for(int j=1;i+(1<<j)-1<=n;j++) mi[i][j]=min(mi[i][j-1],mi[i+(1<<(j-1))][j-1]);
	}
	cout<<res<<"\n";
	return 0;
}