#include <stdio.h>
#include <math.h>
#include <utility>
#include <string.h>
using namespace std;

#define SZ 100005
#define INF 0x3f3f3f3f3f3f3f3fLL

#define err(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

ll st[4 * SZ], a[SZ];
bool is_1[4 * SZ];
int n, q;

void init(const ll *a, int p, int L, int R) {
	st[p] = 0LL;
	if (L == R) {
		st[p] = a[L];
		return;
	}
	int mid = (L + R) >> 1;
	init(a, 2 * p, L, mid);
	init(a, 2 * p + 1, mid + 1, R);
	st[p] = st[2 * p] + st[2 * p + 1];
}

void go_down(int p, int L, int R) {
	if (is_1[p])
		return;
	if (L == R) {
		st[p] = (ll) sqrt(st[p]);
		if (st[p] == 1)
			is_1[p] = true;
		return;
	}
	int mid = (L + R) >> 1;
	go_down(2 * p, L, mid);
	go_down(2 * p + 1, mid + 1, R);
	st[p] = st[2 * p] + st[2 * p + 1];
	is_1[p] = is_1[2 * p] && is_1[2 * p + 1];
}

void update(int p, int L, int R, int u, int v) {
	if (v < L || R < u)
		return;
	if (is_1[p])
		return;
	if (u <= L && R <= v) {
		go_down(p, L, R);
		return;
	}
	int mid = (L + R) >> 1;
	update(2 * p, L, mid, u, v);
	update(2 * p + 1, mid + 1, R, u, v);
	st[p] = st[2 * p] + st[2 * p + 1];
	is_1[p] = is_1[2 * p] && is_1[2 * p + 1];
}

ll query(int p, int L, int R, int u, int v) {
	if (v < L || R < u)
		return 0LL;
	if (u <= L && R <= v) {
		if (is_1[p])
			return R - L + 1;
		else
			return st[p];
	}
	int mid = (L + R) >> 1;
	return query(2 * p, L, mid, u, v) +
			query(2 * p + 1, mid + 1, R, u, v);
}

int main() {
	for (int no = 1; scanf("%d", &n) != EOF; no++) {
		for (int i = 1; i <= n; i++)
			scanf("%lld", &a[i]);
		init(a, 1, 1, n);
		memset(is_1, false, sizeof(is_1));
		scanf("%d", &q);
		printf("Case #%d:\n", no);
		for (int i = 1; i <= q; i++) {
			int t, u, v;
			scanf("%d %d %d", &t, &u, &v);
			if (u > v) swap(u, v);
			if (t == 0)
				update(1, 1, n, u, v);
			else
				printf("%lld\n", query(1, 1, n, u, v));
		}
		printf("\n");
	}
	return 0;
}
