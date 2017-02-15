/*
 * PROB: Codeforces Round #40 - 41D - Pawn
 * LANG: C++
 * INFO: DP (AC)
 */

#include <bits/stdc++.h>
using namespace std;

#define SZ 101

const int dx[] = { 1, 1 };
const int dy[] = { -1, 1 };

int n, m, k, f[SZ][SZ], a[SZ][SZ][1000];

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif
    scanf("%d%d%d\n", &n, &m, &k);

    memset(f, 0, sizeof f);
    memset(a, 0, sizeof a);

    for (char ln[1024], x = 1; scanf("%1024s", ln) != EOF; x++)
        for (char *p = ln, y = 1; *p; p++, y++)
            f[int(x)][int(y)] = int(*p - '0');

    for (int i = 1; i <= m; i++)
        a[n][i][f[n][i]] = -1;

    for (int i = n-1; i >= 1; i--) {
        for (int j = 1; j <= m; j++)
            for (int k = 0; k < 2; k++) {
                int x = i+dx[k], y = j+dy[k];
                if (x <= 0 || y <= 0 || x > n || y > m)
                    continue;
                for (int v = 0; v < 1000; v++)
                    if (a[x][y][v])
                        a[i][j][f[i][j] + v] = y;
            }
    }

    int ans = 0, pos = -1;
    for (int i = 1; i <= m; i++) {
        for (int v = 0; v < 1000; v += k+1)
            if (a[1][i][v] != 0 && ans <= v) {
                ans = v;
                pos = i;
            }
    }

    if (pos < 0) {
        printf("-1");
        return 0;
    }

    printf("%d\n", ans);
    string ret;
    for (int i = 1; i < n; ) {
        int v = f[i][pos];
        if (a[i][pos][ans] == pos-1)
            ret.push_back('R');
        else
            ret.push_back('L');
        pos = a[i][pos][ans];
        ans -= v;
        i++;
    }
    printf("%d\n", pos);
    reverse(ret.begin(), ret.end());
    printf("%s\n", ret.c_str());
    return 0;
}
