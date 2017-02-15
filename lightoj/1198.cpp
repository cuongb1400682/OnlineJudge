#include <bits/stdc++.h>
using namespace std;

#define SZ  512
#define INF 0x3f3f3f3f

int n, m, k, c[SZ][SZ], matchX[SZ], matchY[SZ], trace[SZ], fx[SZ], fy[SZ];
queue<int> q;

int team1[SZ], team2[SZ];

int getC(int x, int y) {
    return c[x][y] - fx[x] - fy[y];
}

void readf() {
    scanf("%d %d", &n, &m);
    k = max(n, m);
    for (int x = 1; x <= k; x++)
        for (int y = 1; y <= k; y++)
            c[x][y] = INF;
    for (int u, v, w; ~scanf("%d%d%d", &u, &v, &w); )
        c[u][v] = w;
}

int findPath(int x) {
    memset(trace, 0, sizeof(trace));
    q = queue<int>();
    q.push(x);
    while (!q.empty()) {
        x = q.front(); q.pop();
        for (int y = 1; y <= k; y++)
            if (getC(x, y) == 0 && trace[y] == 0) {
                trace[y] = x;
                if (matchY[y] == 0) return y;
                q.push(matchY[y]);
            }
    }
    return 0;
}

void change(int start) {
    bitset<SZ> visX, visY;
    int delta;

    visX[start] = true;
    for (int y = 1; y <= k; y++)
        if (trace[y] != 0) {
            visY[y] = true;
            visX[matchY[y]] = true;
        }

    delta = INF;
    for (int x = 1; x <= k; x++)
        for (int y = 1; visX[x] && y <= k; y++)
            if (delta > getC(x, y) && !visY[y])
                delta = getC(x, y);

    for (int t = 1; t <= k; t++) {
        if (visX[t]) fx[t] += delta;
        if (visY[t]) fy[t] -= delta;
    }
}

void enlarge(int y) {
    int next, x;
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
    memset(matchX, 0, sizeof(matchX));
    memset(matchY, 0, sizeof(matchY));
    memset(fx, 0, sizeof(fx));
    memset(fy, 0, sizeof(fy));
    for (int x = 1, y; x <= k; x++) {
        while ((y = findPath(x)) == 0)
            change(x);
        enlarge(y);
    }
}

void print() {
    int ans = 0;
    for (int i = 1; i <= k; i++) {
        int j = matchX[i];
        if (c[i][j] < INF)
            ans += 3 - c[i][j];
    }
    printf("%d\n", ans);
}

void readf_karate() {
    scanf("%d", &k);
    for (int i = 1; i <= k; i++)
        scanf("%d", &team1[i]);
    for (int i = 1; i <= k; i++)
        scanf("%d", &team2[i]);
    for (int i = 1; i <= k; i++)
        for (int j = 1; j <= k; j++)
            if (team1[i] > team2[j])
                c[i][j] = 1;
            else if (team1[i] == team2[j])
                c[i][j] = 2;
            else
                c[i][j] = 3;
}

int main(void) {
    freopen("input.txt", "rt", stdin);
    int nCase;
    scanf("%d", &nCase);
    for (int i = 1; i <= nCase; i++) {
        readf_karate();
        solve();
        printf("Case %d: ", i);
        print();
    }
    return 0;
}
