#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define SZ 100005

typedef long long ll;

struct Node {
  ll x, y;
} st[4 * SZ];

ll n, m, a[SZ], b[SZ];

void apply(ll p, ll x, ll y) {
  st[p].x = x; st[p].y = y;
}

void propagate(ll p) {
  if (st[p].x != 0) {
    apply(2 * p, st[p].x, st[p].y);
    apply(2 * p + 1, st[p].x, st[p].y);
  }
  st[p].x = st[p].y = 0;
}

void update(ll p, ll L, ll R, ll u, ll v, ll x, ll y) {
  if (v < L || R < u)
    return;
  if (u <= L && R <= v) {
    return apply(p, x, y);
  }
  propagate(p);
  ll mid = (L + R) >> 1;
  update(2 * p, L, mid, u, v, x, y);
  update(2 * p + 1, mid + 1, R, u, v, x, y);
}

Node query(ll p, ll L, ll R, ll u) {
  if (L == R)
    return st[p];
  propagate(p);
  ll mid = (L + R) >> 1;
  if (u <= mid)
    return query(2 * p, L, mid, u);
  else
    return query(2 * p + 1, mid + 1, R, u);
}

int main() {
  scanf("%I64d %I64d", &n, &m);
  for (ll i = 1; i <= n; i++)
    scanf("%I64d", &a[i]);
  for (ll i = 1; i <= n; i++)
    scanf("%I64d", &b[i]);
  memset(st, 0, sizeof(st));
  ll type, x, y, k;
  for (ll i = 1; i <= m; i++) {
    scanf("%I64d", &type);
    if (type == 1) {
      scanf("%I64d %I64d %I64d", &x, &y, &k);
      update(1, 1, n, y, y + k - 1, x, y);
    } else {
      scanf("%I64d", &y);
      Node t = query(1, 1, n, y);
      printf("%I64d\n", (t.x == 0 ? b[y] : a[t.x + y - t.y]));
    }
  }
  return 0;
}
