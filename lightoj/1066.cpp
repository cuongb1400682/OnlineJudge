#include <stdio.h>
#include <string.h>
#include <queue>
#include <ctype.h>

using namespace std;

#define SZ 11

const int dx[] = { -1, 0, 1, 0 };
const int dy[] = { 0, -1, 0, 1 };

int n;
char grid[SZ][SZ];

int bfs(int c, pair<int, int> &p, int x, int y) {
  queue<pair<pair<int, int>, int> > q;
  bool in_queue[SZ][SZ];

  memset(in_queue, false, sizeof(in_queue));  
  q.push(make_pair(pair<int, int>(x, y), 0));
  in_queue[x][y] = true;

  while (not q.empty()) {
    int u = q.front().first.first;
    int v = q.front().first.second;
    int l = q.front().second;
    q.pop();

    if (grid[u][v] == c) {
      p = make_pair(u, v);
      return l;
    }

    for (int i = 0; i < 4; i++) {
      x = u + dx[i], y = v + dy[i];
      if (x >= 0 && y >= 0 && x < n && y < n)
	if (not in_queue[x][y] && (grid[x][y] == '.' || grid[x][y] == c)) {
	  q.push(make_pair(pair<int, int>(x, y), l + 1));
	  in_queue[x][y] = true;
	}
    }
  }

  p = make_pair(-1, -1);
  return -1;
}

int main() {
  int T, no = 1;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf(" %s ", grid[i]);
    
    pair<int, int> p;
    int x, y, ans;
    ans = x = y = 0;

    char final_char = 'A' - 1;
    for (int u = 0; u < n; u++)
      for (int v = 0; v < n; v++)
	if (isupper(grid[u][v])) {
	  if (final_char < grid[u][v]) 
	    final_char = grid[u][v];
	  if (grid[u][v] == 'A')
	    x = u, y = v;
	}
	  
    for (int c = 'A'; c <= final_char; c++) {
      int dist = bfs(c, p, x, y);
      if (dist == -1) {
    	ans = -1;
    	break;
      }
      grid[p.first][p.second] = '.';
      if (c != 'A') 
    	ans += dist;
      x = p.first;
      y = p.second;
    }
    printf("Case %d: ", no++);
    if (ans < 0)
      puts("Impossible");
    else
      printf("%d\n", ans);
  }
  return 0;
}
