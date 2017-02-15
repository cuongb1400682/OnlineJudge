#include <stdio.h>
#include <map>
#include <vector>
#include <string.h>

using namespace std;

#define SZ 100005

struct Query {
	int u, v, ans;
};

int st[4 * SZ], a[SZ], n, m;
Query query[SZ];
map<int, vector<int> > P, map_query;

void update(int p, int L, int R, int u, int value) {
	if (L == R) {
		st[p] += value;
		return;
	}
	int mid = (L + R) / 2;
	if (u <= mid)
		update(2 * p, L, mid, u, value);
	else
		update(2 * p + 1, mid + 1, R, u, value);
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

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	map_query.clear();
	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &query[i].u, &query[i].v);
		map_query[query[i].v].push_back(i);
	}
	
	memset(st, 0, sizeof(st));
	P.clear();
	for (int i = 1; i <= n; i++) {
		vector<int>& z = P[a[i]];

		z.push_back(i);
		
		if (a[i] <= z.size())
			update(1, 1, n, z[z.size() - a[i]], 1);			
		if (a[i] + 1 <= z.size())
			update(1, 1, n, z[z.size() - a[i] - 1], -2);
		if (a[i] + 2 <= z.size())
			update(1, 1, n, z[z.size() - a[i] - 2], 1);

		vector<int>& map_query_i = map_query[i];
		for (int j = 0; j < map_query_i.size(); j++) {
			Query& zz = query[map_query_i[j]];
			zz.ans = get_sum(1, 1, n, zz.u, zz.v);
		} 
	}
	for (int i = 1; i <= m; i++)
		printf("%d\n", query[i].ans);
	return 0;
}
