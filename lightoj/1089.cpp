#include <bits/stdc++.h>
using namespace std;

#define debug(x) cerr << #x " = " << (x) << '\n'
#define arr(x, n) {cerr<<#x<<" = "<<"["<<(n)<<"]"<<"(";for(ll _=0;_<(n);_++) cerr<<(x)[_]<<(_!=(n)-1?", ":")\n");}
#define iarr(x, m, n) {cerr<<#x":\n";for(ll _=(m);_<=(n);_++) cerr<<_<<": "<<(x)[_]<<'\n';}
#define err(...) fprintf(stderr, __VA_ARGS__)
#define MAX_N 50005
nnn#define MAX_Q 50005
#define INF 0x3f3f3f3f

typedef long long ll;

struct Segment {
	ll x, y;
	Segment(ll x = 0, ll y = 0) : x(x), y(y) { };
};

vector<ll> pt, query;
vector<Segment> seg, origin;
ll t, n, q, st[25 * MAX_N];

void init(ll p, ll L, ll R) {
	st[p] = 0;
	if (L == R)
		return;
	ll mid = (L + R) >> 1;
	init(2 * p, L, mid);
	init(2 * p + 1, mid + 1, R);
}

void increase(ll p, ll L, ll R, ll u, ll v) {
	if (v < seg[L].x || seg[R].y < u)
		return;
	if (u <= seg[L].x && seg[R].y <= v) {
		st[p]++;
		return;
	}
	ll mid = (L + R) >> 1;
	increase(2 * p, L, mid, u, v);
	increase(2 * p + 1, mid + 1, R, u, v);	
}

ll count_cover(ll p, ll L, ll R, ll u) {
	if (L == R)
		return st[p];
	ll mid = (L + R) >> 1;
	if (u <= seg[mid].y)
		return st[p] + count_cover(2 * p, L, mid, u);
	else
		return st[p] + count_cover(2 * p + 1, mid + 1, R, u);
}

int main() {
	scanf("%lld", &t);
	for (ll no = 1; no <= t; no++) {
		scanf("%lld %lld", &n, &q);
		
		set<ll> uniq;

		origin.clear();
		for (ll i = 1, u, v; i <= n; i++) {
			scanf("%lld %lld", &u, &v);
			uniq.insert(u);
			uniq.insert(v);
			origin.push_back(Segment(u, v));
		}

		query.clear();
		for (ll i = 1, v; i <= q; i++) {
			scanf("%lld", &v);
			query.push_back(v);
			uniq.insert(v);
		}

		pt.clear();
		for (set<ll>::iterator it = uniq.begin(); it != uniq.end(); it++)
			pt.push_back(*it);

		seg.clear();
		for (ll i = 1; i < (ll) pt.size(); i++) {
			seg.push_back(Segment(pt[i - 1], pt[i - 1]));
			if (pt[i] - pt[i - 1] > 1)
				seg.push_back(Segment(pt[i - 1] + 1, pt[i] - 1));
		}
		seg.push_back(Segment(pt.back(), pt.back()));

		init(1, 0, seg.size() - 1);
		for (ll i = 0; i < (ll) origin.size(); i++)
			increase(1, 0, seg.size() - 1, origin[i].x, origin[i].y);

		printf("Case %lld:\n", no);
		for (ll i = 0; i < (ll) query.size(); i++)
			printf("%lld\n", count_cover(1, 0, seg.size() - 1, query[i]));
	}
	return 0;
}
