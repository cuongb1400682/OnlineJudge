#include <stdio.h>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

#define SZ 100000

struct Query {
	int i, x, y, ans;
};

Query query[300000];
map<int, vector<int> > h;
int n, q, w[SZ], st[4 * SZ], a[SZ];

bool query_cmp(const Query& a, const Query& b) {
	return a.x < b.x;
}

bool query_cmp_i(const Query& a, const Query& b) {
	return a.i < b.i;
}

void init(const int *a, int p, int L, int R) {
	st[p] = 0;
	if (L == R) {
		st[p] = a[L];
		return;
	}
	int mid = (L + R) >> 1;
	init(a, 2 * p, L, mid);
	init(a, 2 * p + 1, mid + 1, R);
	st[p] = st[2 * p] + st[2 * p + 1];
}

void update(int p, int L, int R, int u, int value) {
	if (L == R) {
		st[p] = value;
		return;
	}
	int mid = (L + R) >> 1;
	if (u <= mid)
		update(2 * p, L, mid, u, value);
	else
		update(2 * p + 1, mid + 1, R, u, value);
	st[p] = st[2 * p] + st[2 * p + 1];
}

int count_diff(int p, int L, int R, int u, int v) {
	if (v < L || R < u)
		return 0;
	if (u <= L && R <= v)
		return st[p];
	int mid = (L + R) >> 1;
	return count_diff(2 * p, L, mid, u, v) +
			count_diff(2 * p + 1, mid + 1, R, u, v);
}

int main() {
	scanf("%d", &n);
	h.clear();
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		w[i] = bool(h.count(a[i]) == 0);
		h[a[i]].push_back(i);		
	}

	scanf("%d", &q);
	for (int i = 0; i < q; i++) {
		scanf("%d %d", &query[i].x, &query[i].y);
		query[i].i = i;
		query[i].ans = 0;
	}
	
	init(w, 1, 1, n);
	sort(query, query + q, query_cmp);
	
	int prev = 1;
	for (int i = 0; i < q; i++) {
		if (prev != query[i].x) {
			for (int x = prev; x != query[i].x; x++) {
				vector<int>& z = h[a[x]];
				vector<int>::iterator it;
				it = lower_bound(z.begin(), z.end(), query[i].x);
				if (it != z.end()) {
					update(1, 1, n, *it, 1);
				}
				update(1, 1, n, x, 0);
			}
			prev = query[i].x;
		}
		query[i].ans = count_diff(1, 1, n, query[i].x, query[i].y);
	}
	sort(query, query + q, query_cmp_i);
	for (int i = 0; i < q; i++)
		printf("%d\n", query[i].ans);
	return 0;
}
