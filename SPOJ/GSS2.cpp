// SPOJ - GSS2 the maximum sum of continuous distinguish elements in a seq

#include <stdio.h>
#include <map>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;

typedef long long ll;

#define SZ 100005
#define INF 0x3f3f3f3f

struct Node {
	ll lazy, best_lazy;
	ll max, best_max;
};

struct Query {
	ll x, y, ans, i;
};

Node st[4 * SZ];
Query query[SZ];
ll a[SZ], n, q;
map<ll, vector<Query *> > h_query;
map<ll, ll> pos;

void propagate(ll p, ll L, ll R) {
	for (ll c = 2 * p; c <= 2 * p + 1; c++) {
		st[c].best_max = max(st[c].best_max,
							 st[c].max + st[p].best_lazy);
		st[c].best_lazy = max(st[c].best_lazy,
							  st[c].lazy + st[p].best_lazy);
		st[c].max += st[p].lazy;
		st[c].lazy += st[p].lazy;
	}
	st[p].lazy = st[p].best_lazy = 0;
}

void insert(ll p, ll L, ll R, ll u, ll v, ll val) {
	if (v < L || R < u)
		return;
	if (u <= L && R <= v) {
		st[p].max += val;
		st[p].lazy += val;
		st[p].best_max = max(st[p].best_max, st[p].max);
		st[p].best_lazy = max(st[p].best_lazy, st[p].lazy);
		return;
	}
	if (st[p].lazy != 0)
		propagate(p, L, R);
	ll mid = (L + R) >> 1;
	insert(2 * p, L, mid, u, v, val);
	insert(2 * p + 1, mid + 1, R, u, v, val);
	st[p].max = max(st[2 * p].max, st[2 * p + 1].max);
	st[p].best_max = max(st[2 * p].best_max, st[2 * p + 1].best_max);
}

ll get_max(ll p, ll L, ll R, ll u, ll v) {
	if (v < L || R < u)
		return 0;
	if (u <= L && R <= v)
		return st[p].best_max;
	if (st[p].lazy != 0)	
		propagate(p, L, R);
	ll mid = (L + R) >> 1;
	return max(get_max(2 * p, L, mid, u, v),
			   get_max(2 * p + 1, mid + 1, R, u, v));
}

int main() {
	scanf("%lld", &n);
	for (ll i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	scanf("%lld", &q);
	h_query.clear();
	for (ll i = 0; i < q; i++) {
		scanf("%lld %lld", &query[i].x, &query[i].y);
		h_query[query[i].y].push_back(&query[i]);
	}
	pos.clear();
	memset(st, 0, sizeof(st));
	for (ll i = 1; i <= n; i++) {
		insert(1, 1, n, pos[a[i]] + 1, i, a[i]);
		for (ll j = 0; j < h_query[i].size(); j++) {
			h_query[i][j]->ans = get_max(1, 1, n,
									   h_query[i][j]->x,
									   h_query[i][j]->y);
		}
		pos[a[i]] = i;
	}
	
	for (ll i = 0; i < q; i++)
		printf("%lld\n", query[i].ans);
	return 0;
}
