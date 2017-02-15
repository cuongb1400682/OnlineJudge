#include <stdio.h>
#include <map>
#include <set>

using namespace std;

#define SZ 128

map<int, set<int> > G;
int n, m;

void init() {
  int u, v;
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; i++) {
    scanf("%d %d", &u, &v);
    G[u].insert(v);
    G[v].insert(u);
  }
}

int dfs(int u, bool *vis) {
  if (vis[u])
    return 0;
  vis[u] = true;
  int ans = 1;
  for (set<int>::iterator it = G[u].begin(); it != G[u].end(); it++)
    ans += dfs(*it, vis);
  return ans;
}

void solve() {
  bool vis[SZ] = { false };
  if (m != n)
    puts("NO");
  else
    puts(dfs(1, vis) == n ? "FHTAGN!" : "NO");
}

int main() {
  init();
  solve();
  return 0;
}
