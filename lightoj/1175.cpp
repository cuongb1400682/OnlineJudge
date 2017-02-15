#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>

using namespace std;

#define SZ 256

struct Cell {
  int x, y;
  Cell(int x = 0, int y = 0) : x(x), y(y) {
  }
};

const int dx[] = { 0, -1, 0, 1 };
const int dy[] = { -1, 0, 1, 0 };

Cell Jane;
int F[SZ][SZ], J[SZ][SZ], m, n;
char grid[SZ][SZ];

bool valid(Cell y) {
  return y.x >= 0 && y.y >= 0 && y.x < m && y.y < n;
}

int bfs(int (*a)[SZ], Cell x, char fin_char = '\0') {
  queue<pair<Cell, int> > q;
  bool vis[SZ][SZ];
  int l;
  Cell y;

  memset(vis, false, sizeof(vis));
  q.push(make_pair(x, 1));
  vis[x.x][x.y] = true;

  while (!q.empty()) {
    x = q.front().first;
    l = q.front().second;
    q.pop();
    if (a[x.x][x.y] > l)
      a[x.x][x.y] = l;
    if (grid[x.x][x.y] == fin_char)
      return l;
    for (int i = 0; i < 4; i++) {
      y = Cell(x.x + dx[i], x.y + dy[i]);
      if (vis[y.x][y.y])
        continue;
      if (valid(y) && grid[y.x][y.y] != '#') {
        vis[y.x][y.y] = true;
        q.push(make_pair(y, l + 1));
      }
    }
  }

  return -1;
}

int main() {
  int T, no = 1;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &m, &n);

    for (int i = 0; i < m; i++) {
      scanf(" %s ", grid[i]);
      for (int j = 0; j < n; j++) {
        if (grid[i][j] == 'J')
          Jane = Cell(i, j);
      }
    }
    
    memset(J, 0x3f, sizeof(J));
    memset(F, 0x3f, sizeof(F));
    
    bfs(J, Jane);

    int ans = 0x3f3f3f3f, tmp;
    for (int x = 0; x < m; x++) {
      tmp = bfs(F, Cell(x, 0), 'F');
      if (J[x][0] < tmp)
        ans = min(ans, J[x][0]);
      
      tmp = bfs(F, Cell(x, n - 1), 'F');
      if (J[x][n - 1] < tmp)
        ans = min(ans, J[x][n - 1]);
    }
    for (int y = 0; y < n; y++) {
      tmp = bfs(F, Cell(0, y), 'F');
      if (J[0][y] < tmp)
        ans = min(ans, J[0][y]);
      
      tmp = bfs(F, Cell(m - 1, y), 'F');
      if (J[m - 1][y] < tmp)
        ans = min(ans, J[m - 1][y]);
    }
    printf("Case %d: ", no++);
    if (ans == 0x3f3f3f3f)
      puts("IMPOSSIBLE");
    else
      printf("%d\n", ans);
  }
  return 0;
}
