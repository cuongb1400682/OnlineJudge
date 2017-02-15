#include <stdio.h>
#include <string.h>
#include <queue>
#include <vector>

using namespace std;

#define SZ 128

vector<int> G[SZ];
int d1[SZ], d2[SZ], s, t, n, n_test, r;

void sssp(int s, int *d) {
  queue<pair<int, int> > q;
  bool in_queue[SZ] = {0};
  q.push(make_pair(s, 0)); 
  in_queue[s] = true;
  while (not q.empty()) {
    int u = q.front().first; 
    int l = q.front().second;
    d[u] = l;
    q.pop();
    for (int i = 0; i < (int) G[u].size(); i++) {
      int v = G[u][i];
      if (not in_queue[v]) {
	q.push(make_pair(v, l + 1));
	in_queue[v] = true;
      }
    }
  }
}

int main() {
  int no = 1;
  scanf("%d", &n_test);
  while (n_test--) {
    scanf("%d %d", &n, &r);
    for (int i = 1; i <= n; i++)
      G[i].clear();
    for (int i = 1; i <= r; i++) {
      int u, v;
      scanf("%d %d", &u, &v); u++, v++;
      G[u].push_back(v);
      G[v].push_back(u);
    }
    scanf("%d %d", &s, &t); s++, t++;
    memset(d1, 0, sizeof(d1));
    sssp(s, d1);
    memset(d2, 0, sizeof(d2));
    sssp(t, d2);
    int ans = -1;
    for (int i = 1; i <= n; i++)
      ans = max(ans, d1[i] + d2[i]);
    printf("Case %d: %d\n", no++, ans);
  }
  return 0;
}
