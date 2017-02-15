// non-recursive dfs

#include <stdio.h>
#include <string.h>

#define SZ 512

const int dx[] = { 0, -1, 0, 1 };
const int dy[] = { -1, 0, 1, 0 };

struct StackEntry {
  int first, second;
} stk[SZ * SZ];

int m, n, q, a[SZ][SZ], top;
char grid[SZ][SZ];

bool valid(int x, int y) {
  return (x >= 0 && y >= 0 && x < m && y < n) && (grid[x][y] != '#');
}

StackEntry make_entry(int x, int y) {
  StackEntry ans = { 0, 0 };
  ans.first = x;
  ans.second = y;
  return ans;
}

int dfs(int x, int y) {
  if (a[x][y] != -1)
    return a[x][y];
  
  int ans = 0, u, v, l;
  bool visited[SZ][SZ];

  memset(visited, false, sizeof(visited));
  if (grid[x][y] != '#') {
    stk[++top] = make_entry(x * 1000 + y, 0);
    visited[x][y] = true;
  }
  
  while (top >= 0) {
    StackEntry tmp = stk[top--];
    x = tmp.first / 1000; y = tmp.first % 1000;
    l = tmp.second; 

    if (grid[x][y] == 'C')
      ans++;

    for (int i = 0; i < 4; i++) {
      u = x + dx[i]; v = y + dy[i];
      if (valid(u, v) && not visited[u][v]) {
	stk[++top] = make_entry(u * 1000 + v, l + 1);
	visited[u][v] = true;
      }
    }
  }

  for (int x = 0; x < m; x++)
    for (int y = 0; y < m; y++)
      if (visited[x][y])
	a[x][y] = ans;

  return ans;
}

int main() {
  int T, no = 1, x, y;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d %d", &m, &n, &q);
    for (int i = 0; i < m; i++)
      scanf(" %s ", grid[i]);
    memset(a, -1, sizeof(a));
    printf("Case %d:\n", no++);
    top = -1;
    while (q--) {
      scanf("%d %d", &x, &y);
      x--, y--;
      printf("%d\n", dfs(x, y));
      //printf("\n");
    }
  }
  return 0;
}
