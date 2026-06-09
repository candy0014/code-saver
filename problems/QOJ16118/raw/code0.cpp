#include <bits/stdc++.h>
//#define FILE ""
#define INF 0x3f3f3f3f
#define INF_LL 0x3f3f3f3f3f3f3f3f
#define scanf(...) assert(scanf(__VA_ARGS__))
using namespace std;
using ll = long long;
using ull = unsigned long long;

const int N = 1e6 + 5, P = 1e9 + 7;

int n, m;

int a[N], b[N], c[N];

int num[N], fa[N], cnt[N], sz[N];
int find(int x) {
	return (x == fa[x] ? x : fa[x] = find(fa[x]));
}
void merge(int x, int y) {
	x = find(x), y = find(y);
	if (x == y) {
		++cnt[x];
		return ;
	}
	num[x] += num[y];
	sz[x] += sz[y];
	cnt[x] += cnt[y] + 1;
	fa[y] = x;
}

vector<int> vec[N];

int at[N], bt[N], len;

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

	cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		cin >> a[i] >> b[i] >> c[i];
		vec[c[i]].push_back(i);
	}
	int tmp = 0;
	for (int i = 1; i <= n; ++i) {
		if (vec[i].size() == 0) {
			++tmp;
			continue;
		}
		int p1 = a[vec[i][0]], p2 = b[vec[i][0]];
		for (int id : vec[i]) {
			if (a[id] != p1 && b[id] != p1) {
				p1 = 0;
			}
			if (a[id] != p2 && b[id] != p2) {
				p2 = 0;
			}
		}
		if (!p1 && !p2) {
			cout << "0\n";
			return 0;
		}
		else if (p1 && p2 && p1 != p2) {
			at[++len] = p1, bt[len] = p2;
		}
		else {
			if (p1) {
				++num[p1];
			}
			else {
				++num[p2];
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		fa[i] = i;
		sz[i] = 1;
		cnt[i] = 0;
	}
	for (int i = 1; i <= len; ++i) {
		merge(at[i], bt[i]);
	}
	int res = 1;
	for (int i = 1; i <= n; ++i) {
		if (i == find(i)) {
			if (cnt[i]+num[i] > sz[i]) {
				cout << "0\n";
				return 0;
			}
			if(num[i]==0){
				if (cnt[i] == sz[i] - 1) {
					res = 1ll * res * sz[i] % P;
				}
				else {
					res = 1ll * res * 2 % P;
				}
			}
		}
	}
	for (int i = 1; i <= tmp; ++i) {
		res = 1ll * res * i % P;
	}
	cout << res << '\n';

	return 0;
}