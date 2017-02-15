/*
 * PROB: Codeforces - 500A. New Year Transportation
 * LANG: C++
 */

#include <cstdio>
#include <vector>
using namespace std;

#define REP(i, a, b) \
    for (int i = int(a); i <= int(b); i++)

vector<int> next;
int n, t;

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &t);
    next.assign(n + 1, 0);
    next[0] = -1;
    REP(i, 1, n - 1) {
        int nxt;
        scanf("%d", &nxt);
        next[i] = i + nxt;
    }
    bool ok = false;
    for (int u = 1; u > 0; u = next[u])
        if (u == t) {
            ok = true;
            break;
        }
    puts(ok ? "YES" : "NO");
    return 0;
}
