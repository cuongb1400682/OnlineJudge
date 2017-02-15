/*
 * PROB: Codeforces Round #40 - 41D - Pawn
 * LANG: C++
 * INFO: brute-force (TLE)
 */

#include <bits/stdc++.h>
using namespace std;

#define SZ 101

const int dx[] = { -1, -1 };
const int dy[] = { -1, +1};

struct cell {
    int x, y, pea;
    set<cell>::iterator nxt;
    cell(int _x, int _y, int _pea) :
        x(_x), y(_y), pea(_pea), nxt() { }
};

int n, m, k, f[SZ][SZ];
set<cell> vis;

bool operator<(cell a, cell b) {
    if (a.x != b.x)
        return a.x < b.x;
    if (a.y != b.y)
        return a.y < b.y;
    return a.pea < b.pea;
}

set<cell>::iterator solve(int x, int y) {
    set<cell>::iterator ans = vis.end();
    int ans_pea = 0;
    queue<cell> q;
    cell s(x, y, f[x][y]);
    s.nxt = vis.end();
    vis.insert(s);
    q.push(s);
    while (!q.empty()) {
        cell u = q.front(); q.pop();
        if (u.x == 1 && u.pea % (k+1) == 0)
            if (ans_pea < u.pea) {
                ans_pea = u.pea;
                ans = vis.find(u);
            }
        for (int i = 0; i < 2; i++) {
            x = u.x+dx[i], y = u.y+dy[i];
            if (x <= 0 || y <= 0 || x > n || y > m)
                continue;
            cell v(x, y, u.pea+f[x][y]);
            if (!vis.count(v)) {
                v.nxt = vis.find(u);
                vis.insert(v);
                q.push(v);
            }
        }
    }
    return ans;
}

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif
    scanf("%d%d%d\n", &n, &m, &k);
    memset(f, 0, sizeof f);

    for (char ln[1024], x = 1; fgets(ln, sizeof ln, stdin) != NULL; x++)
        for (char *p = ln, y = 1; *p; p++, y++)
            f[int(x)][int(y)] = int(*p - '0');

    vis.clear();
    set<cell>::iterator ans = vis.end();
    for (int i = 1; i <= m; i++) {
        set<cell>::iterator it = solve(n, i);
        if (it != vis.end())
            if (ans == vis.end() || ans->pea < it->pea)
                ans = it;
    }

    if (ans == vis.end()) {
        printf("-1");
        return 0;
    }

    printf("%d\n", ans->pea);
    string ret;

    for (; ans->nxt != vis.end(); ans = ans->nxt) {
        if (ans->y == ans->nxt->y-1)
            ret.push_back('L');
        else
            ret.push_back('R');
    }

    reverse(ret.begin(), ret.end());
    printf("%d\n", ans->y);
    printf("%s\n", ret.c_str());

    return 0;
}
