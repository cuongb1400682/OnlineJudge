#include <stdio.h>
#include <utility>
#include <set>
#include <vector>

using namespace std;

#define X first
#define Y second
#define SZ 100005

typedef pair<int, int> seg_t;

seg_t a[SZ];
int point[SZ], st[4 * SZ], n, m;
vector<int> uniq_pt;

void init(int p, int L, int R) {
  st[p] = -1;
  if (L == R)
    return;
  int mid = (L + R) >> 1;
  init(2 * p, L, mid);
  init(2 * p + 1, mid + 1, R);
}

bool is_better(const seg_t& a, const seg_t& b) {
  return (a.Y - a.X < b.Y - b.X);
}

void apply(int p, int index) {
  if (st[p] == -1 || is_better(a[index], a[st[p]]))
    st[p] = index;  
}

void propagate(int p, int L, int R) {
  if (st[p] != -1) {
    apply(2 * p, st[p]);
    apply(2 * p + 1, st[p]);
  }
  st[p] = -1;
}

void update(int p, int L, int R, int u, int v, int index) {
  if (v < uniq_pt[L] || uniq_pt[R] < u)
    return;
  if (u <= uniq_pt[L] && uniq_pt[R] <= v) {
    apply(p, index);
    return;
  }
  propagate(p, L, R);
  int mid = (L + R) >> 1;
  update(2 * p, L, mid, u, v, index);
  update(2 * p + 1, mid + 1, R, u, v, index);
}

int query(int p, int L, int R, int u) {
  if (L == R)
    return st[p];
  propagate(p, L, R);
  int mid = (L + R) >> 1;
  if (u <= uniq_pt[mid])
    return query(2 * p, L, mid, u);
  else
    return query(2 * p + 1, mid + 1, R, u);
}

int main() {
  scanf("%d", &m);
  for (int i = 1; i <= m; i++)
    scanf("%d %d", &a[i].X, &a[i].Y);
  
  scanf("%d", &n);
  set<int> h;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &point[i]);
    h.insert(point[i]);
  }

  uniq_pt.clear();
  for (set<int>::iterator it = h.begin(); it != h.end(); it++)
    uniq_pt.push_back(*it);

  init(1, 0, uniq_pt.size() - 1);
  
  for (int i = 1; i <= m; i++) {
    update(1, 0, uniq_pt.size() - 1, a[i].X, a[i].Y, i);
  }

  for (int i = 1; i <= n; i++) {
    int idx = query(1, 0, uniq_pt.size() - 1, point[i]);
    printf("%d\n", idx);
  }
  return 0;
}
