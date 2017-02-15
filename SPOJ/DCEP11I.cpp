#include <stdio.h>
#include <string>

using std::string;

#define SZ 100005

typedef long long ll;

struct Node {
  ll n, delta, sum;
  Node() {
    n = delta = sum = 0;
  }
};

Node st[4 * SZ];
ll n, m;

void init(ll p, ll l, ll r) {
  st[p] = Node();
  if (l == r)
    return;
  ll mid = (l + r) / 2;
  init(2 * p, l, mid);
  init(2 * p + 1, mid + 1, r);
}

ll get_sum(ll n) {
  return n * (n + 1) / 2;
}

void apply(ll p, ll l, ll r, ll n, ll delta) {
  st[p].sum += n * get_sum(r - l + 1) + delta * (r - l + 1) ;
  st[p].n += n;
  st[p].delta += delta ;
}

void propagate(ll p, ll l, ll r) {
  if (st[p].n != 0) {
    ll mid = (l + r) / 2;
    apply(2 * p, l, mid, st[p].n, st[p].delta);
    ll tmp = mid - l + 1; // distance from mid to l
    st[p].delta += st[p].n * tmp;
    apply(2 * p + 1, mid + 1, r, st[p].n, st[p].delta);
  }
  st[p].n = st[p].delta = 0;
}

void update(ll p, ll l, ll r, ll u, ll v, ll delta) {
  if (v < l || r < u)
    return;
  if (u <= l && r <= v) {
    apply(p, l, r, 1, delta);
    return;
  }
  ll mid = (l + r) / 2;
  propagate(p, l, r);
  if (v <= mid)
    update(2 * p, l, mid, u, v, delta);
  else if (mid + 1 <= u)
    update(2 * p + 1, mid + 1, r, u, v, delta);
  else {
    update(2 * p, l, mid, u, mid, delta);
    delta += (mid - u + 1); // distance from mid to u
    update(2 * p + 1, mid + 1, r, mid + 1, v, delta);
  }
  st[p].sum = st[2 * p].sum + st[2 * p + 1].sum;
}

ll query(ll p, ll l, ll r, ll u, ll v) {
  if (v < l || r < u)
    return 0;
  if (u <= l && r <= v)
    return st[p].sum;
  propagate(p, l, r);
  ll mid = (l + r) / 2;
  return query(2 * p, l, mid, u, v) +
    query(2 * p + 1, mid + 1, r, u, v);
}

void debug(ll p, ll l, ll r, string i = "") {
  printf("%s[%lld, %lld] -> (sum = %lld, n = %lld, d = %lld)\n",
	 i.c_str(), l, r, st[p].sum, st[p].n, st[p].delta);
  if (l == r)
    return;
  ll mid = (l + r) / 2;
  debug(2 * p, l, mid, i + "   .");
  debug(2 * p + 1, mid + 1, r, i + "   .");
}

int main() {
  scanf("%lld %lld", &n, &m);
  init(1, 1, n);
  ll type, u, v;
  for (ll i = 1; i <= m; i++) {
    scanf("%lld %lld %lld", &type, &u, &v);
    if (type == 0) {
      update(1, 1, n, u, v, 0);
    } else {
      printf("%lld\n", query(1, 1, n, u, v));
    }
  }
  return 0;
}
