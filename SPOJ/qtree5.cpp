#include <bits/stdc++.h>
using namespace std;

#define SZ 100005
#define INF 0x3f3f3f3f
#define BLACK 0
#define WHITE 1

#define debug(x) cerr << #x " = " << (x) << '\n'
#define arr(x, n) {cerr<<#x<<" = "<<"["<<(n)<<"]"<<"(";for(int i=0;i<(n);i++) cerr<<(x)[i]<<(i!=(n)-1?", ":"");cerr<<")\n";}
#define iarr(x, m, n) {cerr<<#x":\n";for(int _=(m);_<=(n);_++) cerr<<_<<": "<<(x)[_]<<'\n';}
#define err(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef pair<int, int> ii;

set<int> g[SZ];
int parent[SZ], n, m, size[SZ], n_child, color[SZ];
int depth[SZ], next[SZ][20];
int x[SZ][20];
map<int, int> h[SZ];

void calc_depth(int u, int p) {
	for (set<int>::iterator it = g[u].begin(); it != g[u].end(); it++) {
		if (*it != p) {
			depth[*it] = depth[u] + 1;
			next[*it][0] = u;
			calc_depth(*it, u);
		}
	}
}

void preprocess_lca() {
	memset(depth, 0, sizeof(depth));
	memset(next, 0, sizeof(next));
	calc_depth(1, 1);
	int k = log2(n);
	for (int j = 1; j <= k; j++)
		for (int i = 1; i <= n; i++)
			next[i][j] = next[next[i][j - 1]][j - 1];
}

int lca(int u, int v) {
	if (depth[u] < depth[v])
		swap(u, v);
	int k = log2(depth[u]);
	for (int i = k; i >= 0; i--) {
		if (next[u][i] != 0 && depth[next[u][i]] >= depth[v])
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

int dist_lca(int u, int v) {
	int y = lca(u, v);
	return depth[u] + depth[v] - 2 * depth[y];
}

int calc_size(int u, int p) {
	size[u] = 1;
	for (set<int>::iterator it = g[u].begin(); it != g[u].end(); it++)
		if (*it != p)
			size[u] += calc_size(*it, u);
	return size[u];
}

pair<int,int> find_cendroid(int u, int p) {
	for (set<int>::iterator it = g[u].begin(); it != g[u].end(); it++)
		if (*it != p && size[*it] > n_child / 2) {
			pair<int, int> tmp = find_cendroid(*it, u);
			return make_pair(tmp.first, tmp.second + 1);
		}
	return make_pair(u, 0);
}

pair<int, int> decompose(int u) {
	n_child = calc_size(u, u); // int n_child
	pair<int, int> ans = find_cendroid(u, u);
	int cen = ans.first;
	for (set<int>::iterator it = g[cen].begin(); it != g[cen].end(); it++) {
		g[*it].erase(cen);
		pair<int, int> tmp = decompose(*it);
		parent[tmp.first] = cen;
		x[tmp.first][0] = tmp.second + 1;
	}
	g[cen].clear(); 
	return ans;
}

void calc_x() {
	for (int u = 1; u <= n; u++) {
		int lv = 1;
		for (int p = parent[parent[u]]; p != 0; p = parent[p]) {
			x[u][lv] = dist_lca(u, p);
			lv++;
		}
	}
}

void do_update(int v) {
	if (color[v] == BLACK) {
		int lv = 0;
		h[v][0] = 1;
		for (int u = parent[v]; u != 0; u = parent[u]) {
			int dist = x[v][lv];
			h[u][dist]++;
			lv++;
		}
	} else {
		int lv = 0;
		for (int u = parent[v]; u != 0; u = parent[u]) {
			int tmp = x[v][lv];
			h[u][tmp]--;
			if (h[u][tmp] == 0)
				h[u].erase(tmp);
			lv++;
		}
		h[v].erase(0);
	}
	color[v] ^= 1;
}

int do_query(int v) {
	if (color[v] == WHITE)
		return 0;
	int lv = -1;
	int ans = INF;
	for (int p = v; p != 0; p = parent[p]) {
		int dist_p_v = (lv == -1 ? 0 : x[v][lv]);
		int min_dist = h[p].begin()->first;
		ans = min(ans, min_dist + dist_p_v);
		lv++;
	}
	return ans == INF ? -1 : ans;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		g[u].insert(v);
		g[v].insert(u);
	}

	for (int u = 1; u <= n; u++) {
		color[u] = BLACK;
		h[u][INF]++;
	}

	memset(parent, 0, sizeof(parent));
	preprocess_lca();
	decompose(1);	
	calc_x();

	scanf("%d", &m);
	for (int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		if (u == 0) {
			do_update(v);
		} else {
			printf("%d\n", do_query(v));
		}
	}
    return 0;
}
