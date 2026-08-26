#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
const ll mod=(ll)1e16+2137,base=233;
const ll inf=2e9;
const int N=2e5+5;
const int M=2e5+5;
const int V=2e6+5;
int n,ca,m,k;
ll pw[60005];
struct node{
	string s;
	ll ha[60005];
	ll get(int l,int r){
		return (ha[r]-(__int128)ha[l-1]*pw[r-l+1]%mod+mod)%mod;
	}
	void init(){
		cin>>s,s=" "+s;
		for(int i=1;i<=m;i++) ha[i]=(ha[i-1]*base+s[i])%mod;
	}
}s[305],t;
void solve(int Ca){
	cin>>n>>ca>>m>>k;
	pw[0]=1;
	for(int i=1;i<=m;i++) pw[i]=pw[i-1]*base%mod;
	for(int i=1;i<=n;i++) s[i].init();
	while(ca--){
		t.init();
		int res=0;
		for(int c=1;c<=n;c++){
			int now=0,cnt=0;
			while(now<m&&cnt<=k){
				int l=now+1,r=m,mid,res=m+1;
				while(l<=r){
					mid=(l+r)>>1;
					if(s[c].get(now+1,mid)!=t.get(now+1,mid)) res=mid,r=mid-1;
					else l=mid+1;
				}
				if(res!=m+1) cnt++;
				now=res;
			}
			res+=cnt<=k;
		}
		cout<<res<<"\n";
	}
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
//	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}