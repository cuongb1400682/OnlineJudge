#include <stdio.h>
#include <vector>
#include <set>
#include <stack>
#include <map>

using namespace std;

#define SZ 100005
#define MOD 1000000007

typedef long long ll;
typedef pair<ll, ll> ii;

set<ll> G[SZ];
ll cost[SZ];
ll n, m;
vector<map<ll, ll> > bunch;
map<ii, ll> dp;

ll lab[SZ], low[SZ], label;
stack<ll> stk;
bool on_stk[SZ], vis[SZ];

void init() {
  ll u, v;
  scanf("%lld", &n);
  for (ll i = 1; i <= n; i++)
    scanf("%lld", &cost[i]);
  scanf("%lld", &m);
  for (ll i = 0; i < m; i++) {
    scanf("%lld %lld", &u, &v);
    G[u].insert(v);
  }
}

void tarjan(ll u) {
  lab[u] = low[u] = ++label;
  stk.push(u); on_stk[u] = true;
  vis[u] = true;
  
  for (set<ll>::iterator it = G[u].begin(); it != G[u].end(); it++) {
    ll v = *it;
    if (lab[v] == 0) {
      tarjan(v);
      low[u] = min(low[u], low[v]);
    } else if (on_stk[v]) {
      low[u] = min(low[u], lab[v]);
    }
  }
  
  if (lab[u] == low[u]) {
    bunch.push_back(map<ll, ll>());
    map<ll, ll> &cc = bunch.back();
    while (u != stk.top()) {
      cc[cost[stk.top()]]++;
      on_stk[stk.top()] = false;
      stk.pop(); 
    }
    cc[cost[stk.top()]]++;
    on_stk[stk.top()] = false;
    stk.pop();
  }
}

ll calc(ll i, ll price) {
  if (i <= 0)
    return bunch[0][price] % MOD;
  if (dp.count(ii(i, price)) > 0)
    return dp[ii(i, price)];
  
  ll ans = 0, tmp;
  map<ll, ll>::iterator it;
  for (it = bunch[i].begin(); it != bunch[i].end(); it++)
    if (price >= it->first) {
      tmp = ((calc(i - 1, price - it->first) % MOD) * (it->second % MOD)) % MOD;
      ans = (ans + tmp) % MOD;      
    }
  
  dp[ii(i, price)] = ans;
  return ans;
}

void solve() {
  for (ll u = 1; u <= n; u++)
    if (!vis[u]) {
      tarjan(u);
    }
    
  ll min_cost = 0, n_way = 1;
  for (ll i = 0; i < bunch.size(); i++) {
    min_cost += bunch[i].begin()->first;
    n_way *= bunch[i].begin()->second;
  }
  
  printf("%lld %lld\n", min_cost, n_way); 
  
}

int main() {
  init(); 
  solve();
  return 0;
}


