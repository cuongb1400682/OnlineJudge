#include <bits/stdc++.h>
using namespace std;

#define INF 0x3f3f3f3f
#define SZ 100005

struct Node {
	int value;
	int height;
	int size;
	Node *left, *right, *parent;
	Node(int _value = 0) {
		value = _value;
		height = 1;
		size = 1;
		left = right = parent = NULL;
	}
	int left_value() {
		return left ? left->value : 0;
	}
	int right_value() {
		return right ? right->value : 0;
	}
	int left_height() {
		return left ? left->height : 0;
	}
	int right_height() {
		return right ? right->height : 0;
	}
	int left_size() {
		return left ? left->size : 0;
	}
	int right_size() {
		return right ? right->size : 0;
	}	
};

Node *st;
int a[SZ], n;

void destroy(Node *p) {
	if (p == NULL)
		return;
	destroy(p->left);
	destroy(p->right);
	delete p;
}

void update(Node *st) {
	st->value = max(st->left_value(), st->right_value());
	st->height = max(st->left_height(), st->right_height()) + 1;
	st->size = st->left_size() + st->right_size();
}

void connect(Node *p, Node *c, bool is_left) {
	if (p != NULL) {
		if (is_left)
			p->left = c;
		else
			p->right = c;
	}
	if (c != NULL)
		c->parent = p;
}

void go_up(Node *p) {
	Node *parent = p->parent;
	if (parent == NULL) return;
	Node *grand = parent->parent;
	bool is_left = grand && grand->left == parent;
	if (parent->left == p) {
		connect(parent, p->right, true);
		connect(p, parent, false);
	} else if (parent->right == p) {
		connect(parent, p->left, false);
		connect(p, parent, true);
	}
	update(parent);
	update(p);
	connect(grand, p, is_left);
}

void balance(Node *st) {
	if (st->left_height() - st->right_height() > 1)
		go_up(st->left);
	else if (st->right_height() - st->left_height() > 1)
		go_up(st->right);
}

void insert(Node *st, int L, int R, int u, int value) {
	if (u < L || R < u || st == NULL)
		return;
	if (L == R) {
		connect(st, new Node(value), true);
		connect(st, new Node(st->value), false);
		update(st);
		return;
	}
	int mid = L + st->left_size() - 1;
	if (st->left)
		insert(st->left, L, mid, u, value);
	if (st->right)
		insert(st->right, mid + 1, R, u, value);
	update(st);
	balance(st);
}

int get_max(Node *st, int L, int R, int u, int v) {
	if (v < L || R < u || st == NULL)
		return -INF;
	if (u <= L && R <= v)
		return st->value;
	int mid = L + st->left_size() - 1;
	int leftAns = get_max(st->left, L, mid, u, v);
	int rightAns = get_max(st->right, mid + 1, R, u, v);
	return max(leftAns, rightAns);
}

int main() {
	st = new Node(-INF);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		int u, v; char type[20];
		scanf("%s %d %d", type, &u, &v);
		if (*type == 'A') {
			insert(st, 1, st->size, v, u);
			while (st->parent)
				st = st->parent;
		} else if (*type == 'Q') {
			printf("%d\n", get_max(st, 1, st->size, u, v));
		}
	}
	destroy(st);
	return 0;
}
