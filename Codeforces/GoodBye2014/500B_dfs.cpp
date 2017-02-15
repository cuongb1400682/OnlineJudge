/*
 * PROB: Codeforces - B. New Year Permutation
 * LANG: C++
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<int> vi;

#define SZ 301
#define REP(i, a, b) \
    for (int i = int(a); i <= int(b); i++)

int n, a[SZ];
bool adj[SZ][SZ], visited[SZ];
char buf[1024];
vi p;

void dfs(int u) {
    visited[u] = true;
    p.push_back(u);
    REP(v, 1, n) if (!visited[v] && adj[u][v])
        dfs(v);
}

bool compare(int i, int k) {
    return a[i] < a[k];
}

void bsort() {
    int n = p.size() - 1;
    REP(i, 0, n - 1)
        REP(k, i + 1, n)
            if (a[p[i]] > a[p[k]]) {
                int t = a[p[i]];
                a[p[i]] = a[p[k]];
                a[p[k]] = t;
            }
}

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d", &a[i]);
    scanf("\n");
    memset(adj, false, sizeof adj);

    REP(u, 1, n) {
        fgets(buf, sizeof buf, stdin);
        REP(v, 0, n - 1)
            adj[u][v + 1] = (buf[v] == '1');
    }

    memset(visited, false, sizeof visited);
    REP(u, 1, n) if (!visited[u]) {
        p.clear();
        dfs(u);
        sort(p.begin(), p.end());
        bsort();
    }

    printf("%d", a[1]);
    REP(i, 2, n) printf(" %d", a[i]);
    return 0;
}
