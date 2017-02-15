#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
#include <string>
#include <map>

using namespace std;

#define SZ 256
#define PI 3.141592653589793238462643
#define S_BIG (PI / 4.0)
#define S_SMALL (1.0 - S_BIG)

struct Point {
  int x, y;
  Point(int x = 0, int y = 0): x(x), y(y) { }
};

int grid[2 * SZ][2 * SZ];
int m, n;
long double hyper_grid[2 * SZ][2 * SZ];

void readf() {
  static char line[10024];
  memset(grid, 0, sizeof grid);
  scanf("%d %d", &m, &n);
  for (int i = 0; i < m; i++) {
    scanf(" %s ", line);
    for (int j = 0; j < n; j++) {
      if (line[j] == '0') {
        grid[2 * i][2 * j] = 3;
        grid[2 * i][2 * j + 1] = 0;
        grid[2 * i + 1][2 * j + 1] = 1;
        grid[2 * i + 1][2 * j] = 0;
      } else {
        grid[2 * i][2 * j] = 0;
        grid[2 * i][2 * j + 1] = 4;
        grid[2 * i + 1][2 * j + 1] = 0;
        grid[2 * i + 1][2 * j] = 2;
      }
    }
  }
}

inline bool is_valid(int x, int y) {
  return (x >= 0) && (y >= 0) && (x < 2 * m) && (y < 2 * n);
}

pair<Point, bool> get_first_point(int x, int y) {
  static const int dx[] = { -1, -1, 0, 0 };
  static const int dy[] = { -1, 0, 0, -1 };
  static const int is_big[][5] = {
    //0  1  2  3  4
    { 1, 1,-1, 0,-1 },
    { 1,-1, 1,-1, 0 },
    { 1, 0,-1, 1,-1 },
    { 1,-1, 0,-1, 1 }
  };
  pair<Point, bool> ans(Point(-1, -1), false);
  for (int i = 0; i < 4; i++) {
    int u = x + dx[i], v = y + dy[i];
    if (is_valid(u, v)) {
      ans = make_pair(Point(u, v), is_big[i][grid[u][v]]);
      if (is_big[i][grid[u][v]] < 0)
        return make_pair(Point(-1, -1), false);
    }
  }
  return ans;
}

long double bfs(int x, int y, bool xy_big) {
  queue<pair<Point, bool> > q;
  vector<pair<Point, bool> > _v;
  bool in_queue[SZ][SZ];
  long double ans = 0.0;
  int u, v;

  static const int dx[] = { -1, 0, 1, 0 };
  static const int dy[] = { 0, 1, 0, -1 };
  
  static const bool zero_big[][5] = {
    //0  1  2  3  4
    { 1, 1, 1, 0, 0 },
    { 1, 0, 1, 1, 0 },
    { 1, 0, 0, 1, 1 },
    { 1, 1, 0, 0, 1 }
  };

  static const bool non_zero_adj[][4] = {
    //0  1  2  3
    { 1, 1, 1, 1 },
    { 0, 1, 1, 0 },
    { 0, 0, 1, 1 },
    { 1, 0, 0, 1 },
    { 1, 1, 0, 0 }
  };

  Point dd[][2] = {
    { Point(0, 0), Point(0, 0) },
    { Point(0, 0), Point(1, 1) },
    { Point(0, 1), Point(1, 0) },
    { Point(1, 1), Point(0, 0) },
    { Point(1, 0), Point(0, 1) }
  };

  if (grid[x][y] != 0) {
    for (int i = 0; i < 4; i++) {
      u = x + dd[grid[x][y]][xy_big].x;
      v = y + dd[grid[x][y]][xy_big].y;
      if (hyper_grid[u][v] != 0.0)
        return hyper_grid[u][v];
    }
  }

  memset(in_queue, false, sizeof in_queue);
  q.push(make_pair(Point(x, y), xy_big));
  in_queue[x][y] = true;
  
  while (not q.empty()) {
    x = q.front().first.x, y = q.front().first.y;
    xy_big = q.front().second;
    _v.push_back(q.front());
    q.pop();

    if (grid[x][y] == 0)
      ans += 1.0;
    else
      ans += (xy_big ? S_BIG : S_SMALL);

    if (grid[x][y] == 0) {
      for (int i = 0; i < 4; i++) {
        u = x + dx[i], v = y + dy[i];
        if (not is_valid(u, v) || in_queue[u][v])
          continue;
        in_queue[u][v] = true;
        q.push(make_pair(Point(u, v), zero_big[i][grid[u][v]]));
      }
    } else {
      for (int i = 0; i < 4; i++) {
        u = x + dx[i], v = y + dy[i];
        if (not is_valid(u, v) || in_queue[u][v])
          continue;
        if (xy_big) {
          if (non_zero_adj[grid[x][y]][i]) {
            in_queue[u][v] = true;
            q.push(make_pair(Point(u, v), true));
          }
        } else {
          if (not non_zero_adj[grid[x][y]][i] && grid[u][v] == 0) {
            in_queue[u][v] = true;
            q.push(make_pair(Point(u, v), true));
          }
        }
      }
    }
  }

  static const int zx[] = { 0, 0, 1, 1 };
  static const int zy[] = { 0, 1, 1, 0 };

  vector<pair<Point, bool> >::iterator it;
  for (it = _v.begin(); it != _v.end(); it++) {
    u = it->first.x;
    v = it->first.y;
    bool uv_big = it->second;
    if (grid[u][v] == 0) {
      for (int i = 0; i < 4; i++) {
        x = u + zx[i];
        y = v + zy[i];
        hyper_grid[x][y] = ans;
      }
    } else {
      x = u + dd[grid[u][v]][uv_big].x;
      y = v + dd[grid[u][v]][uv_big].y;
      hyper_grid[x][y] = ans;
    }
  }
  return ans;
}  

int main() {
  int no = 1, T, q, x, y;
  scanf("%d", &T);
  while (T--) {
    printf("Case %d:\n", no++);
    readf();

    memset(hyper_grid, 0.0, sizeof(hyper_grid));

    scanf("%d", &q);
    while (q-- > 0) {
      scanf("%d %d", &x, &y);
      pair<Point, bool> pp = get_first_point(x, y);
      if (pp.first.x == -1 && pp.first.y == -1)
        puts("0");
      else {
        printf("%.10Lf\n", bfs(pp.first.x, pp.first.y, pp.second));
      }
    }
  }
  return 0;
}
