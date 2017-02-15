#include <stdio.h>
#include <string.h>

#define SZ 1024

int deg[SZ], n, m;
bool a[SZ][SZ];

int main() {
  scanf("%d %d", &n, &m);
  memset(a, true, sizeof(a));

  for (int i = 1; i <= n; i++) {
    a[i][i] = false;
    deg[i] = n - 1;
  }

  for (int i = 1; i <= m; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    a[u][v] = false;
    a[v][u] = false;
    deg[u]--;
    deg[v]--;
  }

  int root = -1;
  int max_deg = -1;
  
  for (int i = 1; i <= n; i++)
    if (max_deg < deg[i]) {
      max_deg = deg[i];
      root = i;
    }

  printf("%d\n", n - 1);
  for (int u = 1; u <= n; u++)
    if (u != root)
      printf("%d %d\n", root, u);
  
  return 0;
}
