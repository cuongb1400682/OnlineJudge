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

int n, a[SZ], pset[SZ], cnt[SZ];
char str[SZ];
vi g[1050];

int find_group(int u) {
    if (u == pset[u])
        return u;
    else
        return pset[u] = find_group(pset[u]);
}

void join(int u, int v) {
    int r = find_group(u);
    int s = find_group(v);
    if (r != s) pset[r] = s;
}

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) {
        scanf("%d", &a[i]);
        pset[i] = i;
    }
    REP(u, 1, n) {
        scanf("%300s", str);
        REP(v, 0, n - 1)
            if (str[v] == '1') join(u, v + 1);
    }
    REP(u, 1, n) {
        int r = find_group(u);
        g[r].push_back(a[u]);
    }
    REP(u, 1, n) sort(g[u].begin(), g[u].end());
    REP(u, 1, n) {
        int r = find_group(u);
        printf("%d%s", g[r][cnt[r]++], u == n ? "" : " ");
    }
    return 0;
}
