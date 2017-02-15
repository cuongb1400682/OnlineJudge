#include <stdio.h>
#include <string.h>
#include <queue>

using namespace std;

#define WHITE 0
#define BLACK -1
#define UNCOLORED 1

char color[20005];
int n;
vector<int> G[20005];

int bfs(int x) {
  int ans = 0, n_white = 0, n_black = 0, y;
  queue<int> q;
  
  color[x] = WHITE;
  q.push(x);

  while (!q.empty()) {
    x = q.front(); q.pop();
    n_white += (color[x] == WHITE);
    n_black += (color[x] == BLACK);
    for (int i = 0; i < (int) G[x].size(); i++) {
      y = G[x][i];
      if (color[y] == UNCOLORED) {
	color[y] = (color[x] == WHITE ? BLACK : WHITE);
	q.push(y);
      }
    }
  }
  return max(n_white, n_black);
}

int main() {
  int T, no = 1;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 0; i < 20005; i++)
      G[i].clear();
    for (int i = 0; i < n; i++) {
      int u, v;
      scanf("%d %d", &u, &v);
      G[u].push_back(v);
      G[v].push_back(u);
    }
    int ans = 0;
    memset(color, UNCOLORED, sizeof(color));
    for (int u = 1; u <= 20000; u++)
      if (G[u].size() > 0 && color[u] == UNCOLORED)
	ans += bfs(u);
    printf("Case %d: %d\n", no++, ans);
  }
  return 0;
}
