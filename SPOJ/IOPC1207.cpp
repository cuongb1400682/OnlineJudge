#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

typedef long long ll;

#define SZ 100005

struct Node {
	ll sum;
	bool lazy;
	Node() {
		lazy = sum = 0;
	}
};

Node st_x[4 * SZ], st_y[4 * SZ], st_z[4 * SZ];
ll t, nx, ny, nz;

void propagate(Node *st, ll p, ll L, ll R) {
	ll right_len = (R - L + 1) >> 1;
	ll left_len = right_len + ((R - L + 1) & 1);
	st[2 * p].lazy = !st[2 * p].lazy;
	st[2 * p].sum = left_len - st[2 * p].sum;
	st[2 * p + 1].lazy = !st[2 * p + 1].lazy;
	st[2 * p + 1].sum = right_len - st[2 * p + 1].sum;
	st[p].lazy = false;
}

void invert(Node *st, ll p, ll L, ll R, ll u, ll v) {
	if (v < L || R < u)
		return;
	if (u <= L && R <= v) {
		st[p].sum = R - L + 1 - st[p].sum;
		st[p].lazy = !st[p].lazy;
		return;
	}
	if (st[p].lazy)
		propagate(st, p, L, R);
	ll mid = (L + R) >> 1;
	invert(st, 2 * p, L, mid, u, v);
	invert(st, 2 * p + 1, mid + 1, R, u, v);
	st[p].sum = st[2 * p].sum + st[2 * p + 1].sum;
}

ll get_sum(Node *st, ll p, ll L, ll R, ll u, ll v) {
	if (v < L || R < u)
		return 0;
	if (u <= L && R <= v)
		return st[p].sum;
	if (st[p].lazy)
		propagate(st, p, L, R);
	ll mid = (L + R) >> 1;
	return get_sum(st, 2 * p, L, mid, u, v) +
		get_sum(st, 2 * p + 1, mid + 1, R, u, v);
}

ll x, y, x1, y1, z1, x2, y2, z2, q, type;
int main() {
	scanf("%lld", &t);
	while (t--) {
		memset(st_x, 0, sizeof(st_x));
		memset(st_y, 0, sizeof(st_y));
		memset(st_z, 0, sizeof(st_z));
		scanf("%lld %lld %lld %lld", &nx, &ny, &nz, &q);
		while (q--) {
			scanf("%lld %lld %lld", &type, &x1, &y1);
			x1++, y1++;
			if (type == 3) {
				scanf("%lld %lld %lld %lld", &z1, &x2, &y2, &z2);
				z1++, x2++, y2++, z2++;
				ll Hx = get_sum(st_x, 1, 1, nx, x1, x2);
				ll Hy = get_sum(st_y, 1, 1, ny, y1, y2);
				ll Hz = get_sum(st_z, 1, 1, nz, z1, z2);
				ll dx = abs(x1 - x2) + 1;
				ll dy = abs(y1 - y2) + 1;
				ll dz = abs(z1 - z2) + 1;
				ll V1 = Hz * (dy - Hy) * (dx - Hx);
				ll V2 = Hy * (dz - Hz) * (dx - Hx);
				ll V3 = Hx * (dz - Hz) * (dy - Hy);
				printf("%lld\n", V1 + V2 + V3 + Hx * Hy * Hz);
			} else if (type == 0) {
				invert(st_x, 1, 1, nx, x1, y1);
			} else if (type == 1) {
				invert(st_y, 1, 1, ny, x1, y1);
			} else if (type == 2) {
				invert(st_z, 1, 1, nz, x1, y1);
			}
		}
	}
	return 0;
}
