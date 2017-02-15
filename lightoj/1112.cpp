#include <bits/stdc++.h>
using namespace std;

#define debug(x) cerr << #x " = " << (x) << '\n'
#define arr(x, n) {cerr<<#x<<" = "<<"["<<(n)<<"]"<<"(";for(ll _=0;_<(n);_++) cerr<<(x)[_]<<(_!=(n)-1?", ":")\n");}
#define iarr(x, m, n) {cerr<<#x":\n";for(ll _=(m);_<=(n);_++) cerr<<_<<": "<<(x)[_]<<'\n';}
#define err(...) fprintf(stderr, __VA_ARGS__)
#define SZ 100005

typedef long long ll;

int n, q, t, sack[SZ], st[4 * SZ];

void init(int p, int L, int R) {
	st[p] = 0;
	if (L == R) {
		st[p] = sack[L];
		return;
	}
	init(2 * p, L, (L + R) / 2);
	init(2 * p + 1, (L + R) / 2 + 1, R);
	st[p] = st[2 * p] + st[2 * p + 1];
}

int clear_sack(int p, int L, int R, int index) {
	int ans;
	if (L == R) {
		ans = st[p];
		st[p] = 0;
		return ans;
	}
	if (index <= (L + R) / 2)
		ans = clear_sack(2 * p, L, (L + R) / 2, index);
	else
		ans = clear_sack(2 * p + 1, (L + R) / 2 + 1, R, index);
	st[p] = st[2 * p] + st[2 * p + 1];
	return ans;
}

void add_money(int p, int L, int R, int index, int value) {
	if (L == R) {
		st[p] += value;
		return;
	}
	if (index <= (L + R) / 2)
		add_money(2 * p, L, (L + R) / 2, index, value);
	else
		add_money(2 * p + 1, (L + R) / 2 + 1, R, index, value);
	st[p] = st[2 * p] + st[2 * p + 1];	
}

int query(int p, int L, int R, int u, int v) {
	if (v < L || R < u)
		return 0;
	if (u <= L && R <= v)
		return st[p];
	return query(2 * p, L, (L + R) / 2, u, v) +
		query(2 * p + 1, (L + R) / 2 + 1, R, u, v);
}

int main() {
	scanf("%d", &t);
	for (int no = 1; no <= t; no++) {
		scanf("%d %d", &n, &q);
		for (int i = 1; i <= n; i++)
			scanf("%d", &sack[i]);
		init(1, 1, n);
		printf("Case %d:\n", no);
		for (int i = 1; i <= q; i++) {
			int index, value, u, v, type;
			scanf("%d", &type);
			if (type == 1) {
				scanf("%d", &index);
				index++;
				printf("%d\n", clear_sack(1, 1, n, index));
			} else if (type == 2) {
				scanf("%d %d", &index, &value);
				index++;
				add_money(1, 1, n, index, value);
			} else {
				scanf("%d %d", &u, &v);
				u++; v++;
				printf("%d\n", query(1, 1, n, u, v));
			}
		}
	}
	return 0;
}
