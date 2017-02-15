#include <bits/stdc++.h>
using namespace std;

#define debug(x) cerr << #x " = " << (x) << '\n'
#define arr(x, n) {cerr<<#x<<" = "<<"["<<(n)<<"]"<<"(";for(ll _=0;_<(n);_++) cerr<<(x)[_]<<(_!=(n)-1?", ":")\n");}
#define iarr(x, m, n) {cerr<<#x":\n";for(ll _=(m);_<=(n);_++) cerr<<_<<": "<<(x)[_]<<'\n';}
#define err(...) fprintf(stderr, __VA_ARGS__)
#define SZ 100005
#define INF 0x3f3f3f3f

typedef long long ll;

struct Node {
	int min, max;
	Node(int _min = 0, int _max = 0) {
		min = _min;
		max = _max;
	}
} st[4 * SZ];

int t, n, d, a[SZ];

void init(const int *a, int p, int L, int R) {
	st[p] = Node();
	if (L == R) {
		st[p].max = st[p].min = a[L];
		return;
	}
	init(a, 2 * p, L, (L + R) / 2);
	init(a, 2 * p + 1, (L + R) / 2 + 1, R);
	st[p].min = min(st[2 * p].min, st[2 * p + 1].min);
	st[p].max = max(st[2 * p].max, st[2 * p + 1].max);	
}

Node query(int p, int L, int R, int u, int v) {
	if (v < L || R < u)
		return Node(INF, -INF);
	if (u <= L && R <= v)
		return st[p];
	Node lft = query(2 * p, L, (L + R) / 2, u, v);
	Node rght = query(2 * p + 1, (L + R) / 2 + 1, R, u, v);
	return Node(min(lft.min, rght.min), max(lft.max, rght.max));
}

int main() {
	scanf("%d", &t);
	for (int no = 1; no <= t; no++) {
		scanf("%d %d", &n, &d);
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		init(a, 1, 1, n);
		int ans = 0;
		for (int i = 1; i <= n - d + 1; i++) {
			Node tmp = query(1, 1, n, i, i + d - 1);
			ans = max(ans, tmp.max - tmp.min);
		}
		printf("Case %d: %d\n", no, ans);
	}
	return 0;
}
