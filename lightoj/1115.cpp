#include <stdio.h>
#include <string.h>
#include <queue>

using namespace std;

#define SZ 55

typedef char table_t[SZ][SZ];

const int dx[] = { 0, 1, 0, -1 };
const int dy[] = { 1, 0, -1, 0 };

int m, n;
table_t tab, tab2;
bool vis[SZ][SZ];

int fill(table_t tab, int x, int y, int c1, int c2) {
  if (x < 0 || y < 0 || x >= m || y >= n || tab[x][y] != c1)
    return 0;
  int ans = 1;
  tab[x][y] = c2;
  for (int i = 0; i < 4; i++)
    ans += fill(tab, x + dx[i], y + dy[i], c1, c2);
  return ans;
}

void make_fence(table_t tab) {
  for (int x = 0; x < m; x++) {
    if (tab[x][0] == '.')
      fill(tab, x, 0, '.', '#');
    if (tab[x][n - 1] == '.')
      fill(tab, x, n - 1, '.', '#');
  }

  for (int y = 0; y < n; y++) {
    if (tab[0][y] == '.')
      fill(tab, 0, y, '.', '#');
    if (tab[m - 1][y] == '.')
      fill(tab, m - 1, y, '.', '#');
  }
}

void isolate(int c, table_t tab1, int x, int y, table_t tab2) {
  if (x < 0 || y < 0 || x >= m || y >= n)
    return;
  if (tab1[x][y] != c || tab2[x][y] != '.')
    return;
  tab2[x][y] = tab1[x][y];
  for (int i = 0; i < 4; i++)
    isolate(c, tab1, x + dx[i], y + dy[i], tab2);
}

void p_fill(int c, table_t tab1, int x, int y, table_t tab2) {
  if (x < 0 || y < 0 || x >= m || y >= n)
    return;
  if (tab1[x][y] == '#' || vis[x][y])
    return;
  tab2[x][y] = c;
  vis[x][y] = true;
  for (int i = 0; i < 4; i++)
    p_fill(c, tab1, x + dx[i], y + dy[i], tab2);
}

void println(table_t tab) {
  for (int x = 0; x < m; x++) {
    for (int y = 0; y < n; y++)
      if (tab[x][y] == '#')
	putchar('.');
      else
	putchar(tab[x][y]);
    putchar('\n');
  }
}

int main() {
  int T, no = 1;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &m, &n);
    for (int i = 0; i < m; i++)
      scanf(" %s ", tab[i]);
    make_fence(tab);

    memset(vis, false, sizeof(vis));
    for (int x = 0; x < m; x++)
      for (int y = 0; y < n; y++)
	if (not vis[x][y] && tab[x][y] >= 'A' && tab[x][y] <= 'Z') {
	  memset(tab2, '.', sizeof(tab2));
	  isolate(tab[x][y], tab, x, y, tab2);
	  make_fence(tab2);
	  p_fill(tab[x][y], tab2, x, y, tab);
	} 
    printf("Case %d:\n", no++);
    println(tab);
  }
  return 0;
}
