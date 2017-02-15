#include <stdio.h>
#include <set>
#include <map>
#include <vector>
#include <string.h>

using namespace std;

#define SZ 100005

int n, m, color[SZ];
map<int, set<int> > G;

void readf() {
  int u, v;
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; i++) {
    scanf("%d %d", &u, &v);
    G[u].insert(v);
    G[v].insert(u);
  }
  memset(color, -1, sizeof(color));
}

bool dfs(int u, int &cnt) {
  cnt++;
  for (set<int>::iterator it = G[u].begin(); it != G[u].end(); it++) {
    int v = *it;
    if (color[v] == -1) {
      color[v] = 1 - color[u];
      if (dfs(v, cnt) == false)
        return false;
    } else if (color[v] == color[u]) {
      return false;
    }
  }
  return true;
}

void print() {
  for (int u = 1; u <= n; u++) {
    int cnt = 0;
    if (color[u] == -1) {
      color[u] = 0;
      if (dfs(u, cnt) == false) {
        printf("-1\n");
        return;
      }
    }
    if (cnt == 1)
      color[u] = 2;
  }

  vector<int> ans[3];
  for (int u = 1; u <= n; u++)
    ans[color[u]].push_back(u);

  printf("%d\n", (int) ans[0].size());
  for (int i = 0; i < (int) ans[0].size(); i++)
    printf("%d ", ans[0][i]);
  printf("\n");

  printf("%d\n", (int) ans[1].size());
  for (int i = 0; i < (int) ans[1].size(); i++)
    printf("%d ", ans[1][i]);
  printf("\n");
}

int main() {
  readf();
  print();
  return 0;
}
