#include <stdio.h>
#include <vector>
#include <string.h>

using namespace std;

#define SZ 2048

vector<int> G[SZ];
int n, parent[SZ];

int dfs(int u, int p) {
  int height = 1;
  for (int i = 0; i < (int) G[u].size(); i++) {
    int v = G[u][i];
    if (p != v) 
      height = max(height, dfs(v, u) + 1);
  }
  return height;
}

int main() {
  scanf("%d", &n);

  memset(parent, -1, sizeof(parent));
  
  for (int i = 1; i <= n; i++) {
    int v;
    scanf("%d", &v);
    if (v != -1) {
      G[v].push_back(i);
      parent[i] = v;
    }
  }

  int max_h = 1;
  for (int u = 1; u <= n; u++)
    if (parent[u] == -1)
      max_h = max(max_h, dfs(u, -1));

  printf("%d\n", max_h);
  
  return 0;
}
