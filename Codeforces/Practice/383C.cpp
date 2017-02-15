#include <stdio.h>
#include <vector>
#include <map>

using namespace std;

#define SZ 200005

int n, m, left_odd[SZ], right_odd[SZ], a[SZ];
int left_even[SZ], right_even[SZ], de_odd[SZ], de_even[SZ];
int st_odd[4 * SZ], st_even[4 * SZ];
bool is_odd[SZ];
map<int, vector<int> > g;

void dfs(int u, int p, int h, int& odd_cnt, int& even_cnt) {
  is_odd[u] = bool(h & 1);
  if (is_odd[u]) {
    left_odd[u] = ++odd_cnt;
    left_even[u] = even_cnt + 1;
    de_odd[left_odd[u]] = u;
  } else {
    left_even[u] = ++even_cnt;
    left_odd[u] = odd_cnt + 1;
    de_even[left_even[u]] = u;
  }
  vector<int>& z = g[u];
  for (int i = 0; i < (int) z.size(); i++)
    if (p != z[i])
      dfs(z[i], u, h + 1, odd_cnt, even_cnt);
  right_odd[u] = odd_cnt;
  right_even[u] = even_cnt;
}

void propagate(int *st, int p) {
  st[2 * p] += st[p];
  st[2 * p + 1] += st[p];
  st[p] = 0;
}

void increase(int *st, int p, int L, int R, int u, int v, int val) {
  if (v < L || R < u)
    return;
  if (u <= L && R <= v) {
    st[p] += val;
    return;
  }
  propagate(st, p);
  int mid = (L + R) >> 1;
  increase(st, 2 * p, L, mid, u, v, val);
  increase(st, 2 * p + 1, mid + 1, R, u, v, val);
}

int get_sum(int *st, int p, int L, int R, int x) {
  if (L == R)
    return st[p];
  propagate(st, p);
  int mid = (L + R) >> 1;
  if (x <= mid)
    return get_sum(st, 2 * p, L, mid, x);
  else
    return get_sum(st, 2 * p + 1, mid + 1, R, x);
}

int main() {
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  for (int i = 1; i <= n - 1; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }

  int odd_cnt = 0, even_cnt = 0;
  dfs(1, 0, 1, odd_cnt, even_cnt);

  int type, x, val;
  for (int i = 1; i <= m; i++) {
    scanf("%d", &type);
    scanf("%d", &x);
    if (type == 1) {
      scanf("%d", &val);
      if (is_odd[x]) {
	increase(st_odd, 1, 1, n, left_odd[x], right_odd[x], val);
	increase(st_even, 1, 1, n, left_even[x], right_even[x], -val);
      } else {
	increase(st_odd, 1, 1, n, left_odd[x], right_odd[x], -val);
	increase(st_even, 1, 1, n, left_even[x], right_even[x], val);
      }
    } else {
      int ans = 0;
      if (is_odd[x]) {
	ans = get_sum(st_odd, 1, 1, n, left_odd[x]) + a[x];
      } else {
	ans = get_sum(st_even, 1, 1, n, left_even[x]) + a[x];
      }
      printf("%d\n", ans);
    }
  }
  
  return 0;
}
