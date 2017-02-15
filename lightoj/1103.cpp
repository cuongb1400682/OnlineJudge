#include <bits/stdc++.h>
using namespace std;

#define debug(x) cerr << #x " = " << (x) << '\n'
#define arr(x, n) {cerr<<#x<<" = "<<"["<<(n)<<"]"<<"(";for(ll _=0;_<(n);_++) cerr<<(x)[_]<<(_!=(n)-1?", ":")\n");}
#define iarr(x, m, n) {cerr<<#x":\n";for(ll _=(m);_<=(n);_++) cerr<<_<<": "<<(x)[_]<<'\n';}
#define err(...) fprintf(stderr, __VA_ARGS__)

#define MAX_N 100005

typedef long long ll;

struct Segment {
	bool is_red;
	ll x, y;
	Segment(ll x = 0, ll y = 0, bool is_red = false):
		x(x), y(y), is_red(is_red) { }
};

vector<Segment> seg;
ll t, n, m, st[8 * MAX_N];

bool seg_cmp(const Segment& a, const Segment& b) {
	return a.x < b.x;
}

void increase(ll p, ll L, ll R, ll u) {
	if (L == R) {
		st[p]++;
		return;
	}
	ll mid = (L + R) >> 1;
	if (u <= mid)
		increase(2 * p, L, mid, u);
	else
		increase(2 * p + 1, mid + 1, R, u);
	st[p] = st[2 * p] + st[2 * p + 1];
}

ll get_sum(ll p, ll L, ll R, ll u, ll v) {
	if (v < L || R < u)
		return 0;
	if (u <= L && R <= v)
		return st[p];
	ll mid = (L + R) >> 1;
	return get_sum(2 * p, L, mid, u, v) +
			get_sum(2 * p + 1, mid + 1, R, u, v);
}
 
int main() {
	scanf("%lld", &t);
	for (ll no = 1; no <= t; no++) {
		scanf("%lld %lld", &n, &m);

		seg.clear();

		for (ll i = 0, u, v; i < n; i++) {
			scanf("%lld %lld", &u, &v);
			seg.push_back(Segment(u, v, true));
		}

		for (ll i = 0, u, v; i < m; i++) {
			scanf("%lld %lld", &u, &v);
			seg.push_back(Segment(u, v, false));
		}
		
		sort(seg.begin(), seg.end(), seg_cmp);

		memset(st, 0, sizeof(st));
		ll ans = 0;
		for (ll i = 0; i < seg.size(); i++) {
			if (seg[i].is_red) {
				increase(1, 0, n + m, seg[i].y);
			} else {
				ans += get_sum(1, 0, n + m, seg[i].y, n + m);
			}
		}

		memset(st, 0, sizeof(st));
		for (ll i = seg.size() - 1; i >= 0; i--) {
			if (seg[i].is_red) {
				increase(1, 0, n + m, seg[i].y);
			} else {
				ans += get_sum(1, 0, n + m, 0, seg[i].y);
			}
		}

		printf("Case %lld: %lld\n", no, ans);
	}
	return 0;
}
