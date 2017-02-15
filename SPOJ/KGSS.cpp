#include <stdio.h>
#include <algorithm>
using namespace std;

typedef long long ll;

#define SZ 100005
#define INF 0x3f3f3f3f

struct Node {
	ll max1, max2;
	Node(ll _max1 = -INF, ll _max2 = -INF):
		max1(_max1), max2(_max2) { }
} st[4 * SZ];

ll a[SZ], n, m;

Node mix(Node a, Node b) {
	ll x[4] = {a.max1, a.max2, b.max1, b.max2};
	sort(x, x + 4);
	return Node(x[3], x[2]);
}

void init(ll p, ll L, ll R) {
	if (L == R) {
		st[p] = Node(a[L], -INF);
		return;
	}
	ll mid = (L + R) >> 1;
	init(2 * p, L, mid);
	init(2 * p + 1, mid + 1, R);
	st[p] = mix(st[2 * p], st[2 * p + 1]);
}

Node query(ll p, ll L, ll R, ll u, ll v) {
	if (v < L || R < u)
		return Node(-INF, -INF);
	if (u <= L && R <= v)
		return st[p];
	ll mid = (L + R) >> 1;
	return mix(query(2 * p, L, mid, u, v),
			   query(2 * p + 1, mid + 1, R, u, v));
}

void update(ll p, ll L, ll R, ll u, ll val) {
	if (L == R) {
		st[p] = Node(val, -INF);
		return;
	}
	ll mid = (L + R) >> 1;
	if (u <= mid)
		update(2 * p, L, mid, u, val);
	else
		update(2 * p + 1, mid + 1, R, u, val);
	st[p] = mix(st[2 * p], st[2 * p + 1]);
}

int main() {
	scanf("%lld", &n);
	for (ll i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	init(1, 1, n);
	char type[4]; ll i, x;
	scanf("%lld", &m);
	while (m--) {
		scanf("%s %lld %lld", type, &i, &x);
		if (*type == 'Q') {
			Node t = query(1, 1, n, i, x);
			printf("%lld\n", t.max1 + t.max2);
		} else {
			update(1, 1, n, i, x);
		}
	}
	return 0;
}
