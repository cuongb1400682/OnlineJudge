#include <stdio.h>
#include <string.h>
#include <set>

using namespace std;

#define SZ 1024

const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

char grid[SZ][SZ];
int a[SZ][SZ], n, n_label;
set<int> G[SZ];

void dfs_label(int x, int y, int lab) {
  if (x <= 0 || y <= 0 || x > n || y > n || a[x][y] != 0 || grid[x][y] == '.')
    return;
  a[x][y] = lab;
  for (int i = 0; i < 4; i++)
    dfs_label(x + dx[i], y + dy[i], lab);
}

void init() {
  int n_snow_drift, x, y;

  // reading the map
  scanf("%d", &n_snow_drift);
  
  memset(grid, '.', sizeof(grid));
  n = 1;
  for (int i = 0; i < n_snow_drift; i++) {
    scanf("%d %d", &x, &y);
    grid[x][y] = '#';
    n = max(max(x, y), n);
  }

  // labeling all connected components
  memset(a, 0, sizeof(a));

  n_label = 0;
  for (int x = 1; x <= n; x++)
    for (int y = 1; y <= n; y++)
      if (grid[x][y] == '#' && a[x][y] == 0)
        dfs_label(x, y, ++n_label);
}

void add_edges(int u, const set<int>& adj) {
  for (set<int>::iterator it = adj.begin(); it != adj.end(); it++) {
    if (*it != u) {
      G[u].insert(*it);
      G[*it].insert(u);
    }
  }
}

void dfs(int u, bool *vis) {
  if (vis[u])
    return;
  vis[u] = true;
  for (set<int>::iterator it = G[u].begin(); it != G[u].end(); it++)
    dfs(*it, vis);
}

void solve() {
  set<int> h[SZ], v[SZ]; // horizontal, vertical

  // creating new graph
  for (int x = 1; x <= n; x++) 
    for (int y = 1; y <= n; y++) 
      if (a[x][y] != 0) {
        add_edges(a[x][y], h[x]);
        h[x].insert(a[x][y]);
        
        add_edges(a[x][y], v[y]);
        v[y].insert(a[x][y]);
      }
  
  bool vis[SZ * SZ] = { false };
  int cnt = 0;
  for (int u = 1; u <= n_label; u++)
    if (!vis[u]) {
      dfs(u, vis);
      cnt++;
    }  

  printf("%d\n", cnt - 1);
}

int main() {
  init();
  solve();
}

