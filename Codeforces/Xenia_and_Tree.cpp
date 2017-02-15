#include <bits/stdc++.h>
using namespace std;

#define SZ 100005
#define INF 0x3f3f3f3f
#define RED 0
#define BLUE 1

#define debug(x) cerr << #x " = " << (x) << '\n'
#define arr(x, n) {cerr<<#x<<" = "<<"["<<(n)<<"]"<<"(";for(int i=0;i<(n);i++) cerr<<(x)[i]<<(i!=(n)-1?", ":"");cerr<<")\n";}
#define iarr(x, m, n) {cerr<<#x":\n";for(int _=(m);_<=(n);_++) cerr<<_<<": "<<(x)[_]<<'\n';}
#define err(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef pair<int, int> ii;

int parent[SZ], cnt[SZ], n, m, n_child, depth[SZ], next[SZ][100], color[SZ], root, d[SZ];
set<int> g[SZ];

int count_child(int u, int p) {
	cnt[u] = 1;
	for (set<int>::iterator it = g[u].begin(); it != g[u].end(); it++)
		if (*it != p)
			cnt[u] += count_child(*it, u);
	return cnt[u];
}

int find_cenroid(int u, int p) {
	for (set<int>::iterator it = g[u].begin(); it != g[u].end(); it++)
		if (*it != p && cnt[*it] > n_child / 2)
			return find_cenroid(*it, u);
	return u;
}

int decompose(int u) {
	n_child = count_child(u, u);
	int cen = find_cenroid(u, u);
	for (set<int>::iterator it = g[cen].begin(); it != g[cen].end(); it++) {
		g[*it].erase(cen);
		parent[decompose(*it)] = cen;
	}
	g[cen].clear();
	return cen;
}

void calc_depth(int u, int p) {
	for (set<int>::iterator it = g[u].begin(); it != g[u].end(); it++)
		if (*it != p) {
			parent[*it] = u;
			depth[*it] = depth[u] + 1;
			calc_depth(*it, u);
		}
}

int log2(int n) {
	int k = 0;
	for (int u = n; u > 0; u >>= 1)
		k++;
	return k;
}

void preprocess() {
	for (int u = 1; u <= n; u++) {
		depth[u] = 0;
		parent[u] = 0;
	}

	calc_depth(1, 1);
	memset(next, 0, sizeof(next));

	int k = log2(n);
	for (int i = 1; i <= n; i++)
		next[i][0] = parent[i];

	for (int j = 1; j <= k; j++)  // calc j first
		for (int i = 1; i <= n; i++)
			next[i][j] = next[next[i][j - 1]][j - 1];
}

int lca(int u, int v) {
	if (depth[u] < depth[v])
		swap(u, v);

	int k = log2(depth[u]) + 1;

	for (int i = k; i >= 0; i--) {
		if (next[u][i] != 0 && depth[next[u][i]] >= depth[v]) // check if next[u][i] != 0
			u = next[u][i];
	}
	
	if (u == v)
		return u;
	
	for (int i = k; i >= 0; i--) {
		int uu = next[u][i];
		int vv = next[v][i];
		if (uu != -1 && uu != vv) {
			u = uu;
			v = vv;
		}
	}

	return next[u][0];
}

int dist(int u, int v) {
	int y = lca(u, v);
	return depth[u] + depth[v] - 2 * depth[y];
}

void do_update(int u) { 
	if (color[u] == RED)
		return;
	color[u] = RED;
	d[u] = 0;
	for (int v = u; v != 0; v = parent[v])
		d[v] = min(d[v], dist(u, v));
}

int do_query(int u) {
	if (color[u] == RED)
		return 0;
	int ans = INF;
	for (int v = u; v != 0; v = parent[v]) {
		ans = min(ans, d[v] + dist(u, v));
	}
	return ans;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].insert(v);
        g[v].insert(u);
    }
	preprocess();
	memset(parent, 0, sizeof(parent));
	root = decompose(1);
	for (int u = 1; u <= n; u++) {
		color[u] = BLUE;
		d[u] = INF;
	}
	do_update(1);
	for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
		if (u == 2)
			printf("%d\n", do_query(v));
		else
			do_update(v);
	}
    return 0;
}
