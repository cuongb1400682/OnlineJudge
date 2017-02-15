#include <bits/stdc++.h>
using namespace std;

#define debug(x) cerr << #x " = " << (x) << '\n'
#define arr(x, n) {cerr<<#x<<" = "<<"["<<(n)<<"]"<<"(";for(ll _=0;_<(n);_++) cerr<<(x)[_]<<(_!=(n)-1?", ":")\n");}
#define iarr(x, m, n) {cerr<<#x":\n";for(ll _=(m);_<=(n);_++) cerr<<_<<": "<<(x)[_]<<'\n';}
#define err(...) fprintf(stderr, __VA_ARGS__)
#define SZ 100005

typedef long long ll;

int a[SZ], st[SZ * 4], t, n;

void init(int p, int L, int R) {
	if (L == R) {
		st[p] = 1;
		return;
	}
	init(2 * p, L, (L + R) / 2);
	init(2 * p + 1, (L + R) / 2 + 1, R);
	st[p] = st[2 * p] + st[2 * p + 1];
}

void update(int p, int L, int R, int u) {
	if (L == R) {
		st[p] = 0;
		return;
	}
	if (u <= (L + R) / 2)
		update(2 * p, L, (L + R) / 2, u);
	else
		update(2 * p + 1, (L + R) / 2 + 1, R, u);
	st[p] = st[2 * p] + st[2 * p + 1];
}

int query(int p, int L, int R, int u, int v) {
	if (v < L || R < u)
		return 0;
	if (u <= L && R <= v)
		return st[p];
	return query(2 * p, L, (L + R) / 2, u, v) +
		query(2 * p + 1, (L + R) / 2 + 1 , R, u, v);
}

#define at(i) ((i) == n ? 0 : query(1, 1, n, (i) + 1, n))

int lower_bound(int key) {
	int low = 1, high = n, mid;
	while (low < high) {
		mid = (low + high) >> 1;
		if (at(mid) <= key)
			high = mid;
		else
			low = mid + 1;
	}
	return low;
}

int main() {
	scanf("%d", &t);
	for (int no = 1; no <= t; no++) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		init(1, 1, n);
		vector<int> res;
		for (int i = n; i >= 1; i--) {
			res.push_back(lower_bound(a[i]));
			update(1, 1, n, res.back());
		}
		printf("Case %d: %d\n", no, res.back());
	}
	return 0;
}
