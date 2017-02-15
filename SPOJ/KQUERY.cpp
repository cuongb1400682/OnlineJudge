#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
#include <map>
#include <string.h>
using namespace std;

#define MAX_N 300005

struct Query {
	int i, ans, x, y, k;
};

struct Element {
	int i, value;
};

int n, bit[MAX_N], q;
Query query[200005];
Element a[MAX_N];

void update(int x, int value) {
	for (; x <= n; x += (x & -x)) {
		bit[x] += value;
	}
}

int get_sum(int x, int y) {
	int ans = 0;
	for (; y > 0; y -= (y & -y))
		ans += bit[y];
	for (x--; x > 0; x -= (x & -x))
		ans -= bit[x];
	return ans;
}

bool cmp_query_k(const Query& a, const Query& b) {
	return a.k > b.k;
}

bool cmp_query_i(const Query& a, const Query& b) {
	return a.i < b.i;
}

bool cmp_a_value(const Element& a, const Element& b) {
	return a.value > b.value;
}

int main() {
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i].value);
		a[i].i = i;
	}
	
	scanf("%d", &q);
	for (int i = 1; i <= q; i++) {
		scanf("%d %d %d", &query[i].x, &query[i].y, &query[i].k);
		query[i].i = i;
	}

	sort(query + 1, query + 1 + q, cmp_query_k);
	sort(a + 1, a + 1 + n, cmp_a_value);

	int x = 1;
	for (int i = 1; i <= q; i++) {
		for (; a[x].value > query[i].k; x++)
			update(a[x].i, 1);
		query[i].ans = get_sum(query[i].x, query[i].y);
	}

	sort(query + 1, query + 1 + q, cmp_query_i);

	for (int i = 1; i <= q; i++)
		printf("%d\n", query[i].ans);
	
	return 0;
}
