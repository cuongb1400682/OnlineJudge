#include <stdio.h>
#include <string.h>

#define SZ 20005

int x[SZ], t, n, bit[SZ];

int query(int x, int y) {
	int ans = 0;
	for (; y > 0; y -= (y & -y))
		ans += bit[y];
	for (x--; x > 0; x -= (x & -x))
		ans -= bit[x];
	return ans;
}

void update(int x, int value) {
	for (; x <= n; x += (x & -x))
		bit[x] += value;
}

int find_pos(int pos) {
	int lw = 1, hi = n;
	while (lw < hi) {
		int mid = (lw + hi) >> 1;
		if (query(1, mid) >= pos)
			hi = mid;
		else
			lw = mid + 1;
	}
	return lw;
}

void print() {
	for (int i = 1; i <= n; i++)
		printf("%d ", x[i]);
	printf("\n"); 
}

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		memset(bit, 0, sizeof(bit));
		for (int i = 1; i <= n; i++) {
			update(i, 1);
			x[i] = 0;
		}
		int pos = 0; 
		for (int i = 1; i <= n; i++) {
			pos = (pos + i) % query(1, n);
			pos++;
			x[find_pos(pos)] = i;
			update(find_pos(pos), -1);
			pos--;
		}
		print();
		printf("\n");
	}
	return 0;
}
