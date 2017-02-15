#include <bits/stdc++.h>
using namespace std;

#define INF 0x3f3f3f3f

int _max(int a, int b) {
	return a > b ? a : b;
}

struct Key {
	int max, left_max, right_max, sum;
	Key(int val = 0) {
		max = left_max = right_max = sum = val;
	}
	Key update(Key a, Key b) {
		sum = a.sum + b.sum;
		left_max = _max(a.left_max, a.sum + b.left_max);
		right_max = _max(b.right_max, b.sum + a.right_max);
		max = _max(_max(a.max, b.max), a.right_max + b.left_max);
		return *this;
	}
};

struct Node {
	Key key;
	int height, count;	
	Node *left, *right, *parent;

	Node(int key) {
		this->key = Key(key);
		count = height = 1;
		left = right = parent = NULL;
	}

	bool is_left() {
		return parent && parent->left == this;
	}
	
	bool is_right() {
		return parent && parent->right == this;
	}

	int left_count() {
		return left ? left->count : 0;
	}

	int right_count() {
		return right ? right->count : 0;
	}

	int left_height() {
		return left ? left->height : 0;
	}

	int right_height() {
		return right ? right->height : 0;
	}	
};

Node *root;
int n, q;

void connect(Node *parent, Node *child, bool is_left) {
	if (parent) {
		if (is_left)
			parent->left = child;
		else
			parent->right = child;
	}
	if (child)
		child->parent = parent;
}

void adjust_param(Node *p) {
	p->count = p->left_count() + p->right_count();
	p->height = _max(p->left_height(), p->right_height()) + 1;
	if (p->left && p->right)
		p->key.update(p->left->key, p->right->key);
	else if (p->left)
		p->key = p->left->key;
	else if (p->right)
		p->key = p->right->key;
}

void bring_up(Node *child) {
	Node *parent = child->parent;
	if (parent == NULL) return;
	Node *grand = parent->parent;
	if (child->is_left()) {
		connect(parent, child->right, true);
		connect(child, parent, false);
	} else {
		connect(parent, child->left, false);
		connect(child, parent, true);
	}
	adjust_param(parent);
	adjust_param(child);
	if (grand)
		// this takes over an hour to debug
		connect(grand, child, grand->left == parent); 
	else
		child->parent = NULL;
}

void rebalance(Node *x) {
	if (x) {
		if (x->left_height() - x->right_height() > 1)
			bring_up(x->left);			
		else if (x->right_height() - x->left_height() > 1)
			bring_up(x->right);			
	}
}

void insert(Node *st, int p, int L, int R, int u, int value) {
	if (L == R) {
		if (u > root->count) {
			connect(st, new Node(st->key.max), true);
			connect(st, new Node(value), false);
		} else {
			connect(st, new Node(value), true);
			connect(st, new Node(st->key.max), false);
		}
		adjust_param(st);
		return;
	}
	int mid = L + st->left_count() - 1;
	if (u <= mid)
		insert(st->left, 2 * p, L, mid, u, value);
	else
		insert(st->right, 2 * p + 1, mid + 1, R, u, value);
	adjust_param(st);
	rebalance(st);
}

bool erase(Node *st, int p, int L, int R, int u) {
	if (L == R) {
		Node *parent = st->parent;
		Node *grand = parent->parent;
		if (st->is_left())
			connect(grand, parent->right, parent->is_left());
		else
			connect(grand, parent->left, parent->is_left());
		if (grand)
			adjust_param(grand);
		else
			root = (parent->right ? parent->right : parent->left);
		delete st;
		delete parent;
		return true;
	}
	int mid = L + st->left_count() - 1;
	bool is_deleted = false;
	if (u <= mid)
		is_deleted = erase(st->left, 2 * p, L, mid, u);
	else
		is_deleted = erase(st->right, 2 * p + 1, mid + 1, R, u);
	if (not is_deleted) {
		adjust_param(st);
		rebalance(st);
	}
	return false;
}

void change(Node *st, int p, int L, int R, int u, int value) {
	if (L == R) {
		st->key = Key(value);
		return;
	}
	int mid = L + st->left_count() - 1;
	if (u <= mid)
		change(st->left, 2 * p, L, mid, u, value);
	else
		change(st->right, 2 * p + 1, mid + 1, R, u, value);
	adjust_param(st);
}

void insert(int pos, int value) {
	if (root == NULL)
		root = new Node(value);
	else
		insert(root, 1, 1, root->count, pos, value);
	while (root && root->parent)
		root = root->parent;
}

void erase(int pos) {
	if (root == NULL || pos > root->count)
		return;
	else {
		if (root->count == 1) {
			delete root;
			root = NULL;
		} else {
			erase(root, 1, 1, root->count, pos);
			while (root && root->parent)
				root = root->parent;
		}			
	}		
}

Key query(Node *st, int p, int L, int R, int u, int v) {
	if (v < L || R < u)
		return Key(-INF);
	if (u <= L && R <= v)
		return st->key;
	int mid = L + st->left_count() - 1;
	Key leftAns = query(st->left, 2 * p, L, mid, u, v);
	Key rightAns = query(st->right, 2 * p + 1, mid + 1, R, u, v);
	if (leftAns.sum == -INF)
		return rightAns;
	else if (rightAns.sum == -INF)
		return leftAns;
	else
		return Key().update(leftAns, rightAns);
}

int main() {
	scanf("%d", &n);
	root = NULL;
	for (int i = 1, number; i <= n; i++) {
		scanf("%d", &number);
		insert(i, number);
	}
	scanf("%d", &q);
	for (int i = 1; i <= q; i++) {
		char type[2]; int x, y;
		scanf("%s %d", type, &x);
		if (*type != 'D')
			scanf("%d", &y);
		if (*type == 'I') {
			insert(x, y);
		} else if (*type == 'D') {
			erase(x);
		} else if (*type == 'R') {
			change(root, 1, 1, root->count, x, y);
		} else if (*type == 'Q') {
			printf("%d\n", query(root, 1, 1, root->count, x, y).max);
		}
	}
	return 0;
}
