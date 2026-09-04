#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
struct P{
	ld x,y;
}p[4],q[4],s[105],t[105];
ld k;
int n;
bool work(ld a,ld b,ld c,
          ld d,ld e,ld f,
          ld g,ld h,ld i,
          ld &x,ld &y,ld &z){
    const ld eps=1e-12;

    ld A=a-d,B=b-e,C=c-f;
    ld D=d-g,E=e-h,F=f-i;

    ld det=A*E-B*D;
    if(fabs(det)<eps) return false;

    x=(C*E-B*F)/det;
    y=(A*F-C*D)/det;
    z=c-a*x-b*y;
    return true;
}
ld dis(P u,P v){return sqrt((u.x-v.x)*(u.x-v.x)+(u.y-v.y)*(u.y-v.y));}
ld a,b,c,d,e,f;
void solve(){
	for(int i=0;i<4;i++) cin>>p[i].x>>p[i].y;
	for(int i=0;i<4;i++) cin>>q[i].x>>q[i].y;
	for(int u=0;u<4;u++) for(int v=u+1;v<4;v++) for(int w=v+1;w<4;w++){
		if(work(p[u].x,p[u].y,q[u].x,p[v].x,p[v].y,q[v].x,p[w].x,p[w].y,q[w].x,a,b,c)) u=v=w=4;
	}
	for(int u=0;u<4;u++) for(int v=u+1;v<4;v++) for(int w=v+1;w<4;w++){
		if(work(p[u].x,p[u].y,q[u].y,p[v].x,p[v].y,q[v].y,p[w].x,p[w].y,q[w].y,d,e,f)) u=v=w=4;
	}
	cin>>s[0].x>>s[0].y>>t[0].x>>t[0].y;
	cin>>k>>n;
	for(int i=1;i<=n;i++){
		s[i].x=a*s[i-1].x+b*s[i-1].y+c,s[i].y=d*s[i-1].x+e*s[i-1].y+f;
		t[i].x=a*t[i-1].x+b*t[i-1].y+c,t[i].y=d*t[i-1].x+e*t[i-1].y+f;
	}
	ld res=1e18;
	for(int i=0;i<=n;i++) for(int j=0;i+j<=n;j++){
		res=min(res,(i+j)*k+dis(s[i],t[j]));
	}
	cout<<fixed<<setprecision(15)<<res<<"\n";
}
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Ca;cin>>Ca;while(Ca--)solve();
	return 0;
}