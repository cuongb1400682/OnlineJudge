#include <stdio.h>
#include <algorithm>
using namespace std;

#define MAX_N 100005
#define MAX_Q 100005
#define INF   0x3f3f3f3f

int left[MAX_N], right[MAX_N], st[4 * MAX_N], a[MAX_N], n, q;

void calc_left_right() {
	int prev = INF;
	int cnt = 0;
	for (int i = 1, tmp; i <= n; i++) {
		tmp = a[i];
		if (a[i] != prev)
			a[i] = ++cnt;
		else
			a[i] = cnt;
		prev = tmp;
	}
	
	left[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (a[i] != a[i - 1])
			left[i] = 1;
		else
			left[i] = left[i - 1] + 1;
	}
	right[n] = 1;
	for (int i = n - 1; i >= 1; i--) {
		if (a[i] != a[i + 1])
			right[i] = 1;
		else
			right[i] = right[i + 1] + 1;
	}	
}

void init(int p, int L, int R) {
	if (L == R) {
		st[p] = left[L];
		return;
	}
	int mid = (L + R) >> 1;
	init(2 * p, L, mid);
	init(2 * p + 1, mid + 1, R);
	st[p] = max(st[2 * p], st[2 * p + 1]);
}

int get_max(int p, int L, int R, int u, int v) {
	if (v < L || R < u)
		return -INF;
	if (u <= L && R <= v)
		return st[p];
	int mid = (L + R) >> 1;
	return max(get_max(2 * p, L, mid, u, v),
			   get_max(2 * p + 1, mid + 1, R, u, v));
}

int main() {
	while (scanf("%d", &n), n) {
		scanf("%d", &q);
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		calc_left_right();

		init(1, 1, n);
		for (int i = 1; i <= q; i++) {
			int u, v;
			scanf("%d %d", &u, &v);
			if (a[v] == a[u]) {
				printf("%d\n", v - u + 1);
			} else if (a[v] - a[u] == 1) {
				printf("%d\n", max(right[u], left[v]));
			} else {
				int t1 = right[u];
				int t2 = left[v];
				int t3 = get_max(1, 1, n, u + t1, v - t2);
				printf("%d\n", max(max(t1, t2), t3));
			}
		}
	}
	return 0;
}
