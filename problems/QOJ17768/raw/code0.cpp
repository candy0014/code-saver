#include <bits/stdc++.h>
using namespace std;
int n,m,a[5000005];
int mp[100000005];
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	int g=__lg(m),tot=0;
	while(n--){
		cin>>a[++tot];
		if(mp[a[tot]>>g]||(mp[(a[tot]>>g)^1]&&(mp[(a[tot]>>g)^1]^a[tot])<m)){
			cout<<"Y";
			for(int i=1;i<tot;i++) mp[a[i]>>g]=0;
			tot=0;
		}
		else cout<<"N",mp[a[tot]>>g]=a[tot];
	}
	return 0;
}
