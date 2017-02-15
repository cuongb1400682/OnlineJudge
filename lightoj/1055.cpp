#include <stdio.h>
#include <string.h>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

#define SZ 16

const int dx[] = { 0, 1, 0, -1 };
const int dy[] = { 1, 0, -1, 0 };

struct Cell {
  int x, y;
  Cell(int x = 0, int y = 0) : x(x), y(y) {
  }
  bool valid(int n) {
    return x >= 0 && y >= 0 && x < n && y < n;
  }
};

struct TripleCell {
  Cell cells[3];
  TripleCell() {
    cells[0] = Cell(0, 0);
    cells[1] = Cell(0, 0);
    cells[2] = Cell(0, 0);
  }
  TripleCell(Cell a, Cell b, Cell c) {
    cells[0] = a;
    cells[1] = b;
    cells[2] = c;
  }
  Cell& operator[](int i) {
    return cells[i];
  }
  int hash() {
    int c[3], i, j;
    c[0] = cells[0].x * 10 + cells[0].y;
    c[1] = cells[1].x * 10 + cells[1].y;
    c[2] = cells[2].x * 10 + cells[2].y;
    for (i = 0; i < 2; i++)
      for (j = i + 1; j < 3; j++)
	if (c[i] > c[j])
	  swap(c[i], c[j]);
    return c[0] * 10000 + c[1] * 100 + c[2];
  }
};

typedef int (*CmpFunc)(Cell, Cell);

char grid[SZ][SZ];
int n;
TripleCell s, t;

bool operator==(Cell a, Cell b) {
  return a.x == b.x && a.y == b.y;
}

int cmp_R_dec_vert(Cell a, Cell b) {
  if (a.y != b.y)
    return b.y - a.y;
  return b.x - a.x;
}

int cmp_D_dec_hrzt(Cell a, Cell b) {
  if (a.x != b.x)
    return b.x - a.x;
  return b.y - a.y;  
}

int cmp_L_inc_vert(Cell a, Cell b) {
  if (a.y != b.y)
    return a.y - b.y;
  return a.x - b.x;  
}

int cmp_U_inc_hrzt(Cell a, Cell b) {
  if (a.x != b.x)
    return a.x - b.x;
  return a.y - b.y;
}

void TripleCellSort(TripleCell &a, int *idx, CmpFunc cmp) {
  for (int i = 0; i < 2; i++)
    for (int j = i + 1; j < 3; j++)
      if (cmp(a[i], a[j]) > 0) {
	swap(a[i], a[j]);
	swap(idx[i], idx[j]);
      }
}

TripleCell next_state(TripleCell a, int z) {
  int idx[] = { 0, 1, 2 };
  bool vis[SZ][SZ];
  CmpFunc cmp_func[] = {
    cmp_R_dec_vert, cmp_D_dec_hrzt,
    cmp_L_inc_vert, cmp_U_inc_hrzt
  };

  memset(vis, false, sizeof(vis));

  TripleCellSort(a, idx, cmp_func[z]);
  
  for (int i = 0; i <= 2; i++) {
    Cell p = Cell(a[i].x + dx[z], a[i].y + dy[z]);
    if (p.valid(n) && grid[p.x][p.y] != '#' && !vis[p.x][p.y])
      a[i] = p;
    vis[a[i].x][a[i].y] = true;
  }        

  TripleCell ans;
  for (int i = 0; i < 3; i++)
    ans[idx[i]] = a[i];
  return ans;
}

bool valid(TripleCell c) {
  return
    c[0].valid(n) && (grid[c[0].x][c[0].y] != '#') &&
    c[1].valid(n) && (grid[c[1].x][c[1].y] != '#') &&
    c[2].valid(n) && (grid[c[2].x][c[2].y] != '#');
}

int bfs(TripleCell x) {
  queue<pair<TripleCell, int> > q;
  bool visited[1000000];
  int l;
  TripleCell y;
  
  memset(visited, false, sizeof(visited));

  q.push(make_pair(x, 0));
  visited[x.hash()] = true;

  while (!q.empty()) {
    x = q.front().first; l = q.front().second; q.pop();
      
    if (x.hash() == t.hash())
      return l;

    for (int i = 0; i < 4; i++) {
      y = next_state(x, i);
      if (!visited[y.hash()] && valid(y)) {
	q.push(make_pair(y, l + 1));
	visited[y.hash()] = true;
      }
    }
  }
  return -1;
}

int main() {
  int no = 1, T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf(" %s ", grid[i]);
    int cnt = 0;
    for (int x = 0; x < n; x++)
      for (int y = 0; y < n; y++) {
	if (grid[x][y] >= 'A' && grid[x][y] <= 'C') {
	  s[grid[x][y] - 'A'] = Cell(x, y);
	  grid[x][y] = '.';
	}
	if (grid[x][y] == 'X') {
	  t[cnt++] = Cell(x, y);
	  grid[x][y] = '.';
	}
      }
    printf("Case %d: ", no++);
    int ans = bfs(s);
    if (ans < 0)
      puts("trapped");
    else
      printf("%d\n", ans);
  }
  return 0;
}
