#include <stdio.h>
#include <queue>
#include <set>
#include <map>

using namespace std;

typedef pair<int, int> ii;

map<int, set<ii> > G;
int n, m;

void init() {
  int u, v, w;
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; i++) {
    scanf("%d %d %d", &u, &v, &w);
    G[u].insert(ii(v, w));
    G[v].insert(ii(u, w));
  }
}

int bfs(int s, int t) {
  queue<ii> q;
  set<ii> vis;
  set<int> ans;
  int u, clr;
  set<ii>::iterator it;

  for (it = G[s].begin(); it != G[s].end(); it++) {
    q.push(*it);
    vis.insert(*it);
  }

  while (!q.empty()) {
    u = q.front().first;
    clr = q.front().second;
    q.pop();

    if (u == t)
      ans.insert(clr);
    
    for (it = G[u].begin(); it != G[u].end(); it++) {
      if (it->second == clr && vis.count(*it) == 0) {
        q.push(*it);
        vis.insert(*it);
      }
    }
  }

  return ans.size();
}

int main() {
  int q;
  init();
  scanf("%d", &q);
  for (int u, v; q--; ) {
    scanf("%d %d", &u, &v);
    printf("%d\n", bfs(u, v));
  }
  return 0;
}
