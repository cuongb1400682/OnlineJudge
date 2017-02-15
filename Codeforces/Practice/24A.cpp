#include <stdio.h>
#include <set>

using namespace std;

typedef pair<int, int> ii;

#define SZ 128

int neg, pos, n, z;
set<ii> G[SZ];
bool vis[SZ];

void dfs(int u) {
  z = u;
  for (set<ii>::iterator it = G[u].begin(); it != G[u].end(); it++) {
    int v = it->first;
    int w = it->second;
    if (!vis[v]) {
      vis[v] = true;
      if (w < 0)
        neg += w;
      else
        pos += w;
      dfs(v);
      break;
    }
  }
}

int main() {
  int u, v, w;
  
  scanf("%d", &n);
  bool first = true;
  for (int i = 1; i <= n; i++) {
    scanf("%d %d %d", &u, &v, &w);
    G[u].insert(ii(v, w));
    G[v].insert(ii(u, -w));
  }

  neg = 0;
  pos = 0;
  vis[1] = true;
  dfs(1);

  for (set<ii>::iterator it = G[z].begin(); it != G[z].end(); it++) {
    if (it->first == 1) {
      if (it->second < 0)
        neg += it->second;
      else
        pos += it->second;
      break;
    }
  }

  neg *= -1;
  printf("%d\n", min(neg, pos));
  
  return 0;
}
