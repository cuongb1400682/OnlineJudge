#include <iostream>
#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;

#define SZ 100005

vector<ii> G[SZ];
ll n, len[SZ];
ll cnt[SZ], t[SZ];

void dfs(ll u) {
  cnt[u] = 1;
  for (vector<ii>::iterator it = G[u].begin(); it != G[u].end(); it++) {
    ll v = it->first;
    ll i = it->second;
    if (cnt[v] == 0) {
      dfs(v);
      cnt[u] += cnt[v];
      t[i] = cnt[v] * (n - cnt[v]);
    }
  }
}

int main() {
  ll u, v, w, q;
  
  scanf("%I64d", &n);
  for (ll i = 1; i <= n - 1; i++) {    
    scanf("%I64d%I64d%I64d", &u, &v, &w);
    G[u].push_back(ii(v, i));
    G[v].push_back(ii(u, i));
    len[i] = w;
  }

  dfs(1);

  long double factor = 6. / (n * (n - 1));
  long double S = 0.0;

  for (ll i = 1; i <= n - 1; i++)
    S += t[i] * len[i];

  scanf("%I64d", &q);

  while (q--) {
    cin >> u >> w;
    S -= (long double) t[u] * abs(w - len[u]);
    printf("%.10Lf\n", S * factor); // on Windows?
    len[u] = w;
  }
  return 0;
}

