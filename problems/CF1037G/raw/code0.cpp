#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
int n,ca;
string s;
vector<pair<int,int> >as[100005];
int pre[100005][26],nex[100005][26];
int presg[100005][26],nexsg[100005][26];
struct TREE{
	int sum[100005];
	void add(int x,int k){while(x<=n)sum[x]^=k,x+=(x&(-x));}
	int query(int x){int t=0;while(x)t^=sum[x],x-=(x&(-x));return t;}
	int query(int l,int r){return query(r)^query(l-1);}
}tr[26];
int query(int l,int r){
	ull vis=0;
	for(int t=0;t<26;t++){
		int pl=nex[l][t],pr=pre[r][t];
		if(pl>pr) continue;
		vis|=(1ull<<(tr[t].query(pl+1,pr)^nexsg[l][t]^presg[r][t]));
	}
	return __builtin_ctzll(~vis);
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	cin>>s>>ca,n=s.length(),s=" "+s+" ";
	for(int i=1;i<=n;i++){
		for(int j=0;j<26;j++) pre[i][j]=pre[i-1][j];
		pre[i][s[i]-'a']=i;
	}
	for(int j=0;j<26;j++) nex[n+1][j]=n+1;
	for(int i=n;i>=1;i--){
		for(int j=0;j<26;j++) nex[i][j]=nex[i+1][j];
		nex[i][s[i]-'a']=i;
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<26;j++){
			if(pre[i][j]) as[i-pre[i][j]].emplace_back(-i,j);
			if(nex[i][j]!=n+1) as[nex[i][j]-i].emplace_back(i,j);
		}
	}
	for(int i=1;i<=n;i++){
		for(auto [p,c]:as[i]){
			int op=1;
			if(p<0) op=0,p=-p;
			int res;
			if(!op) res=query(pre[p][c]+1,p);
			else res=query(p,nex[p][c]-1);
			if(!op){
				presg[p][c]=res;
				if(p<n&&s[p+1]-'a'==c) tr[c].add(p+1,res);
			}
			else nexsg[p][c]=res;
		}
	}
	while(ca--){
		int l,r;cin>>l>>r;
		if(query(l,r)) cout<<"Alice\n";
		else cout<<"Bob\n";
	}
	return 0;
}