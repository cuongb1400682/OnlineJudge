#include <stdio.h>
#include <string.h>
#include <queue>

using namespace std;

#define SZ 64

const int dx[] = { 0, 1, 0, -1 };
const int dy[] = { 1, 0, -1, 0 };

int n, m, ans;
char grid[SZ][SZ], t[SZ][SZ];

int traverse(int x, int y) {
  queue<pair<int, int> > q;
  int u, v, l;
  memcpy(t, grid, sizeof grid);
  q.push(make_pair(x * 100 + y, 1));
  t[x][y] = '#';
  while (not q.empty()) {
    x = q.front().first / 100;
    y = q.front().first % 100;
    l = q.front().second;
    q.pop();
    for (int i = 0; i < 4; i++) {
      u = x + dx[i], v = y + dy[i];
      if (u >= 0 && v >= 0 && u < n && v < m)
	if (t[u][v] != '#' && t[u][v] != 'm') {
	  q.push(make_pair(u * 100 + v, l + 1));
	  if (t[u][v] == 'h')
	    return l;
	  t[u][v] = '#';
	}
    }
  }
  return 0;
}

int main() {
  int n_test;
  scanf("%d", &n_test);
  int no = 1;
  while (n_test--) {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
      scanf("%s", grid[i]);
    ans = -1;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
	if (grid[i][j] >= 'a' && grid[i][j] <= 'c')
	  ans = max(ans, traverse(i, j));	
    printf("Case %d: %d\n", no++, ans);
  }
  return 0;
}
