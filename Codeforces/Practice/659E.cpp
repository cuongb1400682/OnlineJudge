#include <stdio.h>
#include <set>

using namespace std;

#define SZ 100005

int n, m, parent[SZ];
set<int> G[SZ];

void init() {
  int u, v;
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; i++) {
    scanf("%d %d", &u, &v);
    G[u].insert(v);
    G[v].insert(u);
  }
}

bool has_circle(int u, int *parent) {  
  for (set<int>::iterator it = G[u].begin(); it != G[u].end(); it++) {
    if (parent[*it] == 0) {
      parent[*it] = u;
      if (has_circle(*it, parent))
        return true;
    } else if (parent[u] != *it) {
      return true;
    }      
  }
  return false;
}

int main() {
  init();
  int ans = 0;
  for (int u = 1; u <= n; u++) {
    if (parent[u] == 0) {
      parent[u] = u;
      if (!has_circle(u, parent))
        ans++;
    }
  }
  printf("%d\n", ans);
  return 0;
}
