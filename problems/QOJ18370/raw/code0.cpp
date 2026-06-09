#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=1e16+2137;
ll h[100005],pw[100005],ha[200005],n;
string s;
ll get(int l,int r){
	return (ha[l]-(__int128)ha[r+1]*pw[r-l+1]%mod+mod)%mod;
}
bool check(int len){
	int c=n/len+1;
	ll sum=0,g=0;
	int d=min(len,10);
	for(int i=0;i<c;i++){
		int l=i*len,r=l+len-1;
		sum=(sum+get(l,r))%mod,g+=get(r-d+1,r);
	}
	ll de=g/h[d];
	for(int i=-2;i<=2;i++) if((__int128)(de+i)*h[len]%mod==sum) return 1;
	return 0;
}
void solve(){
	cin>>s;reverse(s.begin(),s.end()),n=s.length();
	for(int i=1;i<=n;i++) s+='0';
	ha[s.length()]=0;
	for(int i=s.length()-1;i>=0;i--) ha[i]=(ha[i+1]*10+s[i]-'0')%mod;
	for(int i=n;i>=1;i--) if(check(i)){cout<<i<<"\n";return;}
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	h[1]=1,pw[0]=1,pw[1]=10;
	for(int i=2;i<=100000;i++) h[i]=(h[i-1]*10+1)%mod,pw[i]=pw[i-1]*10%mod;
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}