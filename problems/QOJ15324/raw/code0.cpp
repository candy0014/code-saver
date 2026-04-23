#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int len=400;
int n,ca,th[200005],st[200005],ed[200005];
ll a[200005];
ll tag1[200005],tag2[200005],tmi[200005],tma[200005];
ull sres[200005],smi[200005],sma[200005];
void reset(int x){
	if(tag1[x]!=1e18) for(int i=st[x];i<=ed[x];i++) a[i]=tag1[x];
	else for(int i=st[x];i<=ed[x];i++) a[i]+=tag2[x];
	tag1[x]=1e18,tag2[x]=0;
}
void rebuild(int x){
	ll mi=1e18,ma=-1e18;
	ull ssmi=0,ssma=0,ssres=0;
	for(int i=st[x];i<=ed[x];i++){
		mi=min(mi,a[i]),ma=max(ma,a[i]);
		tmi[i]=-mi,tma[i]=ma;
	}
	for(int i=ed[x];i>=st[x];i--){
		ssmi-=tmi[i],ssma+=tma[i],ssres-=1ull*tmi[i]*tma[i];
		smi[i]=ssmi,sma[i]=ssma,sres[i]=ssres;
	}
	tag1[x]=1e18,tag2[x]=0;
}
void update(int x,ll t1,ll t2){
	if(t1!=1e18) tag1[x]=t1,tag2[x]=0;
	else if(tag1[x]!=1e18) tag1[x]+=t2;
	else tag2[x]+=t2;
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>ca;
	for(int i=1;i<=n;i++){
		cin>>a[i],th[i]=(i-1)/len+1,ed[th[i]]=i;
		if(th[i]!=th[i-1]) st[th[i]]=i;
	}
	for(int i=1;i<=th[n];i++) rebuild(i);
	while(ca--){
		int op,l,r,x;
		cin>>op>>l>>r;
		if(op==1||op==2){
			cin>>x;
			ll t1=1e18,t2=0;
			if(op==1) t2=x;
			else t1=x;
			if(th[l]==th[r]){
				reset(th[l]);
				if(op==1) for(int i=l;i<=r;i++) a[i]+=x;
				else for(int i=l;i<=r;i++) a[i]=x;
				rebuild(th[l]);
			}
			else{
				reset(th[l]),reset(th[r]);
				if(op==1){
					for(int i=l;i<=ed[th[l]];i++) a[i]+=x;
					for(int i=st[th[r]];i<=r;i++) a[i]+=x;
				}
				else{
					for(int i=l;i<=ed[th[l]];i++) a[i]=x;
					for(int i=st[th[r]];i<=r;i++) a[i]=x;
				}
				rebuild(th[l]),rebuild(th[r]);
				for(int i=th[l]+1;i<th[r];i++) update(i,t1,t2);
			}
		}
		else{
			if(th[l]==th[r]){
				reset(th[l]),rebuild(th[l]);
				ll mi=1e18,ma=-1e18;ull res=0;
				for(int i=l;i<=r;i++) mi=min(mi,a[i]),ma=max(ma,a[i]),res+=1ull*mi*ma;
				cout<<res<<"\n";
			}
			else{
				reset(th[l]),rebuild(th[l]),reset(th[r]),rebuild(th[r]);
				ll mi=1e18,ma=-1e18;ull res=0;
				for(int i=l;i<=ed[th[l]];i++) mi=min(mi,a[i]),ma=max(ma,a[i]),res+=1ull*mi*ma;
				for(int i=th[l]+1;i<th[r];i++){
					if(tag1[i]!=1e18){
						mi=min(mi,tag1[i]),ma=max(ma,tag1[i]),res+=1ull*mi*ma*(ed[i]-st[i]+1);
						continue;
					}
					ll t=tag2[i];
					int pos1=lower_bound(tma+st[i],tma+ed[i]+1,ma-t)-tma;
					int pos2=lower_bound(tmi+st[i],tmi+ed[i]+1,-(mi-t))-tmi,pos=max(pos1,pos2);
					res+=1ull*mi*ma*(min(pos1,pos2)-st[i]);
					if(pos<=ed[i]) res+=sres[pos]+t*sma[pos]+t*smi[pos]+1ull*t*t*(ed[i]-pos+1);
					if(pos1<pos2){
						ull tmp=sma[pos1];
						if(pos2<=ed[i]) tmp-=sma[pos2];
						res+=1ull*mi*(tmp+1ull*t*(pos2-pos1));
					}
					if(pos1>pos2){
						ull tmp=smi[pos2];
						if(pos1<=ed[i]) tmp-=smi[pos1];
						res+=1ull*ma*(tmp+1ull*t*(pos1-pos2));
					}
					mi=min(mi,-tmi[ed[i]]+t),ma=max(ma,tma[ed[i]]+t);
				}
				for(int i=st[th[r]];i<=r;i++) mi=min(mi,a[i]),ma=max(ma,a[i]),res+=1ull*mi*ma;
				cout<<res<<"\n";
			}
		}
	}
	return 0;
}