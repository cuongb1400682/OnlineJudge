#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>

using namespace std;

#define SZ 16

const int dx[] = { 1, 1, 2, 2, -1, -1, -2, -2, };
const int dy[] = { 2, -2, 1, -1, 2, -2, 1, -1, };

int m, n, n_rider, rider[SZ][SZ], cnt[SZ][SZ];
char grid[SZ][SZ];

bool valid(int x, int y) {
  return x >= 0 && x < m && y >= 0 && y < n;
}

void bfs(int x, int y) {
  bool visited[SZ][SZ];
  queue<pair<pair<int, int>, int> > q;
  int u, v, l, step;

  step = grid[x][y] - '0';
  memset(visited, false, sizeof(visited));

  q.push(make_pair(make_pair(x, y), 0));
  visited[x][y] = true;

  while (!q.empty()) {
    x = q.front().first.first;
    y = q.front().first.second;
    l = q.front().second;
    q.pop();

    cnt[x][y]++;
    rider[x][y] += l / step + (l % step > 0);
    
    for (int i = 0; i < 8; i++) {
      u = x + dx[i]; v = y + dy[i];
      if (valid(u, v) && !visited[u][v]) {
	q.push(make_pair(make_pair(u, v), l + 1));
	visited[u][v] = true;
      }
    }
  }
}

int main() {
  int T, no = 1;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &m, &n);
    for (int i = 0; i < m; i++)
      scanf(" %s ", grid[i]);
    
    memset(rider, 0, sizeof(rider));
    memset(cnt, 0, sizeof(cnt));

    n_rider = 0;
    for (int i = 0; i < m; i++)
      for (int j = 0; j < n; j++)
	if (grid[i][j] != '.')
	  bfs(i, j), ++n_rider;

    int ans = -1;
    for (int i = 0; i < m; i++)
      for (int j = 0; j < n; j++)
	if (cnt[i][j] == n_rider)
	  if (ans > rider[i][j] || ans == -1)
	  ans = rider[i][j];
    printf("Case %d: %d\n", no++, ans);
  }
  return 0;
}
