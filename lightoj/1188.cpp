#include <bits/stdc++.h>
using namespace std;

#define MAX_N 100005
#define MAX_Q 50005

typedef long long ll;

struct Query {
	int x, y, no, ans;
};

int st[4 * MAX_N], a[MAX_N], t, n, q;
Query query[MAX_Q];
vector<int> h[MAX_N];

bool cmp_query(const Query& a, const Query& b) {
	return a.x < b.x;
}

bool cmp_query_no(const Query& a, const Query& b) {
	return a.no < b.no;
}

void set_0(int p, int L, int R, int u) {
	if (L == R) {
		st[p] = 0;
		return;
	}
	int mid = (L + R) / 2;
	if (u <= mid)
		set_0(2 * p, L, mid, u);
	else
		set_0(2 * p + 1, mid + 1, R, u);
	st[p] = st[2 * p] + st[2 * p + 1];
}

void set_1(int p, int L, int R, int u) {
	if (L == R) {
		st[p] = 1;
		return;
	}
	int mid = (L + R) / 2;
	if (u <= mid)
		set_1(2 * p, L, mid, u);
	else
		set_1(2 * p + 1, mid + 1, R, u);
	st[p] = st[2 * p] + st[2 * p + 1];
}

int get_sum(int p, int L, int R, int u, int v) {
	if (v < L || R < u)
		return 0;
	if (u <= L && R <= v)
		return st[p];
	int mid = (L + R) / 2;
	return get_sum(2 * p, L, mid, u, v) +
		get_sum(2 * p + 1, mid + 1, R, u, v);
}

void solve() {
	int prev_x = 1;
	for (int i = 0; i < q; i++) {
		if (prev_x != query[i].x) {
			for (int j = prev_x; j < query[i].x; j++) {
				vector<int>::iterator it =
					lower_bound(h[a[j]].begin(), h[a[j]].end(), query[i].x);
				if (it != h[a[j]].end())
					set_1(1, 1, n, *it);
				set_0(1, 1, n, j);
			}
			prev_x = query[i].x;
		}
		query[i].ans = get_sum(1, 1, n, query[i].x, query[i].y);
	}
}

int main() {
	scanf("%d", &t);
	for (int no = 1; no <= t; no++) {
		scanf("%d %d", &n, &q);
		memset(st, 0, sizeof(st));
		bitset<MAX_N> is_exist;

		for (int i = 0; i < MAX_N; i++)
			h[i].clear();
		
		for(int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			if (not is_exist[a[i]])
				set_1(1, 1, n, i);
			is_exist[a[i]] = true;
			h[a[i]].push_back(i);
		}

		for (int i = 0; i < q; i++) {
			scanf("%d %d", &query[i].x, &query[i].y);
			query[i].no = i;
		}
		
		sort(query, query + q, cmp_query);
		solve();
		sort(query, query + q, cmp_query_no);
		
		printf("Case %d:\n", no);
		for (int i = 0; i < q; i++)
			printf("%d\n", query[i].ans);
	}
	return 0;
}
