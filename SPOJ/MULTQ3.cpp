#include <stdio.h>

#define SZ 100001

struct Node {
	int cnt[3];
	int lazy;
	Node() {
		lazy = cnt[0] = cnt[1] = cnt[2] = 0;
	}
	void roll(int n = 1) {
		while (n--) {
			int t = cnt[0];
			cnt[0] = cnt[1];
			cnt[1] = cnt[2];
			cnt[2] = t;
		}
	}
};

Node st[4 * SZ];
int n, m, t;

Node mix(Node a, Node b) {
	Node ans;
	ans.cnt[0] = a.cnt[0] + b.cnt[0];
	ans.cnt[1] = a.cnt[1] + b.cnt[1];
	ans.cnt[2] = a.cnt[2] + b.cnt[2];
	return ans;
}

void init(int p, int L, int R) {
	if (L == R) {
		st[p].cnt[0] = 1;
		return;
	}
	int mid = (L + R) >> 1;
	init(2 * p, L, mid);
	init(2 * p + 1, mid + 1, R);
	st[p] = mix(st[2 * p], st[2 * p + 1]);
}

void propagate(int p) {
	int& lazy = st[p].lazy;
	st[2 * p].lazy += lazy;
	st[2 * p + 1].lazy += lazy;
	for (lazy %= 3; lazy > 0; lazy--) {
		st[2 * p].roll();
		st[2 * p + 1].roll();
	}
}

void increase(int p, int L, int R, int u, int v) {
	if (v < L || R < u)
		return;
	if (u <= L && R <= v) {
		st[p].roll();
		st[p].lazy++;
		return;
	}
	propagate(p);
	int mid = (L + R) >> 1;
	increase(2 * p, L, mid, u, v);
	increase(2 * p + 1, mid + 1, R, u, v);
	st[p] = mix(st[2 * p], st[2 * p + 1]);
}

int get_cnt(int p, int L, int R, int u, int v) {
	if (v < L || R < u)
		return 0;
	if (u <= L && R <= v)
		return st[p].cnt[0];
	propagate(p);
	int mid = (L + R) >> 1;
	return get_cnt(2 * p, L, mid, u, v) + 
			get_cnt(2 * p + 1, mid + 1, R, u, v);	
}

int main() {
	scanf("%d %d", &n, &m);
	init(1, 0, n - 1);
	for (int i = 1; i <= m; i++) {
		int u, v, t;
		scanf("%d %d %d", &t, &u, &v);
		if (t == 0)
			increase(1, 0, n - 1, u, v);
		else
			printf("%d\n", get_cnt(1, 0, n - 1, u, v));
	}
	return 0;
}

