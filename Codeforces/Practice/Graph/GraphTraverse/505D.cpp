#include <stdio.h>
#include <string.h>
#include <vector>
#include <stack>

using namespace std;

#define SZ 100005

vector<int> G[SZ];
int n, m, num[SZ], low[SZ], label, comp_size[SZ];
bool on_stack[SZ], vis[SZ];
stack<int> stk;

void readf() {
  int u, v;
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; i++) {    
    scanf("%d %d", &u, &v);
    G[u].push_back(v);
    G[v].push_back(-u);
  }
}

void tarjan(int u) {
  int v;
  num[u] = low[u] = ++label;

  stk.push(u); on_stack[u] = true;
  for (int i = 0; i < (int) G[u].size(); i++) {
    v = G[u][i];
    if (v < 0)
      continue;
    if (num[v] == 0) {
      tarjan(v);
      low[u] = min(low[u], low[v]);
    } else if (on_stack[v]) {
      low[u] = min(low[u], num[v]);
    }      
  }

  if (num[u] == low[u]) {
    vector<int> V;
    do {
      V.push_back(stk.top());
      on_stack[stk.top()] = false;
      stk.pop();
    } while (V.back() != u);
    
    for (int i = 0; i < (int) V.size(); i++)
      comp_size[V[i]] = V.size();
  }
}

void dfs(int u, bool *vis, int &sz, bool &has_circle) {
  vis[u] = true;
  sz++;
  if (comp_size[u] != 1)
    has_circle = true;
  
  for (int i = 0; i < (int) G[u].size(); i++) {
    int v = G[u][i];
    if (v < 0)
      v *= -1;
    if (!vis[v])
      dfs(v, vis, sz, has_circle);
  }
}

void solve() {
  for (int u = 1; u <= n; u++) {
    if (comp_size[u] == 0)
      tarjan(u);
  }

  int ans = 0;
  memset(vis, 0, sizeof(vis));
  for (int u = 1; u <= n; u++)
    if (!vis[u]) {
      int sz = 0;
      bool has_circle = false;
      dfs(u, vis, sz, has_circle);
      ans += (sz - !has_circle);
    }

  printf("%d\n", ans);
}

int main() {
  readf();
  solve();
  return 0;
}
