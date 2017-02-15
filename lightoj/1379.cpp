#include <bits/stdc++.h>
using namespace std;

#define SZ 10005
#define INF 0x3f3f3f3f

#define dbg(x) cerr << "[" #x " = " << x << "]" << endl
template<class T>
void __dba(const T* a, int n) {
    cerr << "[";
    for (int i = 0; i < n; i++)
	cerr << (i > 0 ? ", " : "" ) << a[i];
    cerr << "]" << endl;
}
#define dba(a, n) { cerr << #a " = "; __dba(a, n); }

typedef pair<int, int> ii;

vector<ii> g[SZ], g_rev[SZ];
int ds[SZ], dt[SZ], zs[SZ], zt[SZ], t, s, n, m, p;

void readf() {
    scanf("%d%d%d%d%d", &n, &m, &s, &t, &p);
    for (int i = 1; i <= n; i++)
	g[i].clear(), g_rev[i].clear();
    for (int i = 1, u, v, w; i <= m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        g[u].push_back(ii(w, v));
	g_rev[v].push_back(ii(w, u));
    }
}

void dijkstra(int *d, int *z, int n, int s, const vector<ii> *g) {
    priority_queue<ii, vector<ii>, greater<ii> > q;
    for (int u = 1; u <= n; u++) {
	d[u] = INF;
	z[u] = 0;
    }
    d[s] = 0;
    q.push(ii(0, s));
    while (!q.empty()) {
	int u = q.top().second;
	int w = q.top().first;
	q.pop();
	if (w != d[u]) continue;
	for (int i = 0, v; i < (int)g[u].size(); i++) {
	    v = g[u][i].second;
	    if (d[v] > d[u] + g[u][i].first) {
		d[v] = d[u] + g[u][i].first;
		z[v] = max(g[u][i].first, z[u]);
		q.push(ii(d[v], v));
	    }
	}
    }
}

void solve() {
    dijkstra(ds, zs, n, s, g);
    dijkstra(dt, zt, n, t, g_rev);

    // dba(zs+1, n);
    // dba(zt+1, n);

    int ans = -1;
    for (int u = 1; u <= n; u++) {
	for (int i = 0, v; i < (int)g[u].size(); i++) {
	    v = g[u][i].second;
	    if (ds[u] + g[u][i].first + dt[v] <= p) 
		ans = max(max(ans, g[u][i].first), max(zs[u], zt[v]));
	}
    }

    static int no = 1;
    printf("Case %d: %d\n", no++, ans);
}

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
#endif
    int nCase;
    scanf("%d", &nCase);
    while (nCase--) {
        readf();
        solve();
    }
    return 0;
}

