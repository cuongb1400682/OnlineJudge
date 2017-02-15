#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define SZ 50000
#define INF 0x3f3f3f3f3f3f3f3fLL

struct Rectangle {
	ll x1, y1, x2, y2;
};

struct Vertical {
	ll y_min, y_max, x;
	bool is_end;
};

struct Node {
	ll cnt_cover, n_cover;
};

struct Segment {
	ll low, high;
};

ll t, n, k, n_vert, n_rect, n_seg;
Rectangle rect[SZ];
Vertical vert[2 * SZ];
Segment seg[4 * SZ];
Node st[8 * SZ];

bool vert_cmp(const Vertical& a, const Vertical& b) {
	return a.x < b.x;
}

void init(ll p, ll L, ll R) {
	st[p].cnt_cover = st[p].n_cover = 0;
	if (L == R)
		return;
	init(2 * p, L, (L + R) / 2);
	init(2 * p + 1, (L + R) / 2 + 1, R);
}

void count(ll p, ll L, ll R, ll u, ll v, ll zz) {
	if (seg[R].high <= u || seg[L].low >= v)
		return;
	if (zz + st[p].n_cover >= k)
		st[p].cnt_cover = seg[R].high - seg[L].low;
	else {
		if (L == R)
			st[p].cnt_cover = 0;
		else {
			count(2 * p, L, (L + R) / 2, u, v, zz + st[p].n_cover);
			count(2 * p + 1, (L + R) / 2 + 1, R, u, v, zz + st[p].n_cover);
			st[p].cnt_cover = st[2 * p].cnt_cover + st[2 * p + 1].cnt_cover;
		}
	}
}

void increase(ll p, ll L, ll R, ll u, ll v, ll zz) {
	if (seg[R].high <= u || seg[L].low >= v)
		return;
	if (u <= seg[L].low && seg[R].high <= v) {
		st[p].n_cover++;
		count(p, L, R, u, v, zz);
		return;
	}
	increase(2 * p, L, (L + R) / 2, u, v, zz + st[p].n_cover);
	increase(2 * p + 1, (L + R) / 2 + 1, R, u, v, zz + st[p].n_cover);
	if (zz + st[p].n_cover < k)
		st[p].cnt_cover = st[2 * p].cnt_cover + st[2 * p + 1].cnt_cover;
}

void decrease(ll p, ll L, ll R, ll u, ll v, ll zz) {
	if (seg[R].high <= u || seg[L].low >= v)
		return;
	if (u <= seg[L].low && seg[R].high <= v) {
		st[p].n_cover--;
		count(p, L, R, u, v, zz);
		return;
	}
	decrease(2 * p, L, (L + R) / 2, u, v, zz + st[p].n_cover);
	decrease(2 * p + 1, (L + R) / 2 + 1, R, u, v, zz + st[p].n_cover);
	if (zz + st[p].n_cover < k)
		st[p].cnt_cover = st[2 * p].cnt_cover + st[2 * p + 1].cnt_cover;
}

int main() {
	scanf("%lld", &t);
	for (ll no = 1; no <= t; no++) {
		scanf("%lld %lld", &n, &k);

		set<ll> uniq;		
		for (ll i = 0; i < n; i++) {
			scanf("%lld %lld %lld %lld",
				  &rect[i].x1, &rect[i].y1,
				  &rect[i].x2, &rect[i].y2);
			if (rect[i].x1 > rect[i].x2)
				swap(rect[i].x1, rect[i].x2);
			if (rect[i].y1 > rect[i].y2)
				swap(rect[i].y1, rect[i].y2);
			rect[i].x2++; rect[i].y2++;
			uniq.insert(rect[i].y1);
			uniq.insert(rect[i].y2);
		}

		n_seg = 0;
		ll prev_y = -1;
		for (set<ll>::iterator it = uniq.begin(); it != uniq.end(); it++) {
			if (prev_y != -1) {
				seg[n_seg].low = prev_y;
				seg[n_seg].high = *it;
				n_seg++;
			}
			prev_y = *it;
		}

		n_vert = 0;
		for (ll i = 0; i < n; i++) {
			vert[n_vert].y_min = rect[i].y1;
			vert[n_vert].y_max = rect[i].y2;
			vert[n_vert].is_end = false;
			vert[n_vert].x = rect[i].x1;
			n_vert++;

			vert[n_vert].y_min = rect[i].y1;
			vert[n_vert].y_max = rect[i].y2;
			vert[n_vert].is_end = true;
			vert[n_vert].x = rect[i].x2;
			n_vert++;
		}
		sort(vert, vert + n_vert, vert_cmp);

		ll prev_x = vert[0].x;
		ll ans = 0;
		init(1, 0, n_seg - 1);

		for (ll i = 0; i < n_vert; i++) {
			ans += (vert[i].x - prev_x) * st[1].cnt_cover;
			if (vert[i].is_end) {
				decrease(1, 0, n_seg - 1, vert[i].y_min, vert[i].y_max, 0);
			} else {
				increase(1, 0, n_seg - 1, vert[i].y_min, vert[i].y_max, 0);
			}
			prev_x = vert[i].x;
		}
		printf("Case %lld: %lld\n", no, ans);
	}	
	return 0;
}
