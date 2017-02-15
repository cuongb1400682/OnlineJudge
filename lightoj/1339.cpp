#include <bits/stdc++.h>
using namespace std;

#define debug(x) cerr << #x " = " << (x) << '\n'
#define arr(x, n) {cerr<<#x<<" = "<<"["<<(n)<<"]"<<"(";for(ll _=0;_<(n);_++) cerr<<(x)[_]<<(_!=(n)-1?", ":")\n");}
#define iarr(x, m, n) {cerr<<#x":\n";for(ll _=(m);_<=(n);_++) cerr<<_<<": "<<(x)[_]<<'\n';}
#define err(...) fprintf(stderr, __VA_ARGS__)
#define SZ 100005
#define INF 0x3f3f3f3f

typedef long long ll;

struct segment {
	int x, y;
} segs[SZ];

int n, c, q, t, cnt_left[SZ], cnt_right[SZ], a[SZ], st[4 * SZ], n_segs, base[SZ];

void init(int p, int L, int R) {
	st[p] = -1;
	if (L == R) {
		st[p] = segs[L].y - segs[L].x + 1;
		return;
	}
	init(2 * p, L, (L + R) / 2);
	init(2 * p + 1, (L + R) / 2 + 1, R);
	st[p] = max(st[2 * p], st[2 * p + 1]);
}

int query(int p, int L, int R, int u, int v) {
	if (v < L || R < u)
		return -1;
	if (u <= L && R <= v)
		return st[p];
	return max(query(2 * p, L, (L + R) / 2, u, v),
			   query(2 * p + 1, (L + R) / 2 + 1, R, u, v));
}

int main() {
	scanf("%d", &t);
	for (int no = 1; no <= t; no++) {
		scanf("%d %d %d", &n, &c, &q);

		memset(cnt_left, 0, sizeof(cnt_left));
		memset(cnt_right, 0, sizeof(cnt_right));

		a[0] = a[n + 1] = 0;
		n_segs = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			if (a[i] != a[i - 1]) {
				cnt_left[i] = 1;
				if (i > 1) {
					segs[n_segs].x = i - cnt_left[i - 1];
					segs[n_segs].y = i - 1;
					n_segs++;
				}
			} else {
				cnt_left[i] = cnt_left[i - 1] + 1;
			}
			base[i] = n_segs;
		}
		
		segs[n_segs].x = n - cnt_left[n - 1];
		segs[n_segs].y = n;
		n_segs++;

		for (int i = n; i >= 1; i--) {
			if (a[i] != a[i + 1])
				cnt_right[i] = 1;
			else
				cnt_right[i] = cnt_right[i + 1] + 1;
		}

		init(1, 0, n_segs - 1);
		printf("Case %d:\n", no);
		for (int i = 1; i <= q; i++) {
			int u, v, ans;
			scanf("%d %d", &u, &v);
			if (base[v] - base[u] > 1) { // #seg is greater than or equal to 3
				ans = max(cnt_right[u], cnt_left[v]);
				ans = max(ans, query(1, 0, n_segs - 1, base[u] + 1, base[v] - 1));
				printf("%d\n", ans);
			} else if (base[v] == base[u]) { // #seg is equal to 1
				printf("%d\n", abs(cnt_left[v] - cnt_left[u]) + 1);
			} else { // 2
				printf("%d\n", max(cnt_right[u], cnt_left[v]));
			}
		}
	}
	return 0;
}
