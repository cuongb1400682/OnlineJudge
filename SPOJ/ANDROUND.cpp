#include <stdio.h>

#define SZ 20005

int a[SZ], st[4 * SZ], n, k, t;

int loop_limit(int n) {
	return 1 + ((n - 3) >> 2) + ((n - 3) & 1);
}

void init(int p, int L, int R) {
	if (L == R) {
		st[p] = a[L];
		return;
	}
	int mid = (L + R) >> 1;
	init(2 * p, L, mid);
	init(2 * p + 1, mid + 1, R);
	st[p] = st[2 * p] & st[2 * p + 1];
}

int query(int p, int L, int R, int u, int v) {
	if (v < L || R < u)
		return ~0;
	if (u <= L && R <= v)
		return st[p];
	int mid = (L + R) >> 1;
	return query(2 * p, L, mid, u, v) &
			query(2 * p + 1, mid + 1, R, u, v);
}

int do_query(int u, int v) {
	if (u < 0) {
		return query(1, 0, n - 1, n + u, n - 1) &
			query(1, 0, n - 1, 0, v);
	} else if (v >= n) {
		return query(1, 0, n - 1, 0, v - n) &
			query(1, 0, n - 1, u, n - 1);
	} else {
		return query(1, 0, n - 1, u, v);
	}
}

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d", &n, &k);
		for (int i = 0; i < n; i++) 
			scanf("%d", &a[i]);
		init(1, 0, n - 1);
		for (int i = 0; i < n; i++) {
			if (1 + 2 * k < n) {
				printf("%d", do_query(i - k, i + k));
			} else {
				printf("%d", do_query(0, n - 1));
			}
			if (i == n - 1)
				printf("\n");
			else
				printf(" ");
		}		
	}
	return 0;
}
