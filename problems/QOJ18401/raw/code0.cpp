#include <bits/stdc++.h>
using namespace std;
const int inf=1e9;
int n,m;
int a[300005],op[300005];
struct TREE{
	int mal[1200005],mar[1200005],mil[1200005],mir[1200005];
	int tag[1200005],tagl[1200005],tagr[1200005];
	void pushup(int p){
		mal[p]=max(mal[p*2],mal[p*2+1]);
		mar[p]=max(mar[p*2],mar[p*2+1]);
		mil[p]=min(mil[p*2],mil[p*2+1]);
		mir[p]=min(mir[p*2],mir[p*2+1]);
	}
	void update(int p,int t,int tl,int tr){
		if(tl!=inf) mal[p]=mil[p]=tl,tagl[p]=tl;
		if(tr!=inf) mar[p]=mir[p]=tr,tagr[p]=tr,tag[p]=0;
		mar[p]+=t,mir[p]+=t,tag[p]+=t;
	}
	void pushdown(int p){
		update(p*2,tag[p],tagl[p],tagr[p]),update(p*2+1,tag[p],tagl[p],tagr[p]);
		tag[p]=0,tagl[p]=tagr[p]=inf;
	}
	void build(int p,int l,int r){
		tag[p]=0,tagl[p]=tagr[p]=inf;
		if(l==r){
			mal[p]=mar[p]=mil[p]=mir[p]=-l;
			return;
		}
		int mid=(l+r)>>1;build(p*2,l,mid),build(p*2+1,mid+1,r),pushup(p);
	}
	int queryl(int p,int l,int r,int x){
		if(mar[p]<x) return l;
		if(mir[p]>=x) return m+1;
		int mid=(l+r)>>1;pushdown(p);return min(queryl(p*2,l,mid,x),queryl(p*2+1,mid+1,r,x));
	}
	int queryr(int p,int l,int r,int x){
		if(mil[p]>x) return r;
		if(mal[p]<=x) return -1;
		int mid=(l+r)>>1;pushdown(p);return max(queryr(p*2,l,mid,x),queryr(p*2+1,mid+1,r,x));
	}
	void changel(int p,int l,int r,int x){
		if(mil[p]>=x) return;
		if(mal[p]<=x){update(p,0,x,inf);return;}
		int mid=(l+r)>>1;pushdown(p);changel(p*2,l,mid,x),changel(p*2+1,mid+1,r,x),pushup(p);
	}
	void changer(int p,int l,int r,int x){
		if(mar[p]<=x) return;
		if(mir[p]>=x){update(p,0,inf,x);return;}
		int mid=(l+r)>>1;pushdown(p);changer(p*2,l,mid,x),changer(p*2+1,mid+1,r,x),pushup(p);
	}
	pair<int,int> query(int p,int l,int r,int x){
		if(l==r) return make_pair(mil[p],mir[p]);
		int mid=(l+r)>>1;pushdown(p);
		if(x<=mid) return query(p*2,l,mid,x);
		return query(p*2+1,mid+1,r,x);
	}
}tr;
int _l[300005],_r[300005];
string res;
void print(int sn){
	_l[0]=_r[0]=0;
	for(int i=1;i<n;i++){
		_l[i]=_l[i-1],_r[i]=_r[i-1]+1;
		if(op[i]==1){
			int x=a[i]+sn;
			if(x%2==0) x/=2;
			else x=(x+1)/2;
			_l[i]=max(_l[i],x);
		}
		else{
			int x=a[i]+sn;
			if(x%2==0) x/=2;
			else x=(x-1)/2;
			_r[i]=min(_r[i],x);
		}
	}
	res="";
	int now=sn;
	for(int i=n-1;i>=0;i--){
		if(_l[i]<=now&&now<=_r[i]) res+="<";
		else now--,res+=">";
	}
	reverse(res.begin(),res.end());
	cout<<res<<"\n";
}
bool work(int o){
	tr.build(1,0,m);
	int L=0,R=m;
	for(int i=1;i<n;i++){
		tr.update(1,1,inf,inf);
		if(op[i]==1){
			int x=a[i]+o;
			if(x%2==0) x/=2;
			else x=(x+1)/2;
			// cout<<op[i]<<" "<<x<<"\n";
			R=min(R,tr.queryl(1,0,m,x)-1);
			tr.changel(1,0,m,x);
		}
		else{
			int x=a[i]+o;
			if(x%2==0) x/=2;
			else x=(x-1)/2;
			// cout<<op[i]<<" "<<x<<"\n";
			L=max(L,tr.queryr(1,0,m,x)+1);
			tr.changer(1,0,m,x);
		}
		// for(int g=0;g<=m;g++) cout<<tr.query(1,0,m,g).first<<" \n"[g==m];
		// for(int g=0;g<=m;g++) cout<<tr.query(1,0,m,g).second<<" \n"[g==m];
		// cout<<"\n";
	}
	tr.update(1,1,inf,inf);
	// cout<<L<<" "<<R<<"\n";
	for(int i=L;i<=R;i++){
		int sn=i*2+o;
		if(sn>n) continue;
		pair<int,int> tmp=tr.query(1,0,m,i);
		tmp.first+=i,tmp.second+=i;
		if(tmp.first<=sn&&sn<=tmp.second){
			print(sn);
			return 1;
		}
	}
	return 0;
}
void solve(){
	cin>>n,m=n/2+1;
	for(int i=1;i<n;i++){
		cin>>a[i];
		if(a[i]>0) a[i]+=i-n,op[i]=1;
		else a[i]+=i,op[i]=-1;
	}
	if(work(0)) return;
	work(1);
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}