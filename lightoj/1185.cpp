#include <stdio.h>
#include <string.h>
#include <queue>
#include <vector>

using namespace std;

#define SZ        128
#define NOT_CARRY   1
#define CARRY       0
#define UNLABLED   -1

vector<int> G[SZ];
int n, m, lable[SZ];
bool a[SZ][SZ];

pair<int, int> bfs() {
  queue<int> q;
  int u, v;
  pair<int, int> ans(0, 0);

  memset(lable, UNLABLED, sizeof(lable));

  for (int i = 0; i < G[1].size(); i++) {
    q.push(G[1][i]);
    lable[G[1][i]] = NOT_CARRY;
  }

  while (!q.empty()) {
    u = q.front(); q.pop();

    if (lable[u] == CARRY)
      ans.first++;
    ans.second++;
    
    for (int i = 0; i < G[u].size(); i++) {
      v = G[u][i];
      if (lable[v] == UNLABLED) {
	lable[v] = (lable[u] == CARRY ? NOT_CARRY : CARRY);
	q.push(v);
	a[u][v] = a[v][u] = false;
      }
    }
  }
  return ans;
}

int main() {
  int no = 1, T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
      G[i].clear();
    memset(a, false, sizeof(a));
    for (int i = 1; i <= m; i++) {
      int u, v;
      scanf("%d %d", &u, &v);
      G[u].push_back(v);
      G[v].push_back(u);
      a[u][v] = true;
    }
    pair<int, int> ans = bfs();
    bool has_odd_circuit = false;

    for (int u = 1; u <= n; u++)
      for (int v = 1; v <= n; v++)
	if (a[u][v] && lable[u] == lable[v] && lable[u] != -1) {
	  has_odd_circuit = true;
	  goto print_result;
	}
  print_result:
    printf("Case %d: %d\n", no++,
	   has_odd_circuit ? ans.second : ans.first);
  }
  return 0;
}
