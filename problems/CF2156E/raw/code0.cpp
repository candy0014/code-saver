#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
const ll mod=998244353;
const ll inf=2e9;
const int N=2e5+5;
const int M=2e5+5;
const int V=2e6+5;
int n,a[100005],du[100005];
vector<int>e[100005];
int F(int x,int y){
	if(x>y) swap(x,y);
	return a[y]-a[x];
}
bool check(int x){
	int cnt2=0,cnt3=0,la=0;
	for(int i=1;i<=n;i++){
		du[i]=(F(i,e[i][0])>x)+(F(i,e[i][1])>x)+(F(i,e[i][2])>x);
		if(du[i]==2) cnt2++;
		if(du[i]==3) cnt3++,la=i;
	}
	if(cnt3>=2) return 0;
	if(cnt3==1){
		for(int i=1;i<=n;i++) if(i!=la&&F(i,la)>x&&du[i]==2) cnt2--;
		return !cnt2;
	}
	if(!cnt2) return 1;
	for(int i=1;i<=n;i++) if(du[i]==2&&(du[e[i][0]]==2)+(du[e[i][1]]==2)==cnt2-1) return 1;
	return 0;
}
void solve(int Ca){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],e[i].clear();
	int pos[4]={0,0,0,0};
	for(int i=2;i<=n;i++){
		pos[3]=i-1;
		for(int j=3;j>=1;j--) if(!pos[j-1]||a[pos[j]]<a[pos[j-1]]) swap(pos[j],pos[j-1]);
		for(int j=0;j<3;j++) if(pos[j]) e[i].emplace_back(pos[j]);
	}
	pos[0]=pos[1]=pos[2]=0;
	for(int i=n-1;i>=1;i--){
		pos[3]=i+1;
		for(int j=3;j>=1;j--) if(!pos[j-1]||a[pos[j]]>a[pos[j-1]]) swap(pos[j],pos[j-1]);
		for(int j=0;j<3;j++) if(pos[j]) e[i].emplace_back(pos[j]);
	}
	for(int i=1;i<=n;i++) sort(e[i].begin(),e[i].end(),[&](int u,int v){return F(u,i)>F(v,i);});
	int l=-1e9,r=1e9,mid,res=0;
	while(l<=r){
		mid=l+(r-l)/2;
		if(check(mid)) res=mid,r=mid-1;
		else l=mid+1;
	}
	cout<<res<<"\n";
}
int main(){
	#ifdef ONLINE_JUDGE
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	#endif
	#ifndef ONLINE_JUDGE
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	
	int Ca=1;
	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}