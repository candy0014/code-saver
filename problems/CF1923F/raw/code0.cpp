#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=1e16+2137,base=233;
ll pw[500005],ha[500005];
int n,k,cnt[2][500005];
string s,str,h,w;
ll Hash(int l,int r){
	return (ha[r]-(__int128)ha[l-1]*pw[r-l+1]%mod+mod)%mod;
}
struct node{
	int l,r,cnt;
	bool operator<(const node &rs)const{
		if(r-l+cnt!=rs.r-rs.l+rs.cnt) return r-l+cnt<rs.r-rs.l+rs.cnt;
		int _l=1,_r=min(r-l+1,rs.r-rs.l+1),mid,res=0;
		while(_l<=_r){
			mid=(_l+_r)>>1;
			if(Hash(r-mid+1,r)==Hash(rs.r-mid+1,rs.r)) res=mid,_l=mid+1;
			else _r=mid-1;
		}
		if(res==min(r-l+1,rs.r-rs.l+1)) return r-l>rs.r-rs.l;
		return s[r-res]<s[rs.r-res];
	}
};
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>k>>s,s=" "+s,str=s;
	pw[0]=1;
	for(int i=1;i<=n;i++) pw[i]=pw[i-1]*base%mod,ha[i]=(ha[i-1]*base+s[i])%mod;
	for(int i=1;i<=n;i++) cnt[0][i]=cnt[0][i-1],cnt[1][i]=cnt[1][i-1],cnt[s[i]-'0'][i]++;
	if(cnt[1][n]==0){cout<<"0\n";return 0;}
	vector<int>p;
	for(int i=n;i>=1;i--) if(s[i]=='1') p.emplace_back(i);
	int tmp=k;
	for(int i=n;i>=1;i--){
		if(str[i]=='1') h+='1';
		else if(tmp&&p.size()&&p.back()<i) str[p.back()]='0',p.pop_back(),h+='1',tmp--;
		else h+='0';
	}
	while(h.back()=='0') h.pop_back();
	reverse(h.begin(),h.end());
	k--;
	node mi={0,(int)1e9,0};
	for(int i=1;i<=n;i++){
		if(cnt[1][i-1]>k) break;
		int l=i,r=n,mid,pos=0;
		while(l<=r){
			mid=(l+r)>>1;
			if(cnt[0][mid]-cnt[0][i-1]<=min(k,cnt[1][i-1]+cnt[1][n]-cnt[1][mid])) pos=mid,l=mid+1;
			else r=mid-1;
		}
		if(cnt[0][pos]-cnt[0][i-1]<cnt[1][i-1]) continue;
		int g=cnt[0][pos]-cnt[0][i-1],pos2=0;
		l=pos,r=n;
		while(l<=r){
			mid=(l+r)>>1;
			if(cnt[1][i-1]+cnt[1][n]-cnt[1][mid]<=g) r=mid-1,pos2=mid;
			else l=mid+1;
		}
		if(node{pos+1,pos2,pos-i+1}<mi) mi=node{pos+1,pos2,pos-i+1};
	}
	for(int i=mi.r;i>=mi.l;i--) w+=s[i];
	for(int i=1;i<=mi.cnt;i++) w+='1';
	if(h.length()>w.length()||(h.length()==w.length()&&w<h)) h=w;
	int ans=0;
	for(int i=0;h[i];i++) ans=(ans*2+h[i]-'0')%1000000007;
	cout<<ans<<"\n";
	return 0;
}