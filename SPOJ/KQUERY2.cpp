#include <stdio.h>
#include <string.h>
#include <math.h>

struct fenwick_t {
	int bit[10010], sum;
	int query(int y) {
		int ans = 0;
		for (; y > 0; y -= (y & -y))
			ans += bit[y];
		return ans;
	}	
	void update(int x, int value) {
		for (; x <= 10000; x += (x & -x))
			bit[x] += value;
		sum += value;
	}
};

fenwick_t seg[175];
int n, a[30010], q;

#define sqrt_n 997 // what the fuck?

int main() {
	scanf("%d", &n);
	memset(seg, 0, sizeof(seg));
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		seg[(i - 1) / sqrt_n].update(a[i], 1);
	}
	scanf("%d", &q);
	int i, j, v, k, type;
	for (int cntr = 1; cntr <= q; cntr++) {
		scanf("%d", &type);
		if (type == 0) { // change a[i] to v
			scanf("%d %d", &i, &v);
			seg[(i - 1) / sqrt_n].update(a[i], -1);
			seg[(i - 1) / sqrt_n].update(v, 1);
			a[i] = v;
		} else { // answer query i, j, k
			int ans = 0;
			scanf("%d %d %d", &i, &j, &k);
			while (i <= j && i % sqrt_n != 1)
				ans += a[i++] > k;
			while (i <= j && j % sqrt_n != 0)
				ans += a[j--] > k;
			while (i <= j) {
				int group_no = (i - 1) / sqrt_n;
				ans += seg[group_no].sum - seg[group_no].query(k);
				i += sqrt_n;
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}
