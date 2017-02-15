#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

#define SZ 1024

int n, m, money[SZ];
bool visited[SZ];
vector<int> G[SZ];

void dfs(int u, int &n_vertices, int &total_money) {
  if (visited[u])
    return;
  visited[u] = true;
  n_vertices++;
  total_money += money[u];
  for (int i = 0; i < (int) G[u].size(); i++)
    dfs(G[u][i], n_vertices, total_money);
}

int main() {
  int T, no = 1;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &n, &m);
    int avg_money = 0;
    for (int i = 1; i <= n; i++) {
      G[i].clear();
      scanf("%d\n", &money[i]);
      avg_money += money[i];
    }
    for (int i = 1; i <= m; i++) {
      int u, v;
      scanf("%d %d", &u, &v);
      G[u].push_back(v);
      G[v].push_back(u);
    }
    memset(visited, false, sizeof(visited));
    bool ans = (avg_money % n == 0);
    if (ans == true) {
      avg_money /= n;
      for (int u = 1; u <= n; u++)
	if (!visited[u]) {
	  int n_vertices = 0;
	  int total_money = 0;
	  dfs(u, n_vertices, total_money);
	  if (total_money % n_vertices != 0 ||
	      total_money / n_vertices != avg_money) {
	    ans = false;
	    break;
	  }
	}
    }
    printf("Case %d: %s\n", no++, ans ? "Yes" : "No");
  }  
  return 0;
}
