#include <stdio.h>
#include <set>
#include <vector>
#include <queue>
#include <string.h>
#include <algorithm>

using namespace std;

#define SZ 50005

set<int> G[SZ];
int s, t, n, parent[SZ];

void readf() {
  scanf("%d", &n);
  for (int i = 0; i < SZ; i++)
    G[i].clear();
  for (int i = 1, u, v; i <= n; i++) {
    scanf("%d", &u);
    if (i > 1) {
      G[u].insert(v);
      G[v].insert(u);
    }
    if (i == 1) s = u;
    if (i == n) t = u;
    v = u; 
  }
}

void bfs() {
  queue<int> q;
  int u, v;
  set<int>::iterator it;

  memset(parent, 0, sizeof(parent));

  q.push(s);
  parent[s] = s;

  while (!q.empty()) {
    u = q.front(); q.pop();
    if (u == t) {
      break;
    }
    for (it = G[u].begin(); it != G[u].end(); it++) {
      v = *it;
      if (parent[v] == 0) {
        q.push(v);
        parent[v] = u;
      }
    }
  }
}

void print() {
  vector<int> ans;
  for (int u = t; u != s; u = parent[u])
    ans.push_back(u);
  ans.push_back(s);
  reverse(ans.begin(), ans.end());
  for (int i = 0; i < ans.size(); i++)
    printf("%d%s", ans[i], i == ans.size() - 1 ? "\n" : " ");
}

int main() {
  int T, no = 1;
  scanf("%d", &T);
  while (T--) {
    readf();
    bfs();
    printf("Case %d:\n", no++);
    print();
  }
  return 0;
}
