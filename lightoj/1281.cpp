#include <bits/stdc++.h>
using namespace std;

#define SZ 10005
#define INF 0x3f3f3f3f

typedef long long ll;

struct Edge {
    ll v, w;
    bool is_proposed;
    Edge(ll v = 0, ll w = 0, bool is_proposed = false) :
        v(v), w(w), is_proposed(is_proposed) {}
};

vector<Edge> g[SZ];
ll n, m, k, d;

void init() {
    scanf("%lld%lld%lld%lld", &n, &m, &k, &d);
    for (ll u = 0; u <= n; u++) g[u] = vector<Edge>();
    for (ll i = 1, u, v, w; i <= m; i++) {
        scanf("%lld%lld%lld", &u, &v, &w);
        g[u].push_back(Edge(v, w, false));
    }
    for (ll i = 1, u, v, w; i <= k; i++) {
        scanf("%lld%lld%lld", &u, &v, &w);
        g[u].push_back(Edge(v, w, true));
    }
}

struct Item {
    ll w, v, phi;
    Item(ll w = 0, ll v = 0, ll phi = 0) :
        w(w), v(v), phi(phi) {}
};

bool operator<(const Item& a, const Item& b) {
    return a.w > b.w;
}

ll solve() {
    static ll dist[SZ][11];
    priority_queue<Item, vector<Item> > q;

    memset(dist, 0x3f, sizeof(dist));
    memset(dist[0], 0, sizeof(dist[0]));
    q.push(Item(0, 0, 0));

    while (!q.empty()) {
        int u = q.top().v;
        int w = q.top().w;
        int phi = q.top().phi;
        q.pop();
        if (w != dist[u][phi]) continue;
        if (u == n - 1) return dist[u][phi];
        for (int i = 0, v; i < (int) g[u].size(); i++) {
            v = g[u][i].v;
            if (g[u][i].is_proposed) {
                if (phi < d && dist[v][phi + 1] > dist[u][phi] + g[u][i].w) {
                    dist[v][phi + 1] = dist[u][phi] + g[u][i].w;
                    q.push(Item(dist[v][phi + 1], v, phi + 1));
                }
            } else {
                if (phi <= d && dist[v][phi] > dist[u][phi] + g[u][i].w) {
                    dist[v][phi] = dist[u][phi] + g[u][i].w;
                    q.push(Item(dist[v][phi], v, phi));
                }
            }
        }
    }

    return -1;
}

int main(void) {
    freopen("input.txt", "rt", stdin);
    ll nCase;
    scanf("%lld", &nCase);
    for (ll no = 1; no <= nCase; no++) {
        init();
        printf("Case %lld: ", no);
        ll ans = solve();
        if (ans == -1)
            printf("Impossible\n");
        else
            printf("%lld\n", ans);
    }
    return 0;
}
