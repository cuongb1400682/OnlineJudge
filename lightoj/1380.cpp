#include <bits/stdc++.h>
using namespace std;

#define dbg(x) cerr << "[" #x " = " << x << "]" << endl
template<class T>
void __dba(const T* a, int n) {
  cerr << "[";
  for (int i = 0; i < n; i++)
    cerr << (i > 0 ? ", " : "" ) << a[i];
  cerr << "]" << endl;
}
#define dba(a, n) { cerr << #a " = "; __dba(a, n); }
#define dbb(s,...) fprintf(stderr, s, __VA_ARGS__)
#define for_in(it, c)                                                   \
  for(__typeof((c).begin()) it=(c).begin(); it!=(c).end(); it++)

#define INF 0x3f3f3f3f
#define SZ 1024
typedef map<int, int> mii;
typedef pair<int, int> ii;

struct Edge {
  int u, v, w;
  Edge(int u=0, int v=0, int w=0) : u(u), v(v), w(w) {}
};

int n, m, root;
vector<Edge> g;

void readf() {
  scanf("%d%d%d", &n, &m, &root);
  g.assign(m, Edge());
  for (int i = 0, u, v, w; i < m; i++) {
    scanf("%d%d%d", &u, &v, &w);
    g[i] = Edge(u, v, w);
  }
}

int solve(vector<Edge> g, int n, int m) {
  vector<int> y, p, b;
  bitset<SZ> vis, in_cycle;
  int ans = 0, label;

  while (true) {
    y.assign(n, INF);
    p.assign(n, -1);

    // find a y[] & p[]
    for (int i = 0, u, v, w; i < (int)g.size(); i++) {
      u = g[i].u; v = g[i].v; w = g[i].w;
      if (v == root || u == v) continue;
      if (y[v] > w) {
        y[v] = w;
        p[v] = u;
      }
    }

    // check if this is strong connected graph
    for (int u = 0; u < n; u++)
      if (u != root && p[u] == -1)
        return -1;

    // check if there exist a cycle
    vis.reset();
    b.assign(n, -1);
    label = 0;
    y[root] = INF, p[root] = -1;
    for (int u = 0, v; u < n; u++) {
      if (u == root) continue;
      ans += y[u];
      in_cycle.reset();
      for (v = u; v != root && !vis[v] && !in_cycle[v]; v = p[v])
        in_cycle[v] = true;
      if (v != root && b[v] == -1 && in_cycle[v]) {
        for (int i = p[v]; i != v; i = p[i]) {
          b[i] = label;
          vis[i] = true;
        }
        b[v] = label++; vis[v] = true;
      }
    }
    if (label == 0)
      return ans;

    // re-lable the rest of vertices
    for (int u = 0; u < n; u++)
      if (b[u] == -1) b[u] = label++;

    for (int i = 0, u, v, w; i < (int)g.size(); i++) {
      u = g[i].u, v = g[i].v, w = g[i].w;
      g[i].u = b[u];
      g[i].v = b[v];
      if (b[u] != b[v])
        g[i].w = w - y[v];
    }
    root = b[root];
    n = label;
  }
}

int main(void) {
  int no = 1, nCase;
  scanf("%d", &nCase);
  while (nCase--) {
    readf();
    int ans = solve(g, n, m);
    if (ans < 0)
      printf("Case %d: impossible\n", no++);
    else
      printf("Case %d: %d\n", no++, ans);
  }
  return 0;
}
