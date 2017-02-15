#include <string.h>
#include <stdio.h>
#include <set>
#include <vector>

using namespace std;

#define INF 1000000000

#define SZ 1024

int n, m, dp[SZ];
bool is_prior[SZ][SZ];
set<int> G[SZ];

void init() {
  int pos[SZ], val;
  
  scanf("%d %d", &n, &m);

  memset(is_prior, true, sizeof(is_prior));
  
  for (int i = 1; i <= m; i++) {
    memset(pos, 0, sizeof(pos));
    for (int j = 1; j <= n; j++)
      scanf("%d", &val), pos[val] = j;
    
    for (int u = 1; u <= n; u++)
      for (int v = 1; v <= n; v++)
        is_prior[u][v] = is_prior[u][v] && (pos[u] < pos[v]);
  }

  for (int u = 1; u <= n; u++)
    for (int v = 1; v <= n; v++)
      if (is_prior[u][v]) {
        G[u].insert(v);
      }
}

void topo_sort(int u, vector<int> &vec, bool *vis) {
  if (vis[u])
    return;
  vis[u] = true;
  for (set<int>::iterator it = G[u].begin(); it != G[u].end(); it++)
    topo_sort(*it, vec, vis);
  vec.push_back(u);
}

void solve() {
  vector<int> vec;
  bool vis[SZ] = {false};

  for (int u = 1; u <= n; u++)
    if (!vis[u])
      topo_sort(u, vec, vis);

  for (int i = 0; i < (int) vec.size(); i++) {
    int u = vec[i];
    dp[u] = 1;
    for (set<int>::iterator it = G[u].begin(); it != G[u].end(); it++)
      dp[u] = max(dp[u], dp[*it] + 1);
  }

  int ans = 0;
  for (int u = 1; u <= n; u++)
    ans = max(ans, dp[u]);

  printf("%d\n", ans);
}

int main() {
  init();
  solve();
  return 0;
}
