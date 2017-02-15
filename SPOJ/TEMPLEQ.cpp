#include <stdio.h>
#include <string.h>
#include <utility>
#include <algorithm>
using namespace std;

#define SZ 100005
#define value first
#define pos second

typedef long long ll;
typedef pair<int, int> ii;

ii a[SZ];
int n, m, pos[SZ], bit[SZ];

inline void _update(int x, int value) {
	for (; x <= n; x += (x & -x))
		bit[x] += value;
}

inline int _query(int x) {
	int ans = 0;
	for (; x > 0; x -= (x & -x))
		ans += bit[x];
	return ans;
}

inline void add(int x, int y, int value) {
	_update(x, value);
	_update(y + 1, -value);
}

inline int at(int x) {
	return _query(x);
}

int lower_bound(int key) {
	int lw = 1, hi = n + 1;
	while (lw < hi) {
		int mid = (lw + hi) >> 1;
		if (at(mid) >= key)
			hi = mid;
		else
			lw = mid + 1;
	}
	return lw;
}

int upper_bound(int key) {
	int lw = 1, hi = n + 1;
	while (lw < hi) {
		int mid = (lw + hi) >> 1;
		if (at(mid) > key)
			hi = mid;
		else
			lw = mid + 1;
	}
	return lw;
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i].value);
		a[i].pos = i;
	}
	
	sort(a + 1, a + 1 + n);
	memset(bit, 0, sizeof(bit));
	
	for (int i = 1; i <= n; i++) {
		pos[a[i].pos] = i;
		add(i, i, a[i].value);
	}

	int type, x;
	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &type, &x);
		if (type == 1) {
			int value = at(pos[x]);
			int y = upper_bound(value) - 1;
			add(y, y, 1);
			int tmp = pos[x];
			swap(pos[x], pos[a[y].pos]);
			swap(a[tmp], a[y]);
		} else if (type == 2) {
			int y = lower_bound(x);
			printf("%d\n", n + 1 - y);
		} else {
			int y = lower_bound(x);
			if (y != n + 1)
				add(y, n, -1);
		}
	}
	return 0;
}
