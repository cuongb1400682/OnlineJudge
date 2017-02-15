#include <bits/stdc++.h>
using namespace std;

#define debug(x) cerr << #x " = " << (x) << '\n'
#define arr(x, n) {cerr<<#x<<" = "<<"["<<(n)<<"]"<<"(";for(ll _=0;_<(n);_++) cerr<<(x)[_]<<(_!=(n)-1?", ":")\n");}
#define iarr(x, m, n) {cerr<<#x":\n";for(ll _=(m);_<=(n);_++) cerr<<_<<": "<<(x)[_]<<'\n';}
#define err(...) fprintf(stderr, __VA_ARGS__)
#define SZ 30005
#define INF 0x3f3f3f3f

typedef long long ll;
typedef short int si;

int a[SZ], n, st[4 * SZ];

int init(const int *a, int p, int L, int R) {
	if (L == R) {
		return st[p] = a[L];
	}
	init(a, 2 * p, L, (L + R) / 2);
	init(a, 2 * p + 1, (L + R) / 2 + 1, R);
	st[p] = min(st[2 * p], st[2 * p + 1]);
}

int query(int p, int L, int R, int u, int v) {
	if (v < L || R < u)
		return INF;
	if (u <= L && R <= v)
		return st[p];
	return min(query(2 * p, L, (L + R) / 2, u, v),
			   query(2 * p + 1, (L + R) / 2 + 1, R, u, v));
}

int get_min(int u, int v) {
	if (u > v) swap(u, v);
	return query(1, 1, n, u, v);
}

int lw_bnd(int idx) {
	int lo = 1, hi = idx, mid, key = a[idx];
	while (lo < hi) {
		mid = (lo + hi) >> 1;
		if (get_min(mid, idx) >= key)
			hi = mid;
		else
			lo = mid + 1;
	}
	return lo;
}

int up_bnd(int idx) {
	int lo = idx, hi = n, mid, key = a[idx];
	while (lo < hi) {
		mid = (lo + hi) >> 1;
		if (get_min(idx, mid) >= key)
			lo = mid + 1;
		else
			hi = mid;
	}
	return lo;
}

int main() {
	int t;
	scanf("%d", &t);
	for (int no = 1; no <= t; no++) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		init(a, 1, 1, n);
		int ans = 0;
		for (int i = 1; i <= n; i++) {
			int lo = lw_bnd(i);
			int hi = up_bnd(i);
			if (hi > 1 && a[hi] < a[i])
				hi--;
			int S = (hi - lo + 1) * a[i];
			ans = max(ans, S);
		}
		printf("Case %d: %d\n", no, ans);
	}
	return 0;
}

