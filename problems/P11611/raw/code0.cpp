#include <bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int n,p[1000005],son[3000005][2],tot,id[3000005],tag[3000005],du[3000005],dp[3000005],fail[3000005];
string str;
queue<int>q;
int F(int u,int x){
	if(fail[u]) return son[fail[u]][x];
	return id[u]*2+x+1;
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n,tot=n*2;
	for(int i=1;i<=n*2;i++) id[i]=(i+1)/2;
	getline(cin,str),getline(cin,str);
	for(int i=0,v=0,mi=1e9,ma=0,flag=0;str[i];i++){
		if(str[i]=='~') flag=1;
		if('0'<=str[i]&&str[i]<='9') v=v*10+str[i]-'0';
		if((str[i]==' '||str[i]==')')&&v) p[v]=flag,flag=0,mi=min(mi,v),ma=max(ma,v),v=0;
		if(str[i]==')'){
			int now=2*mi+p[mi]-1;
			for(int j=mi+1;j<=ma;j++){
				if(!son[now][p[j]]) son[now][p[j]]=++tot,id[tot]=j;
				now=son[now][p[j]];
			}
			tag[now]=1;
			mi=1e9,ma=0;
		}
	}
	for(int i=1;i<=n*2;i++) q.push(i);
	while(!q.empty()){
		int u=q.front();q.pop(),tag[u]|=tag[fail[u]];
		if(id[u]==n) continue;
		for(int x:{0,1}){
			int v=son[u][x];
			if(v) fail[v]=F(u,x),q.push(v);
			else son[u][x]=F(u,x);
			du[son[u][x]]++;
		}
	}
	for(int i=1;i<=tot;i++) if(!du[i]) q.push(i);
	dp[1]=dp[2]=1;
	int res=0;
	while(!q.empty()){
		int u=q.front();q.pop();
		if(tag[u]) dp[u]=0;
		if(id[u]==n){res=(res+dp[u])%mod;continue;}
		for(int x:{0,1}){
			dp[son[u][x]]=(dp[son[u][x]]+dp[u])%mod,du[son[u][x]]--;
			if(!du[son[u][x]]) q.push(son[u][x]);
		}
	}
	cout<<res<<"\n";
	return 0;
}