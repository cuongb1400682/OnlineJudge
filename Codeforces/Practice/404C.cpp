#include <stdio.h>
#include <vector>
#include <set>

using namespace std;

#define SZ 100005

typedef pair<int, int> ii;

int n, k, max_dist, root;
int d1[SZ], d2[SZ];
vector<int> V[SZ];
vector<ii> edge;
set<int> G[SZ];

void dfs(int u, int dist) {
  if (max_dist <= dist) {
    return;
  }
  int max_deg = (u == root ? k : k - 1);
  for (int i = 1; i <= max_deg && !V[dist + 1].empty(); i++) {
    int v = V[dist + 1].back();
    V[dist + 1].pop_back();

    edge.push_back(ii(u, v));
    G[u].insert(v);
    G[v].insert(u);

    dfs(v, dist + 1);
  }
}

void dfs2(int u, int *d2) {
  for (set<int>::iterator it = G[u].begin(); it != G[u].end(); it++) {
    if (d2[*it] == 0) {
      d2[*it] = d2[u] + 1;
      dfs2(*it, d2);
    }
  }
}

int main() {
  int i;
  scanf("%d %d", &n, &k);
  max_dist = 0;
  for (i = 1; i <= n; i++) {
    int dist;
    scanf("%d", &dist);
    V[dist].push_back(i);
    max_dist = max(max_dist, dist);
    d1[i] = dist;
  }

  for (i = 1; i <= max_dist; i++)
    if (V[i].size() > V[i - 1].size() * k)
      break;

  if (i <= max_dist || V[0].size() != 1)
    puts("-1");
  else {
    root = V[0][0];
    dfs(V[0][0], 0); V[0].pop_back();

    d2[root] = 1;
    dfs2(root, d2);

    for (int u = 1; u <= n; u++)
      if (d1[u] != d2[u] - 1) {
        puts("-1");
        return 0;
      }
    
    printf("%d\n", (int) edge.size());
    for (int i = 0; i < (int) edge.size(); i++)
      printf("%d %d\n", edge[i].first, edge[i].second);
  }
  return 0;
}
