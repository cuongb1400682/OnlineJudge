#include <stdio.h>
#include <set>

using namespace std;

#define SZ 3005

typedef long long ll;

ll n, m, x[3], cnt[SZ][SZ];
bool vis[SZ];
set<ll> G[SZ];

void init() {
  ll u, v;
  scanf("%lld %lld", &n, &m);
  for (ll i = 0; i < m; i++) {
    scanf("%lld %lld", &u, &v);
    G[u].insert(v);
  }
}

void dfs(ll idx) {
  if (idx >= 3) {
    cnt[x[0]][x[2]]++;
    return;
  }

  ll u = x[idx - 1];
  for (set<ll>::iterator it = G[u].begin(); it != G[u].end(); it++) {
    ll v = *it;
    if (!vis[v]) {
      vis[v] = true;
      x[idx] = v;
      dfs(idx + 1);
      x[idx] = 0;
      vis[v] = false;
    }
  }
}

void solve() {
  for (ll u = 1; u <= n; u++) {
    vis[u] = true;
    x[0] = u;
    dfs(1);
    x[0] = 0;
    vis[u] = false;
  }

  ll ans = 0;
  for (ll u = 1; u <= n; u++)
    for (ll v = 1; v <= n; v++)
      if (u != v && cnt[u][v] > 0) {
        if (cnt[u][v] & 1)
          ans += ((cnt[u][v] - 1) / 2) * cnt[u][v];
        else
          ans += (cnt[u][v] - 1) * (cnt[u][v] / 2);
      }

  printf("%lld\n", ans);
}

int main() {
  init();
  solve();
  return 0;
}
