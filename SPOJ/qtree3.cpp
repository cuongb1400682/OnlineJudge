#include <bits/stdc++.h>
using namespace std;

#define SZ 100001
#define INF 0x3f3f3f3f

#define debug(x) cerr << #x " = " << (x) << '\n'
#define arr(x, n) {cerr<<#x<<" = "<<"["<<(n)<<"]"<<"(";for(int i=0;i<(n);i++) cerr<<(x)[i]<<(i!=(n)-1?", ":")\n");}
#define iarr(x, m, n) {cerr<<#x":\n";for(int _=(m);_<=(n);_++) cerr<<_<<": "<<(x)[_]<<'\n';}
#define err(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef pair<int, int> ii;

int N, Q, parent[SZ], base[SZ], lable[SZ], depth[SZ], de_lable[SZ], st[4 * SZ];
vector<int> adj[SZ];

// determine parent, depth
int dfs(int u) {
    int ans = 1, cnt = 0, max_cnt = -INF, heaviest = -1;
    for (vector<int>::iterator it = adj[u].begin(); it != adj[u].end(); it++) {
        if (parent[u] != *it) {    
            parent[*it] = u;
            cnt = dfs(*it);
            depth[u] = max(depth[u], depth[*it] + 1);
            if (max_cnt < cnt) {
                max_cnt = cnt;
                heaviest = *it;
            }
            ans += cnt;
        }
    }
    base[u] = heaviest;
    return ans;
}

// determine base, lable
void hld(int u, int base_chain, int& cnt) {
    if (u == -1)
        return;
    int heaviest = base[u];
    base[u] = base_chain;
    lable[u] = ++cnt;
    de_lable[lable[u]] = u;
    hld(heaviest, base_chain, cnt);
    for (vector<int>::iterator it = adj[u].begin(); it != adj[u].end(); it++) 
        if (parent[u] != *it && *it != heaviest) 
            hld(*it, *it, cnt);
}

void inverse(int p, int L, int R, int u) {
    if (L == R) {
        if (st[p] == INF)
            st[p] = u;
        else
            st[p] = INF;
        return;
    }
    if (u <= (L + R) / 2)
        inverse(2 * p, L, (L + R) / 2, u);
    else
        inverse(2 * p + 1, (L + R) / 2 + 1, R, u);
    st[p] = min(st[2 * p], st[2 * p + 1]);
}

int query(int p, int L, int R, int u, int v) {
    if (v < L || R < u)
        return INF;
    if (u <= L && R <= v)
        return st[p];
    return min(query(2 * p, L, (L + R) / 2, u, v),
               query(2 * p + 1, (L + R) / 2 + 1, R, u, v));
}

int main() {
    freopen("qtree3.txt", "r", stdin);
    scanf("%d %d", &N, &Q);
    for (int u = 1; u <= N; u++) {
        adj[u].clear();
        base[u] = u;
        lable[u] = -1;
        parent[u] = -1;
        depth[u] = 1;
    }
    for (int i = 1, a, b; i <= N - 1; i++) {
        scanf("%d %d", &a, &b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1);
    int cnt = 0;
    hld(1, 1, cnt);
    for (int i = 1; i <= 4 * N; i++)
        st[i] = INF;    
    for (int i = 1, a, b; i <= Q; i++) {
        scanf("%d %d", &a, &b);
        if (a == 0) {
            inverse(1, 1, N, lable[b]);
        } else {
            int ans = INF, tmp;
            for (int u = b; u != -1; u = parent[base[u]]) {
                tmp = query(1, 1, N, lable[base[u]], lable[u]);
                ans = min(ans, tmp);
            }
            printf("%d\n", (ans == INF ? -1: de_lable[ans]));
        }
    }    
    return 0;
}


