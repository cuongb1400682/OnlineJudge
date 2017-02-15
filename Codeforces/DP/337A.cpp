/*
 * PROB: Codeforces Round #196 - Div.2 - A. Puzzles
 * LANG: C++
 */

#include <bits/stdc++.h>
using namespace std;

int f[50], n, m;
list<int> q;

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++)
        scanf("%d", &f[i]);
    sort(f, f+m, less<int>());
    int ans = f[n-1] - f[0];
    for (int i = n; i < m; i++)
        ans = min(ans, f[i] - f[i-n+1]);
    printf("%d\n", ans);
    return 0;
}

