#include <bits/stdc++.h>
using namespace std;

#define SZ 64
#define INF 0x3f3f3f3f

int k, c[SZ][SZ], fx[SZ], fy[SZ], d[SZ], trace[SZ], matchX[SZ], matchY[SZ];
queue<int> q;

int maxC;

void readf() {
    scanf("%d", &k);
    maxC = -INF;
    for (int i = 1; i <= k; i++)
        for (int j = 1; j <= k; j++) {
            scanf("%d", &c[i][j]);
            maxC = max(maxC, c[i][j]);
        }
    for (int i = 1; i <= k; i++)
        for (int j = 1; j <= k; j++)
            if (c[i][j] < INF) c[i][j] = maxC - c[i][j];
}

int getC(int x, int y) {
    return c[x][y] - fx[x] - fy[y];
}

int findPath(int x) {
    q = queue<int>();
    q.push(x);
    memset(trace, 0, sizeof(trace));
    for (int y = 1; y <= k; y++)
        d[y] = getC(x, y);
    while (!q.empty()) {
        x = q.front(); q.pop();
        for (int y = 1; y <= k; y++) {
            int w = getC(x, y);
            if (w == 0 && trace[y] == 0) {
                trace[y] = x;
                if (matchY[y] == 0) return y;
                q.push(matchY[y]);
            }
            if (d[y] > w) d[y] = w;
        }
    }
    return 0;
}

void change(int x) {
    int delta = INF;

    for (int y = 1; y <= k; y++)
        if (trace[y] == 0 && d[y] < delta)
            delta = d[y];


    fx[x] += delta;

    for (int y = 1; y <= k; y++) {
        x = matchY[y];
        if (trace[y] != 0) {
            fx[x] += delta;
            fy[y] -= delta;
        } else d[y] -= delta;
    }
}

void enlarge(int y) {
    int x, next;
    while (true) {
        x = trace[y];
        next = matchX[x];
        matchX[x] = y;
        matchY[y] = x;
        if (next == 0) break;
        y = next;
    }
}

void solve() {
    memset(fx, 0, sizeof(fx));
    memset(fy, 0, sizeof(fy));
    memset(matchX, 0, sizeof(matchX));
    memset(matchY, 0, sizeof(matchY));
    for (int x = 1, y; x <= k; x++) {
        while ((y = findPath(x)) == 0)
            change(x);
        enlarge(y);
    }
}

void print() {
    static int testNo = 1;
    int ans = 0;
    printf("Case %d: ", testNo++);
    for (int y = 1, x; y <= k; y++) {
        x = matchY[y];
        if (c[x][y] < INF) {
            ans += maxC - c[x][y];
        }
    }
    printf("%d\n", ans);
}

int main(void) {
    freopen("input.txt", "rt", stdin);

    int nCase;
    scanf("%d", &nCase);
    while (nCase--) {
        readf();
        solve();
        print();
    }
    return 0;
}

