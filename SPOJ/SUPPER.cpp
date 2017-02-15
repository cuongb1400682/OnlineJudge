#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <vector>
#include <map>
using namespace std;

#define SZ 100005
#define INF 0x3f3f3f3f

int st[4 * SZ], number[SZ], n, inc[SZ], dec[SZ], n_ans;

int get_max(int p, int L, int R, int u, int v) {
	if (v < L || R < u)
		return -INF;
	if (u <= L && R <= v)
		return st[p];
	int mid = (L + R) >> 1;
	return max(get_max(2 * p, L, mid, u, v),
			   get_max(2 * p + 1, mid + 1, R, u, v));
}

void update(int p, int L, int R, int u, int max_len) {
	if (L == R) {
		st[p] = max_len;
		return;
	}
	int mid = (L + R) >> 1;
	if (u <= mid)
		update(2 * p, L, mid, u, max_len);
	else
		update(2 * p + 1, mid + 1, R, u, max_len);
	st[p] = max(st[2 * p], st[2 * p + 1]);
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; i++)
			scanf("%d", &number[i]);

		int max_len = -INF;
		memset(st, 0, sizeof(st));
		memset(inc, 0, sizeof(inc));
		for (int i = 1; i <= n; i++) {
			inc[i] = get_max(1, 1, n, 1, number[i]) + 1;
			update(1, 1, n, number[i], inc[i]);
			if (max_len < inc[i])
				max_len = inc[i];
		}

		n_ans = 0;
		memset(st, 0, sizeof(st));
		for (int i = n; i >= 1; i--) {
			dec[i] = get_max(1, 0, n, number[i], n) + 1;
			update(1, 1, n, number[i], dec[i]);
		}

		vector<int> ans;
		for (int i = 1; i <= n; i++)
			if (inc[i] + dec[i] - 1 == max_len)
				ans.push_back(number[i]);
		
		sort(ans.begin(), ans.end());
		
		printf("%d\n", (int) ans.size());
		for (int i = 0; i < (int) ans.size(); i++)
			printf("%d ", ans[i]);
		printf("\n");
	}
	return 0;
}
