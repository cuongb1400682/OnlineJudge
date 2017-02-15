#include <stdio.h>
#include <string.h>
#include <queue>

using namespace std;

#define SZ 512

bool a[SZ][SZ];
int n, m;

void readf() {
  int u, v;
  scanf("%d %d", &n, &m);
  memset(a, false, sizeof(a));
  for (int i = 0; i < m; i++) {
    scanf("%d %d", &u, &v);
    a[u][v] = true;
    a[v][u] = true;
  }
}

int bfs(int s, int t, bool zz) {
  queue<pair<int, int> > q;
  bool vis[SZ] = {false};
  int u, v, w;

  q.push(make_pair(s, 0));
  vis[s] = true;

  while (!q.empty()) {
    u = q.front().first;
    w = q.front().second;
    q.pop();

    if (u == t) {
      return w;
    }

    for (int v = 1; v <= n; v++) {
      if (a[u][v] == zz && !vis[v]) {
        q.push(make_pair(v, w + 1));
        vis[v] = true;
      }
    }
  }

  return -1;
}

int main() {
  readf();
  int d1 = bfs(1, n, false);
  int d2 = bfs(1, n, true);
  if (d1 != -1 && d2 != -1)
    printf("%d\n", max(d1, d2));
  else
    puts("-1");
  return 0;
}
