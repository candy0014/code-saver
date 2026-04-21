#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
namespace FASTIO {
char ibuf[1 << 21], *p1 = ibuf, *p2 = ibuf;
inline char getc() {return p1 == p2 && (p2 = (p1 = ibuf) + fread(ibuf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++;}
template<class T> bool read(T &x) {
    x = 0; int f = 0; char ch = getc();
    while (ch < '0' || ch > '9') f |= ch == '-', ch = getc();
    while (ch >= '0' && ch <= '9') x = (x * 10) + (ch ^ 48), ch = getc();
    x = (f ? -x : x); return 1;
}
template<typename A, typename ...B> bool read(A &x, B &...y) {return read(x) && read(y...);}
char obuf[1 << 21], *o1 = obuf, *o2 = obuf + (1 << 21) - 1;
void flush() {fwrite(obuf, 1, o1 - obuf, stdout), o1 = obuf;}
void putc(char x) {*o1++ = x; if (o1 == o2) flush();}
template<class T> void write(T x) {
    if (!x) putc('0');
    if (x < 0) x = -x, putc('-');
    char c[40]; int tot = 0;
    while (x) c[++tot] = x % 10, x /= 10;
    for (int i = tot; i; --i) putc(c[i] + '0');
}
void write(char x) {putc(x);}
void write(char *x) {while (*x) putc(*x++);}
void write(const char *x) {while (*x) putc(*x++);}
template<typename A, typename ...B> void write(A x, B ...y) {write(x), write(y...);}
struct Flusher {~Flusher() {flush();}} flusher;
}
using FASTIO::read; using FASTIO::putc; using FASTIO::write;
int ID,n,ca;
ll c[3000005],a[3000005],b[3000005];
int cnt[45];
int work(ll &x){
	int res=0;
	while(x&(x+1)) x>>=1,res++;
	x=__lg(x)+1;
	return res;
}
ll solve(){
	int res=cnt[0]*2;
	for(int i=40;i>=2;i--) if(cnt[i]){
		int t=cnt[i]/2;
		cnt[i]-=t*2,cnt[i-1]+=t,res+=t*(2*i+4);
		if(cnt[i]){
			res+=2*i+1;
			i--;
			while(i>=2&&!cnt[i]) i--;
			if(i==1){
				return res+cnt[1]*2;
			}
			else{
				res+=3;
				cnt[i]--,cnt[i-1]++;
			}
			i++;
		}
	}
	return res+cnt[1]*2+1;
}
int N;
struct TREE{
	int sum[3100005];
	void add(int x,int k){while(x<=N)sum[x+(x>>10)]+=k,x+=(x&(-x));}
	int query(int x){int t=0;while(x)t+=sum[x+(x>>10)],x&=(x-1);return t;}
	int query(int l,int r){return query(r)-query(l-1);}
}tr[41];
int main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	read(n);N=(n>>6)+1;
	for(int i=0;i<n;i++) read(a[i]),cnt[0]+=work(a[i]),cnt[a[i]]++;
	write(solve(),'\n');
	cerr<<clock()*1.0/CLOCKS_PER_SEC<<"\n";
	return 0;
}