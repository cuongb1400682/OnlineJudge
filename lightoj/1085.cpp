#include <bits/stdc++.h>
using namespace std;

#define debug(x) cerr << #x " = " << (x) << '\n'
#define arr(x, n) {cerr<<#x<<" = "<<"["<<(n)<<"]"<<"(";for(ll _=0;_<(n);_++) cerr<<(x)[_]<<(_!=(n)-1?", ":")\n");}
#define iarr(x, m, n) {cerr<<#x":\n";for(ll _=(m);_<=(n);_++) cerr<<_<<": "<<(x)[_]<<'\n';}
#define err(...) fprintf(stderr, __VA_ARGS__)
#define SZ 100005LL
#define MOD 1000000007LL

typedef long long ll;

ll st[4 * SZ], a[SZ], n, d[SZ], n_d;

void init(ll p, ll L, ll R) {
	st[p] = 0;
	if (L == R)
		return;
	init(2 * p, L, (L + R) / 2);
	init(2 * p + 1, (L + R) / 2 + 1, R);
}

ll query(ll p, ll L, ll R, ll u, ll v) {
	if (v < L || R < u)
		return 0LL;
	if (u <= L && R <= v)
		return st[p];
	return (query(2 * p, L, (L + R) / 2, u, v) +
			query(2 * p + 1, (L + R) / 2 + 1, R, u, v)) % MOD;
}

void update(ll p, ll L, ll R, ll u, ll val) {
	if (L == R) {
		(st[p] += val) %= MOD;
		return;
	}
	if (u <= d[(L + R) / 2])
		update(2 * p, L, (L + R) / 2, u, val);
	else
		update(2 * p + 1, (L + R) / 2 + 1, R, u, val);
	st[p] = (st[2 * p] + st[2 * p + 1]) % MOD;
}

void pr() {
	for (ll i = 0; i <= n_d; i++)
		err("%lld ", query(1, 1, n_d, i, i));
	err("\n");
}

int bf() {
	ll ans = 0;
	for (ll i = 1; i <= (1 << n) - 1; i++) {
		ll j = 1, sta;
		vector<ll> s;
		for (sta = i; sta > 0; sta >>= 1) {
			if (sta & 1) {
				if (!s.empty() && a[j] <= s.back())
					break;
				s.push_back(a[j]);
			}
			j++;
		}
		if (sta == 0) {
			ans++;
			err("%lld: ", ans);
			arr(s.data(), s.size());
		}
	}
}

int main() {
	ll t;
	scanf("%lld", &t);
	for (ll no = 1; no <= t; no++) {
		scanf("%lld", &n);
		set<ll> h;
		for (ll i = 1; i <= n; i++) {
			scanf("%lld", &a[i]);
			h.insert(a[i]);
		}


		n_d = 0;
		for (set<ll>::iterator it = h.begin(); it != h.end(); it++)
			d[++n_d] = *it;
		init(1, 1, n_d);

		for (ll i = 1; i <= n; i++) {
			ll p = lower_bound(d + 1, d + n_d + 1, a[i]) - d;
			ll f_p = (query(1, 1, n_d, 0, p - 1LL) + 1LL) % MOD;
			update(1, 1, n_d, d[p], f_p);
		}

		printf("Case %lld: %lld\n", no, query(1, 1, n_d, 1, n_d));
	}
	return 0;
}
