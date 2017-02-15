#include <bits/stdc++.h>
using namespace std;

#define debug(x) cerr << #x " = " << (x) << '\n'
#define arr(x, n) {cerr<<#x<<" = "<<"["<<(n)<<"]"<<"(";for(ll _=0;_<(n);_++) cerr<<(x)[_]<<(_!=(n)-1?", ":")\n");}
#define iarr(x, m, n) {cerr<<#x":\n";for(ll _=(m);_<=(n);_++) cerr<<_<<": "<<(x)[_]<<'\n';}
#define err(...) fprintf(stderr, __VA_ARGS__)

#define SZ 30005

typedef long long ll;

int base[SZ], parent[SZ], depth[SZ], n, t, a[SZ], st[4 * SZ], lable[SZ], de_lable[SZ];
set<int> g[SZ];

int dfs(int u, int p) {
	int ans = 1, max_w = 0;
	parent[u] = p;
	base[u] = -1;
	depth[u] = 1;
	for (set<int>::iterator it = g[u].begin(); it != g[u].end(); it++) {
		if (*it != p) {
			int tmp = dfs(*it, u);
			if (max_w <= tmp) {
				base[u] = *it;
				max_w = tmp;
			}
			ans += tmp;
			depth[u] = max(depth[u], depth[*it] + 1);
		}
	}
	return ans;
}


int hld_cnt;
void hld(int u, int base_chain) {
	if (u == -1) return;
	int heaviest = base[u];
	base[u] = base_chain;
	lable[u] = hld_cnt++;
	de_lable[lable[u]] = u;
	hld(heaviest, base_chain);
	for (set<int>::iterator it = g[u].begin(); it != g[u].end(); it++) {
		if (*it != parent[u]  && *it != heaviest) {
			hld(*it, *it);
		}
	}
}

void init(int p, int L, int R) {
	st[p] = 0;
	if (L == R) {
		st[p] = a[de_lable[L]];
		return;
	}
	int mid = (L + R) >> 1;
	init(2 * p, L, mid);
	init(2 * p + 1, mid + 1, R);
	st[p] = st[2 * p] + st[2 * p + 1];
}

int get_sum(int p, int L, int R, int u, int v) {
	if (v < L || R < u)
		return 0;
	if (u <= L && R <= v)
		return st[p];
	int mid = (L + R) >> 1;
	return get_sum(2 * p, L, mid, u, v) +
		get_sum(2 * p + 1, mid + 1, R, u, v);
}

void update(int p, int L, int R, int u, int val) {
	if (L == R) {
		st[p] = val;
		return;
	}
	int mid = (L + R) >> 1;
	if (u <= mid)
		update(2 * p, L, mid, u, val);
	else
		update(2 * p + 1, mid + 1, R, u, val);
	st[p] = st[2 * p] + st[2 * p + 1];
}

int lca(int u, int _v) {
	while (u != -1) {
		for (int v = _v; v != -1; v = parent[base[v]])
			if (base[u] == base[v])
				return depth[u] > depth[v] ? u : v;
		u = parent[base[u]];
	}
	return -1;
}

int do_query(int u, int v) {
	int ans = 0;
	int z = lca(u, v);
	
	for (int p = v; p != -1; p = parent[base[p]]) {
		if (base[p] == base[z]) {
			ans += get_sum(1, 0, n - 1, lable[z], lable[p]);
			break;
		} else {
			ans += get_sum(1, 0, n - 1, lable[base[p]], lable[p]);
		}
	}

	for (int p = u; p != -1; p = parent[base[p]]) {
		if (base[p] == base[z]) {
			ans += get_sum(1, 0, n - 1, lable[z], lable[p]);
			break;
		} else {
			ans += get_sum(1, 0, n - 1, lable[base[p]], lable[p]);
		}
	}
	
	return ans - get_sum(1, 0, n - 1, lable[z], lable[z]);
}

void do_update(int u, int v) {
	update(1, 0, n - 1, lable[u], v);
}

int main() {
	scanf("%d", &t);
	for (int no = 1, q; no <= t; no++) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d", &a[i]);
			g[i].clear();
		}
		for (int i = 0, u, v; i < n - 1; i++) {
			scanf("%d %d", &u, &v);
			g[u].insert(v);
			g[v].insert(u);
		}
		dfs(0, -1);
		hld_cnt = 0;
		hld(0, 0);
		
		init(1, 0, n - 1);

		scanf("%d", &q);
		printf("Case %d:\n", no);
		for (int i = 1, type, u, v; i <= q; i++) {
			scanf("%d %d %d", &type, &u, &v);
			if (type == 0)
				printf("%d\n", do_query(u, v));
			else
				do_update(u, v);
		}
	}
	return 0;
}
