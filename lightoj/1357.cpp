#include <stdio.h>
#include <vector>

using namespace std;

#define SZ 100005

vector<int> G[SZ];
int n, n_visited;
long long ans;

void dfs(int u, int p) {
  n_visited++;
  for (int i = 0; i < G[u].size(); i++)
    if (G[u][i] != p)
      dfs(G[u][i], u);
  ans += (long long) (n - n_visited);
}

int main() {
  int T, no = 1;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
      G[i].clear();
    for (int i = 1; i <= n - 1; i++) {
      int u, v;
      scanf("%d %d", &u, &v);
      G[u].push_back(v);
      G[v].push_back(u);
    }
    n_visited = 0;
    ans = 0;
    dfs(1, 1);
    printf("Case %d: %d %lld\n", no++, n - 1, ans);
  }
  return 0;
}
