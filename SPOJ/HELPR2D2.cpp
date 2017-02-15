#include <stdio.h>
#include <ctype.h>
#include <set>
using namespace std;

typedef long long ll;

#define cap first
#define idx second
#define INF 0x3f3f3f3f3f3f3f3fLL

set<ll> a[1001];
pair<ll, ll> st[4 * 1001];
ll t, K, n;

void init(ll p, ll L, ll R) {
	st[p] = pair<ll, ll>(INF, INF);
	if (L == R) {
		a[L].clear();
		return;
	}
	ll mid = (L + R) >> 1;
	init(2 * p, L, mid);
	init(2 * p + 1, mid + 1, R);
}

pair<ll, ll> mix(pair<ll, ll> a, pair<ll, ll> b) {
	return (a.idx < b.idx ? a : b);
}

pair<ll, ll> query(ll p, ll L, ll R, ll u, ll v) {
	if (v < L || R < u)
		return make_pair(INF, INF);
	if (u <= L && R <= v)
		return st[p];
	ll mid = (L + R) >> 1;
	pair<ll, ll> left_ans = query(2 * p, L, mid, u, v);
	pair<ll, ll> right_ans = query(2 * p + 1, mid + 1, R, u, v);
	return mix(left_ans, right_ans);
}

void insert(ll p, ll L, ll R, ll cap, ll idx) {
	if (L == R) {
		a[L].insert(idx);
		st[p] = make_pair(cap, *a[L].begin());
		return;
	}
	ll mid = (L + R) >> 1;
	if (cap <= mid)
		insert(2 * p, L, mid, cap, idx);
	else
		insert(2 * p + 1, mid + 1, R, cap, idx);
	st[p] = mix(st[2 * p], st[2 * p + 1]);
}

void erase(ll p, ll L, ll R, ll cap, ll idx) {
	if (L == R) {
		a[L].erase(idx);
		st[p] = (a[L].empty() ?
				 make_pair(INF, INF) :
				 make_pair(cap, *a[L].begin()));
		return;
	}
	ll mid = (L + R) >> 1;
	if (cap <= mid)
		erase(2 * p, L, mid, cap, idx);
	else
		erase(2 * p + 1, mid + 1, R, cap, idx);
	st[p] = mix(st[2 * p], st[2 * p + 1]);
}

void load_container(ll v) {
	pair<ll, ll> t = query(1, 1, K, v, K);
	erase(1, 1, K, t.cap, t.idx);
	if (t.cap > v)
		insert(1, 1, K, t.cap - v, t.idx);
}

int main() {
	char *p, buf[256];
	ll r, v;
	scanf("%lld", &t);
	while (t--) {
		scanf("%lld %lld\n", &K, &n);
		init(1, 1, K);
		for (ll i = 1; i <= n; i++)
			insert(1, 1, K, K, i);
		ll i = 1;
		while (i <= n) {
			scanf("%s", buf);
			if (*buf == 'b') {
				scanf("%lld %lld", &r, &v);
				i += r;
				while (r--)
					load_container(v);
			} else {
				i++;
				sscanf(buf, "%lld", &v);
				load_container(v);				
			}
		}

		ll cnt = 0;
		for (ll i = 1; i <= K - 1; i++)
			if (a[i].size() > 0) {
				cnt += i * a[i].size();
			}
		
		printf("%lld %lld\n", n - (ll) a[K].size(), cnt);
	}
	return 0;
}
