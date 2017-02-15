#include <bits/stdc++.h>
using namespace std;

#define debug(x) cerr << #x " = " << (x) << '\n'
#define arr(x, n) {cerr<<#x<<" = "<<"["<<(n)<<"]"<<"(";for(ll _=0;_<(n);_++) cerr<<(x)[_]<<(_!=(n)-1?", ":")\n");}
#define iarr(x, m, n) {cerr<<#x":\n";for(ll _=(m);_<=(n);_++) cerr<<_<<": "<<(x)[_]<<'\n';}
#define err(...) fprintf(stderr, __VA_ARGS__)
#define SZ 30005

typedef long long ll;

struct Node {
	int count;
	Node *left, *right;
	Node(int cnt, Node *lft, Node *rght) {
	    count = cnt;
		left = lft;
		right = rght;
	}
} *st[SZ], *null_tree;

int data[SZ], memo[SZ], n_data, n_memo;

void init() {
	null_tree = st[0] = new Node(0, NULL, NULL);
	st[0]->left = null_tree;
	st[0]->right = null_tree;
	set<int> uniq;
	for (int i = 1; i <= n_data; i++) {
		uniq.insert(data[i]);
	}
	n_memo = 0;
	for (set<int>::iterator it = uniq.begin(); it != uniq.end(); it++) {
		memo[++n_memo] = *it;
	}
}

void print_tree(Node *node, int L, int R, string indent = "") {
	err("%s[%d, %d] -> %d\n", indent.c_str(), L, R, node->count);
	if (node->left != null_tree)
		print_tree(node->left, L, (L + R) / 2, indent + "   .");
	if (node->right != null_tree)
		print_tree(node->right, (L + R) / 2 + 1, R, indent + "   .");
}

Node* insert(Node *node, int L, int R, int u) {
	if (L == R)
		return new Node(node->count + 1, null_tree, null_tree);
	Node *ans = new Node(node->count + 1, node->left, node->right);
	int mid = (L + R) / 2;
	if (u <= memo[mid]) {
		ans->left = insert(node->left, L, mid, u);
	} else {
		ans->right = insert(node->right, mid + 1, R, u);
	}
	return ans;
}

int get_count(Node *node, int L, int R, int val) {
	if (memo[R] <= val)
		return 0;
	if (val < memo[L])
		return node->count;
	return get_count(node->left, L, (L + R) / 2, val) +
		get_count(node->right, (L + R) / 2 + 1, R, val);
}

int main() {
	int u, v, k, q;
	scanf("%d", &n_data);
	for (int i = 1; i <= n_data; i++) 
		scanf("%d", &data[i]);
	init();
	for (int i = 1; i <= n_data; i++) {
		st[i] = insert(st[i - 1], 1, n_memo, data[i]);
	}

	scanf("%d", &q);
	int ans = 0;
	while (q--) {
		scanf("%d %d %d", &u, &v, &k);
		u ^= ans;
		v ^= ans;
		k ^= ans;
		if (u > v)
			puts("0");
		else {
			u--;
			int tmp1 = (v <= 0 ? 0 : get_count(st[min(v, n_data)], 1, n_memo, k));
			int tmp2 = (u <= 0 ? 0 : get_count(st[min(u, n_data)], 1, n_memo, k));
			ans =  tmp1 - tmp2;
			printf("%d\n", ans);
		}
	}
	return 0;
}
