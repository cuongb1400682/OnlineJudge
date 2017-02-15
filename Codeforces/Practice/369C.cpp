#include <stdio.h>
#include <set>
#include <string.h>
#include <vector>

using namespace std;

#define SZ 100005

typedef pair<int, int> ii;

int n, deg[SZ];
set<ii> G[SZ];

void init() {
  int u, v, w;
  scanf("%d", &n);
  for (int i = 1; i <= n - 1; i++) {
    scanf("%d %d %d", &u, &v, &w);
    G[u].insert(ii(v, w == 2));
    G[v].insert(ii(u, w == 2));
    deg[u]++;
    deg[v]++;
  }
}

void find_leaf(int u, int *parent) {
  int v, problem;
  for (set<ii>::iterator it = G[u].begin(); it != G[u].end(); it++) {
    v = it->first;
    problem = it->second;
    if (parent[v] == 0) {
      parent[v] = u;
      find_leaf(v, parent);
    }
    if (deg[v] == 1 && !problem) {
      deg[v]--;
      deg[u]--;
      G[u].erase(ii(v, 1));
      G[v].erase(ii(u, 1));
    }
  }
}

void solve() {
  int parent[SZ] = { 0 };
  set<int> ans;
  find_leaf(1, parent);
  memset(parent, 0, sizeof(parent));

  for (int u = 1; u <= n; u++) {
    if (deg[u] == 1 && u != 1)
      ans.insert(u);
  }

  printf("%d\n", (int) ans.size());
  for (set<int>::iterator it = ans.begin(); it!= ans.end(); it++)
    printf("%d ", *it);
  printf("\n");
}

int main() {
  init();
  solve();
  return 0;
}
