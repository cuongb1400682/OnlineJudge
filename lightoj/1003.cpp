#include <bits/stdc++.h>
using namespace std;

#define SZ 20005
#define INF 0x3f3f3f3f

#define debug(x) cerr << #x " = " << (x) << '\n'
#define arr(x, n) {cerr<<#x<<" = "<<"["<<(n)<<"]"<<"(";for(int i=0;i<(n);i++) cerr<<(x)[i]<<(i!=(n)-1?", ":")\n");}

#define BLACK 0
#define WHITE 1
#define BROWN 2

typedef long long ll;

map<string, int> h;
string drink_a, drink_b;
vector<int> g[SZ];
char color[SZ];
int m, T;

int get_id(string a) {
    if (h.count(a) == 0)
        h[a] = h.size();
    return h[a];
}

bool has_circle(int u) {
    color[u] = BROWN;
    for (int i = 0, v; i < g[u].size(); i++) {
        v = g[u][i];
        if (color[v] == BROWN || has_circle(v))
            return true;
    }
    color[u] = BLACK;
    return false;
}

int main() {
    freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin >> T;
    for (int no = 1; no <= T; no++) {
        cin >> m;
        h.clear();
        for (int i = 0; i < SZ; i++)
            g[i].clear();
        for (int i = 0, u, v; i < m; i++) {
            cin >> drink_a >> drink_b;
            u = get_id(drink_a);
            v = get_id(drink_b);
            g[u].push_back(v);
        }
        cout << "Case " << no << ": ";
        for (int i = 0; i < SZ; i++)
            color[i] = WHITE;
        bool ans = false;
        for (int i = 1; i <= h.size(); i++) {
            if (color[i] == WHITE)
                if (has_circle(i)) {
                    ans = true;
                    break;
                }                 
        }
        cout << (ans ? "No" : "Yes") << '\n';
    }
    return 0;
}


