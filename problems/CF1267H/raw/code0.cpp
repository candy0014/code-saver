#include <bits/stdc++.h>
using namespace std;
int n,a[8505],res[8505],tag[8505],pre[8505],nex[8505];
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],res[i]=0;
	for(int c=1;c<=24;c++){
		for(int i=1;i<=n;i++) tag[i]=0,pre[i]=i-1,nex[i]=i+1;
		for(int i=1;i<=n;i++) if(res[i]) nex[pre[i]]=nex[i],pre[nex[i]]=pre[i];
		for(int i=n;i>=1;i--){
			int x=a[i];
			if(res[x]) continue;
			if(!tag[x]) res[x]=c,tag[pre[x]]=tag[nex[x]]=1;
			nex[pre[x]]=nex[x],pre[nex[x]]=pre[x];
		}
	}
	for(int i=1;i<=n;i++) cout<<res[i]<<" \n"[i==n];
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}