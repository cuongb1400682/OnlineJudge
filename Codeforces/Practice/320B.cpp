#include <stdio.h>
#include <map>
#include <set>
#include <vector>

using namespace std;

#define SZ 128

typedef pair<int, int> ii;

vector<ii> intervals;
set<int> G[SZ];
int n, q;

bool is_intersected(int a, int b, int c, int d) {
  return (c < a && a < d) || (c < b && b < d);
}

void add_interval(int x, int y) {
  ii I1(x, y), I2;
  intervals.push_back(I1);
  n++;
  for (int i = 1; i <= n - 1; i++) {
    I2 = intervals[i - 1];
    if (is_intersected(I1.first, I1.second, I2.first, I2.second)) {
      G[n].insert(i);
    }
    if (is_intersected(I2.first, I2.second, I1.first, I1.second)) {
      G[i].insert(n);
    }
  }
}

bool dfs(int s, int t, bool *vis) {
  if (s == t)
    return true;
  for (set<int>::iterator it = G[s].begin(); it != G[s].end(); it++) {
    if (!vis[*it]) {
      vis[*it] = true;
      if (dfs(*it, t, vis))
        return true;
    }
  }
  return false;
}

int main() {
  scanf("%d", &q);
  int t, x, y;
  n = 0;
  while (q--) {
    scanf("%d %d %d", &t, &x, &y);    
    if (t == 1) {
      add_interval(x, y);
    } else {
      bool vis[SZ] = { false };
      puts(dfs(x, y, vis) ? "YES" : "NO");
    }
  }
  return 0;
}
