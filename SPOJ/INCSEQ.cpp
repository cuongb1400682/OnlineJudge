#include <stdio.h>
#include <string.h>
#include <math.h>
#include <map>
using namespace std;

#define MOD 5000000
#define SZ 100002

typedef int ll;

ll st[51][4 * SZ], a[10005], n, k;

ll query(ll *st, ll p, ll L, ll R, ll u, ll v) {
	if (v < L || R < u || u > v)
		return 0;
	if (u <= L && R <= v) {
		return st[p] % MOD;
	}
	ll mid = (L + R) >> 1;
	return (query(st, 2 * p, L, mid, u, v) +
			query(st, 2 * p + 1, mid + 1, R, u, v)) % MOD;
}

void increase(ll *st, ll p, ll L, ll R, ll u, ll value) {
	if (L == R) {
		st[p] += value;
		st[p] %= MOD;
		return;
	}
	ll mid = (L + R) >> 1;
	if (u <= mid)
		increase(st, 2 * p, L, mid, u, value);
	else
		increase(st, 2 * p + 1, mid + 1, R, u, value);
	st[p] = (st[2 * p] + st[2 * p + 1]) % MOD;
}

int main() {
	scanf("%d %d", &n, &k);
	map<ll, ll> z;
	for (ll i = 1; i <= n; i++) {
		scanf("%d",  &a[i]);
		z[a[i]] = -1;
	}
	ll cnt = 0;
	for (map<ll, ll>::iterator it = z.begin(); it != z.end(); it++) {
		if (z[it->first] == -1)
			z[it->first] = ++cnt;
	}
	for (ll i = 1; i <= n; i++) 
		a[i] = z[a[i]];
	memset(st, 0, sizeof(st));
	for (ll i = 1; i <= n; i++) {
		increase(st[1], 1, 0, SZ, a[i], 1);
		for (ll j = 2; j <= k; j++) {
			ll tmp = query(st[j - 1], 1, 0, SZ, 0, a[i] - 1);
			increase(st[j], 1, 0, SZ, a[i], tmp);
		}
	}
	printf("%d\n", st[k][1]);
	return 0;
}

