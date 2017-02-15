#include <stdio.h>
#include <queue>
#include <string.h>

using namespace std;

int bfs(int s, int t) {
  queue<pair<int, int> > q;
  bool vis[10005];
  int u, v, l;

  q.push(make_pair(s, 0));
  memset(vis, false, sizeof(vis));

  vis[s] = true;
  
  while (!q.empty()) {
    u = q.front().first;
    l = q.front().second;
    q.pop();

    if (u == t)
      return l;

    for (int i = 0; i <= 1; i++) {
      if (i == 0)
        v = u - 1;
      else
        v = 2 * u;
      if (v >= 0 && !vis[v] && v <= 10000) {
        q.push(make_pair(v, l + 1));
        vis[v] = true;
      }
    }
  }

  return 0;  
}

int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  if (n == m)
    printf("0");
  else if (n > m)
    printf("%d", n - m);
  else
    printf("%d", bfs(n, m));
  printf("\n");
  return 0;
}
