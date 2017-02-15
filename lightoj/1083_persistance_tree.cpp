#include <bits/stdc++.h>
using namespace std;

#define debug(x) cerr << #x " = " << (x) << '\n'
#define arr(x, n) {cerr<<#x<<" = "<<"["<<(n)<<"]"<<"(";for(ll _=0;_<(n);_++) cerr<<(x)[_]<<(_!=(n)-1?", ":")\n");}
#define iarr(x, m, n) {cerr<<#x":\n";for(ll _=(m);_<=(n);_++) cerr<<_<<": "<<(x)[_]<<'\n';}
#define err(...) fprintf(stderr, __VA_ARGS__)
#define SZ 30005

typedef long long ll;
typedef short int si;

struct Node {
	si count;
	Node *left, *right;
	Node(si cnt, Node *lft, Node *rght) {
	    count = cnt;
		left = lft;
		right = rght;
	}
} *st[SZ], *null_tree;

si data[SZ], memo[SZ], n_data, n_memo;

void init() {
	null_tree = st[0] = new Node(0, NULL, NULL);
	st[0]->left = null_tree;
	st[0]->right = null_tree;
	set<si> uniq;
	for (si i = 1; i <= n_data; i++) {
		uniq.insert(data[i]);
	}
	n_memo = 0;
	for (set<si>::iterator it = uniq.begin(); it != uniq.end(); it++) {
		memo[++n_memo] = *it;
	}
}

void print_tree(Node *node, si L, si R, string indent = "") {
	err("%s[%d, %d] -> %d\n", indent.c_str(), L, R, node->count);
	if (node->left != null_tree)
		print_tree(node->left, L, (L + R) / 2, indent + "   .");
	if (node->right != null_tree)
		print_tree(node->right, (L + R) / 2 + 1, R, indent + "   .");
}

Node* insert(Node *node, si L, si R, si u) {
	if (L == R)
		return new Node(node->count + 1, null_tree, null_tree);
	Node *ans = new Node(node->count + 1, node->left, node->right);
	si mid = (L + R) / 2;
	if (u <= memo[mid]) {
		ans->left = insert(node->left, L, mid, u);
	} else {
		ans->right = insert(node->right, mid + 1, R, u);
	}
	return ans;
}

si cnt_lt(Node *node, si L, si R, si val) {
	if (memo[L] >= val)
		return 0;
	if (memo[R] < val)
		return node->count;
	return cnt_lt(node->left, L, (L + R) / 2, val) +
		cnt_lt(node->right, (L + R) / 2 + 1, R, val);
}

si lw_bnd(si idx) {
	si i = 1, j = n_data;
	si key = cnt_lt(st[idx], 1, n_memo, data[idx]);
	while (i < j) {
		si mid = (i + j) >> 1;
		if (cnt_lt(st[mid], 1, n_memo, data[idx]) >= key)
			j = mid;
		else
			i = mid + 1;
	}
	return i;
}

si up_bnd(si idx) {
	si i = 1, j = n_data;
	si key = cnt_lt(st[idx], 1, n_memo, data[idx]);
	while (i < j) {
		si mid = (i + j) >> 1;
		if (cnt_lt(st[mid], 1, n_memo, data[idx]) <= key)
			i = mid + 1;
		else
			j = mid;
	}
	return i;
}

int main() {
	si t;	
	scanf("%hd", &t);
	for (si no = 1; no <= t; no++) {
		scanf("%hd", &n_data);
		for (si i = 1; i <= n_data; i++)
			scanf("%hd", &data[i]);
		init();
		for (si i = 1; i <= n_data; i++) {
			st[i] = insert(st[i - 1], 1, n_memo, data[i]);
		}
		si ans = 0;
		for (si i = 1; i <= n_data; i++) {
			si lw = lw_bnd(i);
			si hi = up_bnd(i);
			if (lw < n_data && data[lw] < data[i])
				lw++;
			if (hi > 1 && data[hi] < data[i])
				hi--;
			si S = (hi - lw + 1) * data[i];
			ans = max(ans, S);
		}
		printf("Case %hd: %hd\n", no, ans);
	}
	return 0;
}

