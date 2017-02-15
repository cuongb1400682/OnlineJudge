#include <iostream>
#include <vector>
#include <set>

using namespace std;

#define SZ 512
#define INF 1000000000

typedef long long ll;

ll d[SZ][SZ], a[SZ][SZ], n, x[SZ];

void init() {
  cin >> n;
  for (ll u = 1; u <= n; u++)
    for (ll v = 1; v <= n; v++)
      cin >> a[u][v];
  for (ll i = 1; i <= n; i++)
    cin >> x[i];
}

void solve() {
  ll ans[SZ] = {0};
  for (ll i = 1; i <= n; i++)
    for (ll j = 1; j <= n; j++)
      d[i][j] = a[x[i]][x[j]];

  for (ll k = n; k >= 1; k--) {
    for (ll i = 1; i <= n; i++)
      for (ll j = 1; j <= n; j++)
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    
    for (ll i = k; i <= n; i++)
      for (ll j = k; j <= n; j++) {
        ans[k] += d[i][j];
      }
  }

  for (ll i = 1; i <= n; i++)
    cout << ans[i] << " ";
  cout << "\n";
}

int main() {
  init();
  solve();
  return 0;
}
