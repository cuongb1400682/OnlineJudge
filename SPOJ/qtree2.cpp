#include <bits/stdc++.h>
using namespace std;

#define SZ 10005
#define INF 0x3f3f3f3f

#define debug(x) cerr << #x " = " << (x) << '\n'
#define arr(x, n) {cerr<<#x<<" = "<<"["<<(n)<<"]"<<"(";for(int i=0;i<(n);i++) cerr<<(x)[i]<<(i!=(n)-1?", ":")\n");}
#define iarr(x, m, n) {cerr<<#x":\n";for(int _=(m);_<=(n);_++) cerr<<_<<": "<<(x)[_]<<'\n';}
#define err(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef pair<int, int> ii;

struct query_t {
    int u, v, w;
    query_t(int u, int v, int w = -1) {
        this->u = u;
        this->v = v;
        this->w = w;
    }
};

vector<ii> adj[SZ], edge;
int base[SZ], parent[SZ], weight[SZ], lable[SZ], delable[SZ], depth[SZ], n, st[4 * SZ];
vector<query_t> vQuery;

void read_tree() {
    int u, v, w;
    scanf("%d", &n);
    edge.clear();
    for (int u = 1; u <= n; u++)
        adj[u].clear();
    edge.push_back(ii(0, 0));
    for (int i = 1; i <= n - 1; i++) {
        scanf("%d %d %d", &u, &v, &w);
        adj[u].push_back(ii(v, w));
        adj[v].push_back(ii(u, w));
        edge.push_back(ii(u, v));
    }
    
    char Q[22];
    vQuery.clear();    
    while (true) {
        scanf("%s", Q);
        if (strcmp(Q, "DONE") == 0)
            break;
        else if (strcmp(Q, "KTH") == 0) {
            scanf("%d %d %d", &u, &v, &w);
            vQuery.push_back(query_t(u, v, w));
        } else if (strcmp(Q, "DIST") == 0) {
            scanf("%d %d", &u, &v);
            vQuery.push_back(query_t(u, v));
        } 
    }
}

int dfs(int u) {
    int ans = 1, max_sum = -INF, heaviest = -1, sum;
    for (int i = 0, v, w; i < adj[u].size(); i++) {
        v = adj[u][i].first;
        w = adj[u][i].second;
        if (parent[v] == -1) {
            parent[v] = u;
            weight[v] = w;
            sum = dfs(v);
            if (max_sum <= sum) {
                heaviest = v;
                max_sum = sum;
            }
            ans += sum;
        }
    }
    base[u] = heaviest;
    return ans;
}

void hld(int u, int base_chain, int& cnt) {
    if (u == -1)
        return;
    int heaviest = base[u];
    base[u] = base_chain;
    lable[u] = ++cnt;
    delable[lable[u]] = u;
    hld(heaviest, base_chain, cnt);    
    depth[u] = max(depth[u], depth[heaviest] + 1);
    for (int i = 0, v; i < adj[u].size(); i++) {
        v = adj[u][i].first;
        if (parent[u] != v && v != heaviest) {
            hld(v, v, cnt);
            depth[u] = max(depth[u], depth[v] + 1);
        }
    }
}

void update(int p, int L, int R, int u, int value) {
    if (L == R) {
        st[p] = value;
        return;
    }
    if (u <= (L + R) / 2)
        update(2 * p, L, (L + R) / 2, u, value);
    else
        update(2 * p + 1, (L + R) / 2 + 1, R, u, value);
    st[p] = st[2 * p] + st[2 * p + 1];
}

int query(int p, int L, int R, int u, int v) {
    if (v < L || R < u)
        return 0;
    if (u <= L && R <= v)
        return st[p];
    return query(2 * p, L, (L + R) / 2, u, v) + 
           query(2 * p + 1, (L + R) / 2 + 1, R, u, v);
}

int lca(int u, int v) {
    for (; u != -1; u = parent[base[u]])
        for (int i = v; i != -1; i = parent[base[i]])
            if (base[u] == base[i])
                return (depth[u] > depth[i] ? u : i);
    return -1;
}

void build_tree() {
    for (int u = 1; u <= n; u++) {
        parent[u] = -1;
        base[u] = -1;
        depth[u] = 1;
        lable[u] = -1;
        weight[u] = 0;
    }
    parent[1] = 1;
    dfs(1);    
    parent[1] = -1;
    int cnt = 0;
    hld(1, 1, cnt);
    for (int u = 0; u <= 4 * n; u++)
        st[u] = 0;
    for (int u = 2; u <= n; u++)
        update(1, 1, n, lable[u], weight[u]);
}

int dist(int u, int v) {
    int x = lca(u, v);
    int ans = 0;
    
    for (; u != x; u = parent[base[u]]) {
        if (base[u] == base[x] && u != x) {
            ans += query(1, 1, n, lable[x] + 1, lable[u]);
            break;
        } else {
            ans += query(1, 1, n, lable[base[u]], lable[u]);
        }
    }
    
    for (; v != x; v = parent[base[v]]) {
        if (base[v] == base[x] && v != x) {
            ans += query(1, 1, n, lable[x] + 1, lable[v]);
            break;
        } else {
            ans += query(1, 1, n, lable[base[v]], lable[v]);
        }
    }    
    
    return ans;
}

int length(int u, int x) {    
    int ans = 0;
    for (; ; u = parent[base[u]]) {
        if (base[u] == base[x]) {
            ans += lable[u] - lable[x] + 1;
            break;            
        } else {
            ans += lable[u] - lable[base[u]] + 1;
        }
    }
    return ans;
}

int kth(int u, int v, int k) {
    int x = lca(u, v), d, len_ux, len_vx;
    len_ux = length(u, x);
    len_vx = length(v, x);
    if (len_ux >= k) {
        for (; ; u = parent[base[u]]) {
            if (k == 1)
                return u;
            if (base[u] == base[x])
                return delable[lable[u] - k + 1];
            else {
                d = lable[u] - lable[base[u]] + 1;
                if (k <= d)
                    return delable[lable[u] - k + 1];
                k -= d;
            }
        }
    } else {
        k = len_vx + len_ux - k ;
        for (; ; v = parent[base[v]]) {
            if (k == 1)
                return v;
            if (base[v] == base[x])
                return delable[lable[v] - k + 1];
            else {
                d = lable[v] - lable[base[v]] + 1;
                if (k <= d)
                    return delable[lable[v] - k + 1];
                k -= d;
            }
        }                
    }
    return -1;
}

int main() {
    freopen("qtree2.txt", "r", stdin);
    int T, u, v, w;
    scanf("%d", &T);
    while (T--) {  
        read_tree();
        build_tree();
        for (vector<query_t>::iterator it = vQuery.begin(); it != vQuery.end(); it++) {
            if (it->w == -1) { 
                printf("%d\n", dist(it->u, it->v));
            } else {
                printf("%d\n", kth(it->u, it->v, it->w));
            }
        }
        putchar('\n');
    }
    return 0;
}

/*
1

17
1 2 9
1 3 10
2 8 5
2 9 3
3 4 8
3 6 15
3 7 4
6 15 7
6 14 6
7 11 3
7 10 9
8 17 2
8 16 1
10 13 3
11 12 1
17 5 1
CHANGE 1 2
QUERY 9 1
DONE
*/
