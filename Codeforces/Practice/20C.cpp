#include <stdio.h>
#include <queue>
#include <set>
#include <vector>
#include <string.h>

using namespace std;

typedef pair<int, int> ii;

#define SZ 100005
#define INF 1000000000000LL

typedef long long ll;

int parent[SZ], n, m;
ll d[SZ];
set<ii> G[SZ];

ll dijkstra(int s, int t) {
  set<pair<ll, int> > q;

  for (int u = 1; u <= n; u++)
    d[u] = INF;
  q.insert(ii(0, s));
  d[s] = 0;
  parent[s] = -1;
  
  while (!q.empty()) {
    ll w = q.begin()->first;
    int u = q.begin()->second;
    q.erase(q.begin());

    if (u == t)
      return w;

    for (set<ii>::iterator it = G[u].begin(); it != G[u].end(); it++) {
      if (d[it->first] > d[u] + it->second) {
        if (d[it->first] != INF)
          q.erase(q.find(ii(d[it->first], it->first)));
        d[it->first] = d[u] + it->second;
        parent[it->first] = u;
        q.insert(ii(d[it->first], it->first));
      }
    }
  }

  return -1LL;
}

void init() {
  int u, v, w;
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; i++) {
    scanf("%d %d %d", &u, &v, &w);
    G[u].insert(ii(v, w));
    G[v].insert(ii(u, w));
  }
}

void print() {
  vector<int> ans;
  for (int u = n; u != -1; u = parent[u])
    ans.push_back(u);
  for (int i = ans.size() - 1; i >= 0; i--)
    printf("%d ", ans[i]);
  printf("\n");
}

int main() {
  init();
  if (dijkstra(1, n) == -1LL)
    puts("-1");
  else
    print();
  return 0;
}
