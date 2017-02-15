#include <stdio.h>
#include <stdlib.h>
#include <set>

using namespace std;

#define SZ 512

set<int> G[SZ];
int n, m, deg[SZ];
char s[SZ];

void init() {
  int u, v;
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; i++) {
    scanf("%d %d", &u, &v);
    G[u].insert(v);
    G[v].insert(u);
    deg[u]++;
    deg[v]++;
  }
}

void solve() {
  for (int u = 1; u <= n; u++)
    if (deg[u] == n - 1)
      s[u] = 'b';
  
  bool first_time = true;
  for (int u = 1; u <= n; u++)
    if (s[u] == 0) {
      if (first_time)  {
        s[u] = 'a';
        for (set<int>::iterator it = G[u].begin(); it != G[u].end(); it++) {
          int v = *it;
          if (s[v] == 0)
            s[v] = 'a';
        }
        first_time = false;
      } else {
        s[u] = 'c';
      }
    }

  for (int i = 1; i <= n - 1; i++)
    for (int j = i + 1; j <= n; j++) {
      int d = abs(s[i] - s[j]);
      int c = G[i].count(j);
      if ((d <= 1 && c == 0) || (d > 1 && c != 0)) {
        puts("No");
        return;
      }
    }
  
  puts("Yes");
  puts(s + 1);
}

int main() {
  init();
  solve();
  return 0;
}
