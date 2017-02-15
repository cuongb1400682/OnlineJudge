#include <stdio.h>
#include <utility>
using namespace std;

#define SZ 200005
#define MOD 10007LL

typedef long long ll;

struct triple {
	ll first, second, third;
	triple(ll first, ll second, ll third) {
		this->first = first;
		this->second = second;
		this->third = third;
	}
	triple() {
		first = second = third = 0;
	}
};

struct Node {
	// sum is divided into 3 sub kinds of sum because the origin sum is too large
	// sa - (a1 + a2 + a3 + ...) * sum_2
	// sb - (b1 + b2 + b3 + ...) * sum_1
	// sc - (c1 + c2 + c3 + ...)
	ll a, b, c, sa, sb, sc; // sa + sb + sc = sum
	bool is_lazy;
	Node() {
		a = b = c = 0;
		sa = sb = sc = 0;
		is_lazy = false;
	}
};

Node st[4 * SZ];
ll dp[SZ], n, m;

void init(ll p, ll L, ll R) {
	st[p] = Node();
	if (L == R)
		return;
	ll mid = (L + R) >> 1;
	init(2 * p, L, mid);
	init(2 * p + 1, mid + 1, R);
}

// L^2 + (L + 1)^2 + ... + R^2
ll sum_2(ll L, ll R) {
	if (L > R) swap(L, R);
	if (L == 0)
		return dp[R];
	else
		return (dp[R] - dp[L - 1]) % MOD;
}

// L + (L + 1) + (L + 2) + ... + R
ll sum_1(ll L, ll R) {
	if (L > R) swap(L, R);
	ll n = R - L;
	return (L * (n + 1) % MOD + (n * (n + 1) / 2) % MOD) % MOD;
}

Node mix(Node a, Node b) {
	Node ans;
	ans.sa = (a.sa + b.sa) % MOD;
	ans.sb = (a.sb + b.sb) % MOD;
	ans.sc = (a.sc + b.sc) % MOD;
	return ans;
}

void apply(ll p, ll L, ll R, ll a, ll b, ll c) {
	st[p].sa = (st[p].sa + a * sum_2(L, R)) % MOD;
	st[p].sb = (st[p].sb + b * sum_1(L, R)) % MOD;
	st[p].sc = (st[p].sc + c * (R - L + 1)) % MOD;
	st[p].a += a;
	st[p].b += b;
	st[p].c += c;
	st[p].is_lazy = true;
}

void propagate(ll p, ll L, ll R) {
	ll& a = st[p].a;
	ll& b = st[p].b;
	ll& c = st[p].c;
	ll mid = (L + R) >> 1;
	if (st[p].is_lazy) {
		apply(2 * p, L, mid, a, b, c);
		apply(2 * p + 1, mid + 1, R, a, b, c);
		st[p].is_lazy = false;
		a = b = c = 0;
	}
}

void update(ll p, ll L, ll R, ll u, ll v, ll a, ll b, ll c) {
	if (v < L || R < u)
		return;
	if (u <= L && R <= v) {
		apply(p, L, R, a, b, c);
		return;
	}
	propagate(p, L, R);
	ll mid = (L + R) >> 1;
	update(2 * p, L, mid, u, v, a, b, c);
	update(2 * p + 1, mid + 1, R, u, v, a, b, c);
	st[p] = mix(st[2 * p], st[2 * p + 1]);
}

triple operator+ (triple a, triple b) {
	triple c;
	c.first = (a.first + b.first) % MOD;
	c.second = (a.second + b.second) % MOD;
	c.third = (a.third + b.third) % MOD;
	return c;
}

triple get_sum(ll p, ll L, ll R, ll u, ll v) {
	if (v < L || R < u)
		return triple();
	if (u <= L && R <= v)
		return triple(st[p].sa, st[p].sb, st[p].sc);
	propagate(p, L, R);
	ll mid = (L + R) >> 1;
	return get_sum(2 * p, L, mid, u, v) +
			get_sum(2 * p + 1, mid + 1, R, u, v);
}

int main() {
	for (long long i = 1; i < SZ; i++)
		dp[i] = dp[i - 1] + i * i;
	scanf("%lld %lld", &n, &m);
	init(1, 0, n);
	ll type, x0, x1, a, b, c;
	for (ll i = 1; i <= m; i++) {
		scanf("%lld %lld %lld", &type, &x0, &x1);
		if (type == 0) {
			scanf("%lld %lld %lld", &a, &b, &c);
			update(1, 0, n, x0, x1, a, b, c);
		} else {
			triple t = get_sum(1, 0, n, x0, x1);
			printf("%lld\n", (t.first + t.second + t.third) % MOD);
		}
	}
	return 0;
}
