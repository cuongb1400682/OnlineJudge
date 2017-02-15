#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <string.h>

using namespace std;

#define SZ 100005
#define MOD 1000000007LL
#define INF 0x3f3f3f3f3f3f3f3fLL

typedef long long ll;

struct Node {
    ll min, max, lazy;
    Node() {
	min = INF;
	max = -INF;
	lazy = 0;
    }
    Node(ll value) {
	max = min = value;
	lazy = 0;
    }
};

Node st[4 * SZ];
ll a[SZ], n, m, lcm[300003];
vector<ll> L;
bool is_prime[300005];

Node mix(Node a, Node b) {
    Node ans;
    ans.min = min(a.min, b.min);
    ans.max = max(a.max, b.max);
    return ans;
}

void apply(Node& a, ll value) {
    a.lazy += value;
    a.min += value;
    a.max += value;
}

void propagate(ll p, ll L, ll R) {
    ll& lazy = st[p].lazy;
    if (lazy != 0) {
	apply(st[2 * p], lazy);
	apply(st[2 * p + 1], lazy);
    }
    lazy = 0;
}

void init(ll p, ll L, ll R) {
    st[p] = Node();
    if (L == R) {
	st[p] = Node(a[L]);
	return;
    }
    ll mid = (L + R) >> 1;
    init(2 * p, L, mid);
    init(2 * p + 1, mid + 1, R);
    st[p] = mix(st[2 * p], st[2 * p + 1]);
}

Node query(ll p, ll L, ll R, ll u, ll v) {
    if (v < L || R < u)
	return Node();
    if (u <= L && R <= v)
	return st[p];
    propagate(p, L, R);
    ll mid = (L + R) >> 1;
    return mix(query(2 * p, L, mid, u, v),
	       query(2 * p + 1, mid + 1, R, u, v));
}

void update(ll p, ll L, ll R, ll u, ll v, ll value) {
    if (v < L || R < u)
	return;
    if (u <= L && R <= v) {
	apply(st[p], value);
	return;
    }
    propagate(p, L, R);
    ll mid = (L + R) >> 1;
    update(2 * p, L, mid, u, v, value);
    update(2 * p + 1, mid + 1, R, u, v, value);
    st[p] = mix(st[2 * p], st[2 * p + 1]);
}

ll pow_mod(ll a, ll b) {
    ll ans = 1LL;
    while (b > 0) {
	if (b & 1)
	    ans = ans * a % MOD;
	a = a * a % MOD;
	b >>= 1;
    }
    return ans;
}

void prepare_prime_list() {
    ll n = 300005;
    ll sqrt_n = (ll) sqrt(n);
    
    L.clear();    
    memset(is_prime, true, sizeof(is_prime));
    is_prime[0] = is_prime[1] = false;
    
    for (ll i = 2; i <= sqrt_n; i++) 
	if (is_prime[i]) {
	    for (ll j = i * i; j <= n; j += i)
		is_prime[j] = false;
	}
    
    for (ll i = 2; i <= n; i++)
	if (is_prime[i])
	    L.push_back(i);
}

void prepare_lcm() {
    static int pw[300005];
    ll tt = 1;
    memset(pw, 0, sizeof(pw));
    lcm[0] = 0;
    lcm[1] = 1;
    for (ll i = 2; i <= 300000; i++) {
	for (ll j = i, h = 0; j > 1; ) {
	    if (is_prime[j]) {
		if (pw[j] < 1) {
		    pw[j] = 1;
		    tt = tt * j % MOD;
		}
		break;
	    }
	    
	    ll cnt = 0;
	    while (j % L[h] == 0) {
		j /= L[h];
		cnt++;
	    }
	    
	    if (pw[L[h]] < cnt) {
		tt = tt * pow_mod(L[h], cnt - pw[L[h]]) % MOD;
		pw[L[h]] = cnt;
	    }
	    
	    h++;
	}
	lcm[i] = tt;
    }
}

int main() {
    prepare_prime_list();
    prepare_lcm();

    scanf("%lld %lld", &n, &m);
    for (ll i = 1; i <= n; i++)
	scanf("%lld", &a[i]);
    
    init(1, 1, n);
    
    ll type, u, v, p;
    for (ll i = 1; i <= m; i++) {
	scanf("%lld %lld %lld", &type, &u, &v);
	u++, v++;
	if (type == 0) {
	    scanf("%lld", &p);
	    update(1, 1, n, u, v, p);
	} else if (type == 1) {
	    printf("%lld\n", lcm[query(1, 1, n, u, v).max]);
	} else if (type == 2) {
	    printf("%lld\n", lcm[query(1, 1, n, u, v).min]);
	}
    }
    return 0;
}
