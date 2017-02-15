#include <stdio.h>
#include <algorithm>
#include <map>

using namespace std;

#define SZ 100005
#define INF 0x3f3f3f3f

struct Node {
	int count;
	Node *left, *right;
	Node (int cnt = 0) {
		count = cnt;
		left = right = NULL;
	}
};

Node *st[SZ];
int lst[SZ], n_lst, n, q, a[SZ];

Node *insert(Node *node, int p, int L, int R, int value) {
	Node *r = new Node(node->count + 1);
	r->left = r->right = st[0];
	if (L == R)
		return r;
	int mid = (L + R) >> 1;
	if (value <= lst[mid]) {
		r->left = insert(node->left, 2 * p, L, mid, value);
		r->right = node->right;
	} else {
		r->right = insert(node->right, 2 * p + 1, mid + 1, R, value);
		r->left = node->left;
	}
	return r;
}

int count_less_than(Node *node, int p, int L, int R, int value) {
	if (value <= lst[L])
		return 0;
	if (lst[R] < value)
		return node->count;
	int mid = (L + R) >> 1;
	return count_less_than(node->left, 2 * p, L, mid, value) +
		count_less_than(node->right, 2 * p + 1, mid + 1, R, value);
}

int get_pos(int u, int v, int value) {
	int u_ans = count_less_than(st[v], 1, 0, n_lst - 1, value);
	int v_ans = count_less_than(st[u - 1], 1, 0, n_lst - 1, value);
	return abs(u_ans - v_ans);
}

int upper_bound(int u, int v, int k) {
	int lw = lst[0], hi = lst[n_lst - 1];
	while (lw < hi) {
		int mid = (lw + hi) >> 1;
		if (get_pos(u, v, mid) + 1 > k)
			hi = mid;
		else
			lw = mid + 1;
	}
	return lw;
}

int main() {
	scanf("%d %d", &n, &q);

	int max_val = -INF;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		if (max_val < a[i]) max_val = a[i];
	}
	a[++n] = max_val + 1;
	
	n_lst = 0;
	for (int i = 1; i <= n; i++)
		lst[n_lst++] = a[i];
	
	sort(lst, lst + n_lst);

	st[0] = new Node(0);
	st[0]->left = st[0]->right = st[0];

	for (int i = 1; i <= n; i++)
		st[i] = insert(st[i - 1], 1, 0, n_lst - 1, a[i]);

	for (int i = 1; i <= q; i++) {
		int u, v, k;
		scanf("%d %d %d", &u, &v, &k);
		printf("%d\n", upper_bound(u, v, k) - 1);
	}
	return 0;
}
