#include <stdio.h>
#include <string.h>

#define SZ 32
#define st(a) ((a) / 10000)
#define nd(a) (((a) / 100) % 100)
#define rd(a) ((a) % 100)
#define zip(a, b, c) ((a) * 10000 + (b) * 100 + (c))

const int dx[] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };
const int dy[] = { 0, 0, 1, 1, 1, 0, -1, -1, -1 };
const char *direction[] = { "*",  "U", "UR",
			    "R", "DR",  "D",
			    "DL",  "L", "UL" };

int m, n, q, name_len;
char grid[SZ][SZ], trace[SZ][SZ][SZ], name[SZ];

void readf() {
  scanf("%d %d", &m, &n);
  for (int i = 1; i <= m; i++)
    scanf(" %s ", grid[i] + 1);
}

void print(int x, int y, int idx) {
  int i, ans[SZ * SZ], n_ans;

  n_ans = 0;
  while (idx > 0) {
    i = trace[x][y][idx];
    ans[n_ans++] = i;
    x -= dx[i];
    y -= dy[i];
    idx--;
  }

  printf("found: (%d,%d)", x, y);
  for (i = n_ans - 1; i >= 0; i--) {
    printf(", %s", direction[ans[i]]);
  }
  printf("\n");
}

int dfs(int x, int y, int idx) {
  if (idx >= name_len - 1)
    return zip(x, y, idx);
  int u, v, ans;
    
  for (int i = 0; i < 9; i++) {
    u = x + dx[i]; v = y + dy[i];
    if (u >= 1 && v >= 1 && u <= m && v <= n) {
      if (trace[u][v][idx + 1] != -1)
	continue;
      if (grid[u][v] == name[idx + 1]) {
	trace[u][v][idx + 1] = i;
	ans = dfs(u, v, idx + 1);
	if (ans != -1)
	  return ans;
      }
    }
  }
  return -1;
}

int main() {
  int no = 1, T;
  scanf("%d", &T);
  while (T--) {
    readf();
    scanf("%d", &q);
    printf("Case %d:\n", no++);
    while (q--) {
      scanf(" %s ", name);
      name_len = strlen(name);
      printf("%s ", name);

      memset(trace, -1, sizeof(trace));

      int ans = -1;
      for (int u = 1; u <= m; u++)
	for (int v = 1; v <= n; v++) {	  
	  if (grid[u][v] == name[0]) {
	    ans = dfs(u, v, 0);	    
	    if (ans > -1)
	      goto print_result;
	  }
	}

    print_result:      
      if (ans == -1)
	printf("not found\n");
      else
	print(st(ans), nd(ans), rd(ans));
    }
  }
  return 0;
}
