#include <stdio.h>
#include <set>

using namespace std;

#define SZ 100005

int n, m, color[SZ], ans_deg, ans_clr;
set<int> V;
set<int> Q[SZ];

int main() {
  scanf("%d %d", &n, &m);

  for (int i = 1; i <= n; i++) {
    scanf("%d", &color[i]);
    V.insert(color[i]);
  }

  for (int i = 0, u, v; i < m; i++) {
    scanf("%d %d", &u, &v);
    if (color[u] != color[v]) {
      Q[color[u]].insert(color[v]);
      Q[color[v]].insert(color[u]);
    }
  }

  ans_clr = -1;
  ans_deg = -1;
  for (set<int>::iterator it = V.begin(); it != V.end(); it++)
    if (ans_deg < (int) Q[*it].size()) {
      ans_deg = (int) Q[*it].size();
      ans_clr = *it;
    }

  printf("%d\n", ans_clr);
  
  return 0;
}
