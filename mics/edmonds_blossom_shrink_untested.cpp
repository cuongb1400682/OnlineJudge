#include <bits/stdc++.h>
using namespace std;

#define SZ 1000

void readf() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
        g[i].clear();
    for (int i = 1, u, v; i <= m; i++) {
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
}

int n, m, T[SZ], match[SZ], b[SZ];
vector<int> g[SZ];
queue<int> q;

int findPath(int start) {
    q = queue<int>();
    bitset<SZ> inQueue, vis;
    int p, newBase, r;

    memset(T, 0, sizeof(T));
    q.push(start); inQueue[start] = true;
    for (int u = 1; u <= n; u++) b[u] = u;

    while(!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            if (b[u] == b[v] || v == match[u]) continue;
            if (v == start || (match[v] != 0 && T[match[v]] != 0)) {
                vis.reset();
                for (p = u;;) {
                    p = b[p];
                    vis[p] = true;
                    if (p == start) break;
                    p = T[match[p]];
                }
                for (p = v;;) {
                    p = b[p];
                    if (vis[p]) break;
                    p = T[match[p]];
                }
                newBase = p;
                // reset trace
                vis.reset();
                for (p = u; b[p] != newBase;) {
                    r = match[p];
                    vis[b[p]] = true;
                    vis[b[r]] = true;
                    p = T[r];
                    if (b[p] != newBase) T[p] = r;
                }
                for (p = v; b[p] != newBase; ) {
                    r = match[p];
                    vis[b[p]] = true;
                    vis[b[r]] = true;
                    p = T[r];
                    if (b[p] != newBase) T[p] = r;
                }
                if (b[u] != newBase) T[u] = v;
                if (b[v] != newBase) T[v] = u;
                // shrink blossom
                for (p = 1; p <= n; p++)
                    if (vis[p]) b[p] = newBase;
                for (p = 1; p <= n; p++)
                    if (b[p] == newBase && !inQueue[p])
                        q.push(p);
            } else {
                T[v] = u;
                if (match[v] == 0)
                    return v;
                inQueue[match[v]] = true;
                q.push(match[v]);
            }
        }
    }
    return 0;
}

int enlarge(int u, int start) {
    int v, next;
    while (true) {
        v = T[u];
        next = match[v];
        match[v] = u;
        match[u] = v;
        if (v == start) break;
        u = next;
    }
}

void solve() {
    memset(match, 0, sizeof(match));
    for (int u = 1, v; u <= n; u++)
        if (match[u] == 0) {
            v = findPath(u);
            if (v != 0)
                enlarge(v, u);
        }
}

void print() {
    for (int u = 1; u <= n; u++) {
        if (match[u] > u) {
            printf("%d %d\n", u, match[u]);
        }
    }
}

int main(void) {
    freopen("input.txt", "rt", stdin);
    readf();
    solve();
    print();
    return 0;
}
