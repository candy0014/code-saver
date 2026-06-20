#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m1,m2;
vector<pair<int,pair<int,int> > > p;
pair<int,int> q[2005];
ll val[2005][2005];
ll f[2005][4005],dp[2005];
int calc(int x,int y,int xx,int yy){return max(0,min(yy,y-abs(xx-x)));}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>m1>>m2>>n;
	for(int i=1,x,f,h;i<=m1;i++) cin>>x>>f>>h,p.emplace_back(x,make_pair(h,f));
	for(int i=1,x,f,h;i<=m2;i++) cin>>x>>f>>h,p.emplace_back(x,make_pair(h,-f));
	for(int i=1;i<=n;i++) cin>>q[i].first>>q[i].second;q[++n]=make_pair(0,2e6),q[++n]=make_pair(1e6+1,4e6);
	sort(p.begin(),p.end()),sort(q+1,q+n+1);
	for(int i=1;i<=n;i++){
		int t=lower_bound(p.begin(),p.end(),make_pair(q[i].first,make_pair(0,0)))-p.begin();
		for(int j=t;j<(int)p.size();j++){
			if(j!=t) f[i][j]=f[i][j-1];
			f[i][j]+=1ll*calc(q[i].first,q[i].second,p[j].first,p[j].second.first)*p[j].second.second;
		}
		for(int j=t-1;j>=0;j--){
			if(j!=t-1) f[i][j]=f[i][j+1];
			f[i][j]+=1ll*calc(q[i].first,q[i].second,p[j].first,p[j].second.first)*p[j].second.second;
		}
	}
	for(int i=1;i<n;i++) for(int j=i+1;j<=n;j++){
		int g,len=q[j].first-q[i].first;
		if(abs(q[i].second-q[j].second)>=len){
			if(i==1&&j==n) continue;
			if(i==1){
				if(p[0].first<q[j].first) val[i][j]=f[j][0];
				continue;
			}
			if(j==n){
				if(p.back().first>=q[i].first) val[i][j]=f[i][p.size()-1];
				continue;
			}
			val[i][j]=-1e18;
			continue;
		}
		if(len>=q[i].second+q[j].second) g=q[i].first+q[i].second;
		else g=(q[i].first+q[j].first+q[i].second-q[j].second)/2;
		g=lower_bound(p.begin(),p.end(),make_pair(g+1,make_pair(0,0)))-p.begin();
		if(g<(int)p.size()&&p[g].first<q[j].first) val[i][j]+=f[j][g];
		if(g>=1&&p[g-1].first>=q[i].first) val[i][j]+=f[i][g-1];
	}
	for(int i=2;i<=n;i++){
		dp[i]=-1e18;
		for(int j=1;j<i;j++) dp[i]=max(dp[i],dp[j]+val[j][i]);
	}
	cout<<dp[n]<<"\n";
	return 0;
}