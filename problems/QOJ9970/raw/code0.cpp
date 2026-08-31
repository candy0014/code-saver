#include <bits/stdc++.h>
#include <cassert>
using namespace std;
typedef long long ll;
const ll mod=(ll)1e16+2137,base=233;
ll pw[2000005],ha[2000005];
ll Hash(int l,int r){return (ha[r]-(__int128)ha[l-1]*pw[r-l+1]%mod+mod)%mod;}
int n;
string s[100005];
int son[2000005][3],tot,cnt[2000005],cntt[2000005];
int h[2000005][3];
string str,t;
int pp[2000005];
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	pw[0]=1;
	for(int i=1;i<=2000000;i++) pw[i]=pw[i-1]*base%mod;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>t;
		for(int j=0;t[j];j++){
			if(t[j]=='K') s[i]+='a';
			if(t[j]=='P') s[i]+='b';
			if(t[j]=='N') s[i]+='c';
		}
	}
	sort(s+1,s+n+1,[&](const string &a,const string &b){return a.length()<b.length();});
	ll res=0;
	for(int i=1;i<=n;i++){
		str=s[i]+s[i];
		int len=str.length();
		for(int j=1;j<=len;j++) ha[j]=(ha[j-1]*base+str[j-1])%mod;
		for(int j=0;j<=len;j++) h[j][0]=h[j][1]=h[j][2]=0;
		int now=0;
		for(int j=0;j<len;j++){
			pp[j]=now;
			int x=str[j]-'a';
			ll tmp=1;
			for(int k=0;k<3;k++) if(k!=x) tmp*=(cnt[son[now][k]]+h[j][k]);
			res+=tmp;
			if(!son[now][x]) son[now][x]=++tot;
			now=son[now][x];
			ll g=Hash(1,j+1);
			for(int l=j+2,r=l+j;l<=len;l+=j+1,r+=j+1){
				if(r>len) r=len,g=Hash(1,r-l+1);
				if(Hash(l,r)==g) continue;
				int _l=l,_r=r,mid,res;
				while(_l<=_r){
					mid=(_l+_r)>>1;
					if(Hash(l,mid)==Hash(1,mid-l+1)) _l=mid+1;
					else res=mid,_r=mid-1;
				}
				h[res-1][str[res-l]-'a']+=cntt[now];
				break;
			}
			if(j<len/2) cnt[now]++;
			if(j==len/2-1) cntt[now]++;
		}
	}
	cout<<res<<"\n";
	return 0;
}