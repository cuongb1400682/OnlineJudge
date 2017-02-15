#include <bits/stdc++.h>
using namespace std;

#define SZ 512
#define INF 0x3f3f3f3f

typedef pair<int, int> ii;

vector<ii> g[SZ];
int s, t, n, m, d[SZ], trace[SZ], weight[SZ][SZ];
bitset<SZ> vis;

struct Node {
  int v, w;
  bool is_proposed;
};

void readf() {
  scanf("%d %d", &n, &m);
  for (int i = 0; i <= n; i++)
    g[i].clear();
  memset(weight, 0, sizeof(weight));
  for (int i = 1, u, v, w; i <= m; i++) {
    scanf("%d%d%d", &u, &v, &w);
    g[u].push_back(ii(w, v));
    g[v].push_back(ii(w, u));
    if (weight[u][v] != 0) {
      weight[u][v] = min(w, weight[u][v]);
      weight[v][u] = min(w, weight[v][u]);
    } else {
      weight[u][v] = w;
      weight[v][u] = w;
    }
  }
  scanf("%d", &s);
}

void solve() {
  priority_queue<ii, vector<ii>, greater<ii> > q;
  
  vis.reset();
  q.push(ii(0, s));
  for (int u = 0; u <= n; u++) {
    d[u] = INF;
    trace[u] = -1;
  }

  d[s] = 0;

  while (!q.empty()) {
    int u = q.top().second;
    int w = q.top().first;
    q.pop();
    if (w != d[u]) continue;
    vis[u] = true;
    for (int i = 0, v; i < (int)g[u].size(); i++) {
      v = g[u][i].second;
      if (!vis[v] && d[v] > max(d[u], g[u][i].first)) {
	d[v] = max(d[u], g[u][i].first);
	trace[v] = u;
	q.push(ii(d[v], v));
      }
    }
  }
}

void print() {
  static int caseNo = 1;
  printf("Case %d:\n", caseNo++);
  for (int i = 0; i < n; i++) {
    if (d[i] == INF)
      puts("Impossible");
    else
      printf("%d\n", d[i]);
  }
}

int main(void) {
#ifndef ONLINE_JUDGE
  freopen("input.txt", "rt", stdin);
#endif
  int nCase;
  scanf("%d", &nCase);
  while (nCase--) {
    readf();
    solve();
    print();
  }
  return 0;
}
