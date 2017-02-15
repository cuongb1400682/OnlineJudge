#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <ctype.h>

using namespace std;

#define SZ 200005
#define INF 0x3f3f3f3f3f3f3f3fLL

typedef long long ll;

struct Node {
  ll lazy, min;
} st[4 * SZ];

ll n, m;

void insert(ll p, ll L, ll R, ll u, ll value) {
  if (L == R) {
    st[p].min = value;
    return;
  }
  ll mid = (L + R) / 2;
  if (u <= mid)
    insert(2 * p, L, mid, u, value);
  else
    insert(2 * p + 1, mid + 1, R, u, value);
  st[p].min = min(st[2 * p].min, st[2 * p + 1].min);
}

void apply(ll p, ll value) {
  st[p].lazy += value;
  st[p].min += value;
}

void propagate(ll p) {
  if (st[p].lazy != 0) {
    apply(2 * p, st[p].lazy);
    apply(2 * p + 1, st[p].lazy);
  }
  st[p].lazy = 0;
}

ll query(ll p, ll L, ll R, ll u, ll v) {
  if (v < L || R < u)
    return INF;
  if (u <= L && R <= v)
    return st[p].min;
  propagate(p);
  ll mid = (L + R) / 2;
  return min(query(2 * p, L, mid, u, v),
	     query(2 * p + 1, mid + 1, R, u, v));
}

void increase(ll p, ll L, ll R, ll u, ll v, ll value) {
  if (v < L || R < u)
    return;
  if (u <= L && R <= v)
    return (void) apply(p, value);
  propagate(p);
  ll mid = (L + R) / 2;
  increase(2 * p, L, mid, u, v, value);
  increase(2 * p + 1, mid + 1, R, u, v, value);
  st[p].min = min(st[2 * p].min, st[2 * p + 1].min);
}


ll parse(ll &lf, ll &rg, ll &v) {
  char buf[1024], *p;
  const char *delim = " \t\n\r\b";
  ll c, i;
  while (isspace(c = getchar()))
    ;
  ungetc(c, stdin);
  fgets(buf, sizeof(buf), stdin);
  lf = rg = v = 0;
  i = 0;
  for (p = strtok(buf, delim); p; p = strtok(NULL, delim)) {
    if (i == 0)
      sscanf(p, "%I64d", &lf);
    else if (i == 1)
      sscanf(p, "%I64d", &rg);
    else
      sscanf(p, "%I64d", &v);
    i++;
  }
  return i;
}

int main() {
  scanf("%I64d", &n);
  memset(st, 0, sizeof(st));
  for (ll i = 0; i < n; i++) {
    ll number;
    scanf("%I64d", &number);
    insert(1, 0, n - 1, i, number);
  }
  scanf("%I64d ", &m);
  for (ll i = 1; i <= m; i++) {
    ll lf, rg, v;
    ll n_parse = parse(lf, rg, v);
    if (n_parse == 2) {
      ll ans = INF;
      if (lf > rg) {
	ans = min(ans, query(1, 0, n - 1, 0, rg));
	ans = min(ans, query(1, 0, n - 1, lf, n - 1));
      } else {
	ans = min(ans, query(1, 0, n - 1, lf, rg));
      }
      printf("%I64d\n", ans);
    } else /*3*/ {
      if (lf > rg) {
	increase(1, 0, n - 1, 0, rg, v);
	increase(1, 0, n - 1, lf, n - 1, v);
      } else {
	increase(1, 0, n - 1, lf, rg, v);
      }
    }
  }
  return 0;
}
