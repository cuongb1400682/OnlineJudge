#include <stdio.h>
#include <map>
#include <set>

using namespace std;

#define SZ 100005

map<int, set<int> > G;
int n, m, deg[SZ];

void init() {
  int u, v;
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; i++) {
    scanf("%d %d", &u, &v);
    G[u].insert(v);
    G[v].insert(u);
    deg[u]++;
    deg[v]++;
  }
}

void solve() {
  map<int, int> cnt;
  for (int u = 1; u <= n; u++)
    cnt[deg[u]]++;
  if (cnt[1] == 2 && cnt[2] == n - 2)
    puts("bus topology");
  else if(cnt[2] == n)
    puts("ring topology");
  else if (cnt[1] == n - 1 && cnt[n - 1] == 1)
    puts("star topology");
  else
    puts("unknown topology");
}

int main() {
  init();
  solve();
  return 0;
}
