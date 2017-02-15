#include <stdio.h>
#include <string>

using std::string;

#define SZ 100005

typedef long long ll;

struct Node {
  bool is_inverse;
  ll bit_1;
  Node() {
    bit_1 = 0;
    is_inverse = false;
  }
};

Node st[22][4 * SZ];
ll a[SZ], n, m;

void init(ll b, ll p, ll L, ll R) {
  st[b][p] = Node();
  if (L == R) {
    st[b][p].bit_1 = bool(a[L] & (1 << (b - 1)));
    return;
  }
  ll mid = (L + R) >> 1;
  init(b, 2 * p, L, mid);
  init(b, 2 * p + 1, mid + 1, R);
  st[b][p].bit_1 = st[b][2 * p].bit_1 + st[b][2 * p].bit_1;
}

void apply(Node *st, ll p, ll L, ll R) {
  st[p].is_inverse = not st[p].is_inverse;
  st[p].bit_1 = (R - L + 1) - st[p].bit_1;
}

void propagate(Node *st, ll p, ll L, ll R) {
  if (st[p].is_inverse) {
    ll mid = (L + R) >> 1;
    apply(st, 2 * p, L, mid);
    apply(st, 2 * p + 1, mid + 1, R);
  }
  st[p].is_inverse = false;
}

void invert(Node *st, ll p, ll L, ll R, ll u, ll v) {
  if (v < L || R < u)
    return;
  if (u <= L && R <= v) {
    apply(st, p, L, R);
    return;
  }
  propagate(st, p, L, R);
  ll mid = (L + R) >> 1;
  invert(st, 2 * p, L, mid, u, v);
  invert(st, 2 * p + 1, mid + 1, R, u, v);
  st[p].bit_1 = st[2 * p].bit_1 + st[2 * p + 1].bit_1;
}

ll get_sum(Node *st, ll p, ll L, ll R, ll u, ll v) {
  if (v < L || R < u)
    return 0;
  if (u <= L && R <= v)
    return st[p].bit_1;
  propagate(st, p, L, R);
  ll mid = (L + R) >> 1;
  return get_sum(st, 2 * p, L, mid, u, v) +
	  get_sum(st, 2 * p + 1, mid + 1, R, u, v);
}

ll get_bit(ll a, ll bit) {
  return bool(a & (1 << (bit - 1)));
}

int main() {
  scanf("%I64d", &n);
  for (ll i = 1; i <= n; i++) {
    scanf("%I64d", &a[i]);
  }

  for (ll i = 1; i <= 20; i++) {
    for (ll j = 1; j <= n; j++) {
      if (get_bit(a[j], i))
	invert(st[i], 1, 1, n, j, j);
    }
  }
    
  scanf("%I64d", &m);
  
  for (ll i = 1; i <= m; i++) {
    ll type, l, r, x;
    scanf("%I64d %I64d %I64d", &type, &l, &r);
    if (type == 2) {
      scanf("%I64d", &x);
      for (ll h = 1; h <= 20; h++) {
	ll j = h - 1;
	if (x & (1 << j)) invert(st[h], 1, 1, n, l, r);
      }
    } else {
      ll sum = 0;
      for (ll h = 1; h <= 20; h++) {
	ll tmp = get_sum(st[h], 1, 1, n, l, r) * (1 << (h - 1));
	sum += tmp;
      }
      printf("%I64d\n", sum);
    }
  }
  return 0;
}
