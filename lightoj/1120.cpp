#include <bits/stdc++.h>
using namespace std;

#define debug(x) cerr << #x " = " << (x) << '\n'
#define arr(x, n) {cerr<<#x<<" = "<<"["<<(n)<<"]"<<"(";for(ll _=0;_<(n);_++) cerr<<(x)[_]<<(_!=(n)-1?", ":")\n");}
#define iarr(x, m, n) {cerr<<#x":\n";for(ll _=(m);_<=(n);_++) cerr<<_<<": "<<(x)[_]<<'\n';}
#define err(...) fprintf(stderr, __VA_ARGS__)
#define SZ 30005

typedef long long ll;

struct Rectangle {
	ll x1, y1, x2, y2;
	void arrange() {
		if (x1 > x2) swap(x1, x2);
		if (y1 > y2) swap(y1, y2);
	}
};

struct Vertical {
	ll y_low, y_high, x;
	bool is_end;
};

struct Segment {
	ll low, high;
};

struct Node {
	ll sum_cover, n_cover;
	Node() { sum_cover = 0; n_cover = 0; }
};

Rectangle rect[SZ];
Vertical vert[4 * SZ];
Segment seg[4 * SZ];
Node st[8 * SZ];
ll n_rect, n_vert, t, n_seg;

bool vert_cmp(const Vertical& a, const Vertical& b) {
	return a.x < b.x;
}

void init(ll p, ll L, ll R) {
	st[p] = Node();
	if (L == R)
		return;
	init(2 * p, L, (L + R) / 2);
	init(2 * p + 1, (L + R) / 2 + 1, R);
}

void increase(ll p, ll L, ll R, ll u, ll v) {
	if (v <= seg[L].low || seg[R].high <= u) // not: v < seg[L].low || seg[R].high < u
		return;
	if (u <= seg[L].low && seg[R].high <= v) {
		st[p].n_cover++;
		st[p].sum_cover = seg[R].high - seg[L].low;
		return;
	}
	increase(2 * p, L, (L + R) / 2, u, v);
	increase(2 * p + 1, (L + R) / 2 + 1, R, u, v);
	if (st[p].n_cover == 0)
		st[p].sum_cover = st[2 * p].sum_cover + st[2 * p + 1].sum_cover;
}

void decrease(ll p, ll L, ll R, ll u, ll v) {
	if (v <= seg[L].low || seg[R].high <= u)
		return;
	if (u <= seg[L].low && seg[R].high <= v) {
		st[p].n_cover--;
		if (st[p].n_cover == 0) {
			if (L == R) // the most basic situation
				st[p].sum_cover = 0;
			else
				st[p].sum_cover = st[2 * p].sum_cover + st[2 * p + 1].sum_cover;
		}
		return;
	}
	decrease(2 * p, L, (L + R) / 2, u, v);
	decrease(2 * p + 1, (L + R) / 2 + 1, R, u, v);
	if (st[p].n_cover == 0)
		st[p].sum_cover = st[2 * p].sum_cover + st[2 * p + 1].sum_cover;
}

int main() {
	scanf("%lld", &t);
	for (ll no = 1; no <= t; no++) {
		scanf("%lld", &n_rect);
		n_vert = 0;
		set<ll> u;
		for (ll i = 1; i <= n_rect; i++) {
			scanf("%lld %lld %lld %lld",
				  &rect[i].x1, &rect[i].y1,
				  &rect[i].x2, &rect[i].y2);
			rect[i].arrange();

			vert[n_vert].y_low = rect[i].y1;
			vert[n_vert].y_high = rect[i].y2;
			vert[n_vert].x = rect[i].x1;
			vert[n_vert].is_end = false;
			n_vert++;

			vert[n_vert].y_low = rect[i].y1;
			vert[n_vert].y_high = rect[i].y2;
			vert[n_vert].x = rect[i].x2;
			vert[n_vert].is_end = true;
			n_vert++;

			u.insert(rect[i].y1);
			u.insert(rect[i].y2);
		}

		n_seg = 0;
		ll pX = -1;
		for (set<ll>::iterator it = u.begin(); it != u.end(); it++) {
			if (pX != -1) {
				seg[n_seg].low = pX;
				seg[n_seg].high = *it;
				n_seg++;

			}
			pX = *it;
		}
		sort(vert, vert + n_vert, vert_cmp);

		init(1, 0, n_seg - 1);

		ll ans = 0, prev_x = -1;
		for (ll i = 0; i < n_vert; i++) {
			if (prev_x != -1) {
				ans += st[1].sum_cover * (vert[i].x - prev_x);
			}
			if (!vert[i].is_end) {
				increase(1, 0, n_seg - 1, vert[i].y_low, vert[i].y_high);
			} else {
				decrease(1, 0, n_seg - 1, vert[i].y_low, vert[i].y_high);
			}
			prev_x = vert[i].x;
		}
		printf("Case %lld: %lld\n", no, ans);
	}
	return 0;
}
