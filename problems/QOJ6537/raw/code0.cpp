#include <bits/stdc++.h>
using namespace std;
int n,a[600005],vis[600005];
vector<int>pos[3];
bool check(int x,int y,int op=0){
	for(int i=0;i<pos[1].size();i++) vis[i]=0;
	int i=pos[2].size()-x,_i=0,j=pos[0].size()-y,_j=0;
	int u=0,v=0;
	while(i<pos[2].size()||j<pos[0].size()){
		if(j==pos[0].size()||(i<pos[2].size()&&pos[0][j]>pos[2][i])){
			int l=pos[0][_i++],r=pos[2][i++];
			while(u<pos[1].size()&&(pos[1][u]<l||vis[u])) u++;
			if(u==pos[1].size()||pos[1][u]>r) return 0;
			vis[u]=1;
			if(op) cout<<l-1<<" "<<pos[1][u]-1<<" "<<r-1<<"\n";
		}
		else{
			int l=pos[2][_j++],r=pos[0][j++];
			while(v<pos[1].size()&&(pos[1][v]<l||vis[v])) v++;
			if(v==pos[1].size()||pos[1][v]>r) return 0;
			vis[v]=1;
			if(op) cout<<l-1<<" "<<pos[1][v]-1<<" "<<r-1<<"\n";
		}
	}
	return 1;
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],a[i]--,pos[a[i]].emplace_back(i);
	int l=1,r=min({pos[0].size(),pos[1].size(),pos[2].size()}),mid,res1=0,res2=0;
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid,0)) res1=mid,l=mid+1;
		else r=mid-1;
	}
	l=1,r=min({pos[0].size(),pos[1].size(),pos[2].size()})-res1;
	while(l<=r){
		mid=(l+r)>>1;
		if(check(res1,mid)) res2=mid,l=mid+1;
		else r=mid-1;
	}
	cout<<res1+res2<<"\n";
	check(res1,res2,1);
	return 0;
}
