#include <stdio.h>
#include <queue>
#include <vector>

using namespace std;

#define SZ 30005

vector<pair<int, int> > G[SZ];
int n;

pair<int, int> furthest(int u) {
  queue<pair<int, int> > q;
  pair<int, int> ans(0, 0);
  bool in_queue[SZ] = { false };
  int w, v, l;

  q.push(make_pair(u, 0));
  in_queue[u] = true;
  
  while (not q.empty()) {
    u = q.front().first; l = q.front().second; q.pop();
    if (ans.second < l)
      ans = make_pair(u, l);
    for (int i = 0; i < (int) G[u].size(); i++) {
      v = G[u][i].first; w = G[u][i].second;
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
    for (int i = 1; i <= n; i++)
      G[i].clear();
    int u, v, w;
    for (int i = 1; i <= n - 1; i++) {
      scanf("%d %d %d", &u, &v, &w);
      u++; v++;
      G[u].push_back(make_pair(v, w));
      G[v].push_back(make_pair(u, w));
    }
    printf("Case %d: %d\n", no++, furthest(furthest(1).first).second);
    
  }
  return 0;
}
