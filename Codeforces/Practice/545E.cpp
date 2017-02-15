#include <stdio.h>
#include <set>
#include <vector>

using namespace std;

#define SZ 300005
#define INF 1000000000000000000LL

typedef long long ll;

typedef pair<ll,ll> ii;

struct iii {
  ll first, second, third;
  iii(ll f=0,ll s=0,ll t=0):
    first(f),second(s),third(t) { }
};

ll n, m, parent[SZ];
vector<iii> G[SZ];
vector<iii> e;

bool operator<(iii a, iii b) {
  if (a.first!=b.first)
    return a.first<b.first;
  if(a.second!=b.second)
    return a.second<b.second;
  return a.third<b.third;
}

void solve(ll s) {
  static ll d[SZ];
  set<ii> q;
    
  for (ll u = 1; u <= n; u++) {
    d[u] = INF;
    parent[u] = 0;
  }
  
  d[s] = 0;
  parent[s] = s;
  q.insert(ii(0, s));

  while (!q.empty()) {
    ll u = q.begin()->second;
    q.erase(q.begin());

    for (ll i = 0; i < (ll) G[u].size(); i++) {
      ll v = G[u][i].first;
      ll w = G[u][i].second;
      ll idx = G[u][i].third;
      if (d[v] > d[u] + w) {
        if (d[v] != INF)
          q.erase(q.find(ii(d[v], v)));
        d[v] = d[u] + w;
        q.insert(ii(d[v], v));
        parent[v] = idx;
      } else if (d[v] == d[u] + w) {
        if (parent[v] != 0 && e[parent[v]].third > w) {
          parent[v] = idx;
        }
      }
    }
  }
}

int main() {
  ll u,v,w;
  scanf("%I64d %I64d", &n, &m);
  for (ll i = 1; i <= m; i++) {
    scanf("%I64d %I64d %I64d", &u, &v, &w);
    e.push_back(iii(u, v, w));
    G[u].push_back(iii(v, w, i - 1));
    G[v].push_back(iii(u, w, i - 1));
  }

  ll s;
  scanf("%I64d", &s);

  solve(s);

  ll ans = 0;
  for (ll u = 1; u <= n; u++)
    if (u != s) 
      ans += e[parent[u]].third;
  printf("%I64d\n", ans);
  for (ll u =1;u<=n;u++)
    if (u!=s)
      printf("%I64d ",parent[u]+1);
  printf("\n");
  
  return 0;
}

