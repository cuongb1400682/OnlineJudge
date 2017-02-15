#include <stdio.h>
#include <queue>

using namespace std;

const int hx[] = { 0, 1, 0, -1 };
const int hy[] = { 1, 0, -1, 0 };

int n_test, m, n, x, y;
char grid[64][64];

int count_cells() {
  queue<pair<int, int> > q;
  int ans = 1, u, v;
    
  q.push(make_pair(x, y));
  while (not q.empty()) {
    x = q.front().first;
    y = q.front().second;
    q.pop();
    for (int i = 0; i < 4; i++) {
      u = x + hx[i];
      v = y + hy[i];
      if (u >= 0 && v >= 0 && u < m && v < n) 
	if (grid[u][v] == '.') {
	  q.push(make_pair(u, v));
	  grid[u][v] = '@';
	  ans++;
	}
    }
  }
    
  return ans;
}

int main() {
  int no = 1;
  scanf("%d", &n_test);
  while (n_test--) {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
      scanf("%s", grid[i]);
      for (int j = 0; j < n; j++)
	if (grid[i][j] == '@')
	  x = i, y = j;
    }
    printf("Case %d: %d\n", no++, count_cells());
  }
  return 0;
}

