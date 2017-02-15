#include <stdio.h>
#include <string.h>
#include <queue>
#include <vector>

using namespace std;

#define SZ 30005

vector<pair<int, int> > G[SZ];
int d1[SZ], d2[SZ], n;

pair<int, int> bfs(int u, int *d) {
  queue<pair<int, int> > q;
  bool in_queue[SZ] = {0};
  int l, v, w;
  pair<int, int> ans(0, 0);

  q.push(make_pair(u, 0));
  d[u] = 0;
  in_queue[u] = true;

  while (not q.empty()) {
    u = q.front().first;
    l = q.front().second;
    q.pop();
    d[u] = l;
    if (ans.second < l)
      ans = make_pair(u, l);
    for (int i = 0; i < (int) G[u].size(); i++) {
      v = G[u][i].first;
      w = G[u][i].second;
      if (not in_queue[v]) {
	in_queue[v] = true;
	q.push(make_pair(v, l + w));
      }
    }
  }
  return ans;
}

int main() {
  int T, no = 1;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      G[i].clear();
    for (int i = 0; i < n - 1; i++) {
      int u, v, w;
      scanf("%d %d %d", &u, &v, &w);
      G[u].push_back(make_pair(v, w));
      G[v].push_back(make_pair(u, w));
    }
    printf("Case %d:\n", no++);
    int u = bfs(0, d1).first;
    int v = bfs(u, d1).first;
    bfs(v, d2);
    for (int i = 0; i < n; i++)
      printf("%d\n", max(d1[i], d2[i]));
  }
  return 0;
}
