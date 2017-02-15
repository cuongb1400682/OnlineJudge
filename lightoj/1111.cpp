#include <stdio.h>
#include <string.h>
#include <queue>

using namespace std;

#define SZ 1024

vector<int> G[SZ];
int person[128], K, N, M, cnt[SZ];
bool vis[SZ];

void dfs(int u) {
  if (vis[u]) return;
  vis[u] = true;
  cnt[u]++;
  for (int i = 0; i < (int) G[u].size(); i++)
    dfs(G[u][i]);
}

int main() {
  int T, no = 1;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d %d", &K, &N, &M);
    for (int i = 1; i <= N; i++)
      G[i].clear();
    for (int i = 1; i <= K; i++)
      scanf("%d", &person[i]);
    for (int i = 1; i <= M; i++) {
      int u, v;
      scanf("%d %d", &u, &v);
      G[u].push_back(v);
    }
    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= K; i++) {
      memset(vis, false, sizeof(vis));
      dfs(person[i]);
    }
    int ans = 0;
    for (int i = 1; i <= N; i++)
      if (cnt[i] == K)
	++ans;
    printf("Case %d: %d\n", no++, ans);
  }
  return 0;
}
