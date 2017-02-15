#include <bits/stdc++.h>
using namespace std;

#define SZ 10005
#define INF 0x3f3f3f3f

#define debug(x) cerr << #x " = " << (x) << '\n'
#define arr(x, n) {cerr<<#x" = ["<<(n)<<"](";for(int _=0;_<(n);_++) cerr<<(x)[_]<<(_!=(n)-1?",":")\n");}
#define iarr(x, m, n) {cerr<<#x":\n";for(int _=(m);_<=(n);_++) cerr<<_<<": "<<(x)[_]<<'\n';}
#define err(...) fprintf(stderr, __VA_ARGS__)

#define read(x) scanf("%d", &x)
#define read_str(x) scanf("%s", x);

typedef long long ll;
typedef pair<int, int> ii;

int st[4 * SZ], n, base[SZ], lable[SZ], parent[SZ], depth[SZ], weight[SZ];
vector<ii> adj[SZ], edge;

// SEGMENT TREE's METHODs
void init(int p, int L, int R) {
    st[p] = -INF;
    if (L >= R)
        return;
    init(2*p, L, (L+R)/2);
    init(2*p+1,(L+R)/2+1, R);  
}

void update(int p, int L, int R, int u, int value) {
    if (L == R) {
        st[p] = value;
        return;
    }
    if (u <= (L+R)/2)
        update(2*p, L, (L+R)/2, u, value);
    else
        update(2*p+1, (L+R)/2+1, R, u, value);
    st[p] = max(st[2*p], st[2*p+1]);
}

int query(int p, int L, int R, int u, int v) {
    if (R < u || v < L)
        return -INF;
    if (u <= L && R <= v)
        return st[p];
    return max(query(2*p, L, (L+R)/2, u, v),
               query(2*p+1, (L+R)/2+1, R, u, v));
}

// METHODs for creating the tree
void read_tree() {
    int u, v, w;
    read(n);
    for (int u = 1; u <= n; u++)
        adj[u].clear();
    edge.clear();
    for (int i = 1; i < n; i++) {
        read(u); read(v); read(w);
        edge.push_back(ii(u, v));
        adj[u].push_back(ii(v, w));
        adj[v].push_back(ii(u, w));
    }
}

int dfs(int u) {
    int ans = 1, h_weight, heaviest = -1;
    h_weight = -INF;
    for (int i = 0, v, w, sum; i < adj[u].size(); i++) {
        v = adj[u][i].first;
        w = adj[u][i].second;
        if (parent[v] == -1) {
            parent[v] = u;
            weight[v] = w;
            sum = dfs(v);
            if (h_weight <= sum) {
                h_weight = sum;
                heaviest = v;
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
    hld(heaviest, base_chain, cnt);
    depth[u] = max(depth[u], depth[heaviest] + 1);
    for (int i = 0, v, w; i < adj[u].size(); i++) {
        v = adj[u][i].first;
        w = adj[u][i].second;        
        if (heaviest != v && v != parent[u]) {
            hld(v, v, cnt);
            depth[u] = max(depth[u], depth[v] + 1);
        }
    }
}

int lca(int u, int v) {
    while (u != -1) {
        for (int i = v; i != -1; i = parent[base[i]]) 
            if (base[u] == base[i])
                return (depth[i] > depth[u] ? i : u);
        u = parent[base[u]];
    }
    return -1;
}

void build_tree() {
    for (int i = 1; i <= n; i++) {
        parent[i] = -1;
        base[i] = -1;
        depth[i] = 1;
        lable[i] = i;
        weight[i] = 0;
    }
    
    parent[1] = 1;
    dfs(1);
    parent[1] = -1;
    
    int cnt = 0;
    hld(1, 1, cnt);
    
    init(1, 1, n);
    for (int i = 2; i <= n; i++)
        update(1, 1, n, lable[i], weight[i]);
}

// apply things above
int do_query(int a, int b) {
    int ans = -INF;
    int x = lca(a, b);
    
    for (int u = a; u != x; u = parent[base[u]]) {
        if (base[x] == base[u] && x != u) {
            ans = max(ans, query(1, 1, n, lable[x] + 1, lable[u]));
            break;
        } else {
            ans = max(ans, query(1, 1, n, lable[base[u]], lable[u]));            
        }
    }
    
    for (int u = b; u != x; u = parent[base[u]]) {
        if (base[x] == base[u] && x != u) {
            ans = max(ans, query(1, 1, n, lable[x] + 1, lable[u]));   
            break;         
        } else {
            ans = max(ans, query(1, 1, n, lable[base[u]], lable[u]));            
        }
    }

    return ans;
}

void do_change(int i, int ti) {
    i--;
    int& u = edge[i].first;
    int& v = edge[i].second;
    if (v == parent[u])
        swap(u, v);
    update(1, 1, n, lable[v], ti);
}

int main() {
    char Q[56];
    int u, v, T;
    read(T);
    while (T--) {
        read_tree();
        build_tree();
        while (true) {
            read_str(Q);
            if (!strcmp(Q, "DONE"))
                break;
            read(u); read(v);
            if (!strcmp(Q, "QUERY")) {
                printf("%d\n", do_query(u, v));
            } else {
                do_change(u, v);
            }
        }
        if (T) putchar('\n');
    }
    return 0;
}


