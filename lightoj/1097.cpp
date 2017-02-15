#include <bits/stdc++.h>
using namespace std;

#define SZ 2000000

int st[4 * SZ];

void init(int p, int L, int R) {
	if (L == R) {
		st[p] = L&1;
		return;
	}
	int mid = (L + R) >> 1;
	init(2 * p, L, mid);
	init(2 * p + 1, mid + 1, R);
	st[p] = st[2 * p] + st[2 * p + 1];
}

void remove_kth(int p, int L, int R, int u) {
	if (L == R) {
		st[p] = 0;
		return;
	}
	int mid = (L + R) >> 1;
	if (u <= st[2 * p])
		remove_kth(2 * p,  L, mid, u);
	else
		remove_kth(2 * p + 1, mid + 1, R, u - st[2 * p]);
	st[p] = st[2 * p] + st[2 * p + 1];
}

int find_kth(int p, int L, int R, int k) {
	if (L == R)
		return L;
	int mid = (L + R) >> 1;
	if (k <= st[2 * p])
		return find_kth(2 * p, L, mid, k);
	else
		return find_kth(2 * p + 1, mid + 1, R, k - st[2 * p]);
}

#define find(idx) find_kth(1, 1, SZ - 1, idx)
#define remove(idx) remove_kth(1, 1, SZ - 1, idx)

int main() {
	init(1, 1, SZ - 1);

	for (int i = 2; i <= SZ - 1; i++) {
		int x = find(i), cnt = 0;
		for (int j = x; j <= st[1]; j += x) {
			remove(j - cnt);
			cnt++;
		}
	}

	int t, n;
	scanf("%d", &t);
	for (int no = 1; no <= t; no++) {
		scanf("%d", &n);
		printf("Case %d: %d\n", no, find(n));
	}
	return 0;
}
