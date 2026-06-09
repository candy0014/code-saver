#include <bits/stdc++.h>
//#define FILE ""
#define INF 0x3f3f3f3f
#define INF_LL 0x3f3f3f3f3f3f3f3f
#define scanf(...) assert(scanf(__VA_ARGS__))
using namespace std;
using ll = long long;
using ull = unsigned long long;

const int N = 1e5 + 5;

int n, k;

int a[N];

bool check(int m0,int m1,int m2,int m3,int m4,int m5,int m6) {
	m0+=m3;
	if (m1||m2) return 0;
	if(m5%2==0) return 1;
	if(m6<=1&&m4+m5+m6==n-m0) return 0;
	return 1;
}

void solve() {
	cin >> n >> k;
	int c1 = 0, c2 = 0;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		if (a[i] == 1) {
			++c1;
		}
		else if (a[i] == 2) {
			++c2;
		}
	}
	if (c1 || c2 >= 2) {
		cout << "Bob\n";
		return ;
	}
	if (k == 2) {
		int nn=0,a1=0;
		for(int i=1;i<=n;i++){
			if(a[i]%3){
				nn++,a1=a[i];
			}
		}
		if (nn == 1 && a1 % 3 == 2) {
			cout << "Ana\n";
		}
		else {
			cout << "Bob\n";
		}
	}
	else if (k >= 4) {
		cout << "Ana\n";
	}
	else {
		int m[8]={0,0,0,0,0,0,0,0};
		for (int i = 1; i <= n; ++i) {
			m[min(a[i],7)]++;
		}
		int ans=0;
		if(m[2]){
			ans=check(1,m[1],m[2]-1,m[3],m[4],m[5],m[6]);
		}
		else{
			for(int i=1;i<=n;i++) for(int j=2;j<=3;j++){
				m[min(a[i],7)]--;
				a[i]-=j;
				m[min(a[i],7)]++;
				ans|=check(m[0],m[1],m[2],m[3],m[4],m[5],m[6]);
				m[min(a[i],7)]--;
				a[i]+=j;
				m[min(a[i],7)]++;
			}
		}
		if(ans) cout<<"Ana\n";
		else cout<<"Bob\n";
	}
}

int main() {
#ifdef LOCAL
	assert(freopen("test.in", "r", stdin));
	assert(freopen("test.out", "w", stdout));
#elif defined(FILE)
	assert(freopen(FILE".in", "r", stdin));
	assert(freopen(FILE".out", "w", stdout));
#endif

	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin >> T;
	while (T--) {
		solve();
	}

	return 0;
}