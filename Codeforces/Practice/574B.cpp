#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

#define SZ 4096

int n, m, a[SZ][SZ], d[SZ], x[3], ans;
bool vis[SZ];
vector<int> G[SZ];

void init() {
  memset(a, false, sizeof(a));
  memset(vis, false, sizeof(vis));
  memset(d, 0, sizeof(d));
  ans = 0x3f3f3f3f;
  
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    G[u].push_back(v);
    G[v].push_back(u);
    a[u][v] = true;
    a[v][u] = true;
    d[u]++;
    d[v]++;
  }
}

int recognition() {
  int u = x[0];
  int v = x[1];
  int w = x[2];  
  
  if (a[u][v] && a[u][w] && a[v][w]) {
    return d[u] + d[v] + d[w] - 2 * (a[u][v] + a[u][w] + a[v][w]);
  } else {
    return 0x3f3f3f3f;
  }
}

void dfs(int idx) {
  if (idx >= 3) {
    int r = recognition();
    if (ans > r)
      ans = r;
    return;
  }

  vector<int>::iterator it;
  int u = x[idx - 1];
  for (it = G[u].begin(); it != G[u].end(); it++) {
    if (!vis[*it]) {
      x[idx] = *it;
      vis[*it] = true;
      dfs(idx + 1);
      vis[*it] = false;
      x[idx] = 0;
    }
  }
}

void solve() {
  for (int u = 1; u <= n; u++) {
    x[0] = u;
    vis[u] = true;
    dfs(1);
    x[0] = 0;
    vis[u] = false;
  }
  if (ans == 0x3f3f3f3f)
    puts("-1");
  else
    printf("%d\n", ans);
}

int main() {
  init();
  solve();
  return 0;
}
