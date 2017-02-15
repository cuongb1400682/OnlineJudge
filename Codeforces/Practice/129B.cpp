#include <stdio.h>
#include <set>
#include <vector>
#include <queue>

using namespace std;

#define SZ 128

int n, m, deg[SZ];
set<int> G[SZ];

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

int bfs(int u, bool *vis2) {
  queue<int> q;
  bool vis[SZ] = {false};
  vector<int> d1;
  int v;

  q.push(u); vis[u] = true;
  if (deg[u] == 1)
    d1.push_back(u);
  vis2[u] = true;

  while (!q.empty()) {
    u = q.front(); q.pop();

    for (set<int>::iterator it = G[u].begin(); it != G[u].end(); it++) {
      v = *it;
      if (!vis[v]) {
        if (deg[v] == 1)
          d1.push_back(v);
        q.push(v); vis[v] = true;
        vis2[v] = true;
      }
    }
  }

  for (int i = 0; i < (int) d1.size(); i++) {
    u = d1[i];
    v = *G[u].begin();

    G[u].erase(v);
    G[v].erase(u);

    deg[u]--;
    deg[v]--;
  }

  return d1.size();
}


void solve() {
  int time = 0, total;
  do {
    total = 0;
    bool vis[SZ] = {false};
    for (int u = 1; u <= n; u++)
      if (!vis[u])
        total += bfs(u, vis);
    if (total > 0) time++;
  } while (total > 0);
  printf("%d\n", time);
}

int main() {
  init();
  solve();  
  return 0;
}


