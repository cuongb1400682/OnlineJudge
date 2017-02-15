#include <stdio.h>
#include <vector>

using namespace std;

#define SZ 200002

int w[SZ], n, st[4 * SZ], t, x[SZ];

void init(int p, int L, int R) {
	if (L == R) {
		st[p] = 1;
		return;
	}
	int mid = (L + R) >> 1;
	init(2 * p, L, mid);
	init(2 * p + 1, mid + 1, R);
	st[p] = st[2 * p] + st[2 * p + 1];
}

int value_at(int p, int L, int R, int u) {
	if (L == R)
		return L;
	int mid = (L + R) >> 1;
	if (u > st[2 * p])
		return value_at(2 * p + 1, mid + 1, R, u - st[2 * p]);
	else
		return value_at(2 * p, L, mid, u);
}

void erase(int p, int L, int R, int u) {
	if (L == R) {
		st[p] = 0;
		return;
	}
	int mid = (L + R) >> 1;
	if (u > st[2 * p])
		erase(2 * p + 1, mid + 1, R, u - st[2 * p]);
	else
		erase(2 * p, L, mid, u);
	st[p] = st[2 * p] + st[2 * p + 1];
}

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			scanf("%d", &w[i]);
		init(1, 1, n);
		for (int i = n; i >= 1; i--) {
			int pos = st[1] - w[i];
			x[i] = value_at(1, 1, n, pos);
			erase(1, 1, n, pos);
		}
		for (int i = 1; i <= n; i++)
			printf("%d ", x[i]);
		printf("\n");
	}
	return 0;
}
