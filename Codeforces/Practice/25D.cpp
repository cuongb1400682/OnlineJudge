#include <stdio.h>
#include <map>
#include <set>
#include <vector>

using namespace std;

#define SZ 1024

typedef pair<int, int> ii;

set<int> G[SZ];
int n;

void readf() {
  int u, v;
  scanf("%d", &n);
  for (int i = 1; i <= n - 1; i++) {
    scanf("%d %d", &u, &v);
    G[u].insert(v);
    G[v].insert(u);
  }
}

void dfs(int u, int *parent, set<ii> &z) {
  for (set<int>::iterator it = G[u].begin(); it != G[u].end(); it++) {
    if (parent[*it] == 0) {
      parent[*it] = u;
      dfs(*it, parent, z);
    } else if (parent[*it] != u && parent[u] != *it) {
      if (u < *it)
        z.insert(ii(u, *it));
      else
        z.insert(ii(*it, u));
    }
  }
}

void solve() {
  int parent[SZ] = {0};
  set<ii> z;
  vector<int> r;
  for (int u = 1; u <= n; u++) 
    if (parent[u] == 0) {
      parent[u] = u;
      dfs(u, parent, z);
      r.push_back(u);
    }

  vector<pair<ii, ii> > ans;
  for (int i = 1; i < (int) r.size(); i++) {
    ii e = *z.begin();
    ans.push_back(make_pair(e, ii(r[i], r[i - 1])));
    z.erase(z.begin());
  }

  printf("%d\n", (int) ans.size());
  for (int i = 0; i < (int) ans.size(); i++) {
    ii A = ans[i].first;
    ii B = ans[i].second;
    printf("%d %d %d %d\n", A.first, A.second, B.first, B.second);
  }
}

int main() {
  readf();
  solve();
  return 0;
}
