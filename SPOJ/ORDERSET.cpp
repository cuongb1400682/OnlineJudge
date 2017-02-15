#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <map>
#include <vector>
using namespace std;

struct AvlNode {
	int key, count, height;	
	AvlNode *left, *right, *parent;

	AvlNode(int key) : key(key) {
		height = 1;
		count = 1;
		left = right = parent = NULL;
	}
};

AvlNode *root;

int left_count(AvlNode *p) {
	return p->left ? p->left->count : 0;
}

int right_count(AvlNode *p) {
	return p->right ? p->right->count : 0;
}

int left_height(AvlNode *p) {
	return p->left ? p->left->height : 0;
}

int right_height(AvlNode *p) {
	return p->right ? p->right->height : 0;
}

bool is_left(AvlNode *p) {
	return p->parent && p->parent->left == p;
}

bool is_right(AvlNode *p) {
	return p->parent && p->parent->right == p;
}

AvlNode* connect(AvlNode *parent, AvlNode *child, bool is_left) {
	if (parent) {
		if (is_left)
			parent->left = child;
		else
			parent->right = child;
	}
	if (child)
		child->parent = parent;
	return parent;
}

AvlNode* bst_insert(AvlNode *node, int key) {
	if (node == NULL)
		return new AvlNode(key);
	AvlNode *x = NULL;
	while (node) {
		x = node;
		if (key <= node->key)
			node = node->left;
		else
			node = node->right;
	}
	connect(x, new AvlNode(key), key <= x->key);
	return (key <= x->key ? x->left : x->right);
}

AvlNode* bst_erase(AvlNode *node, AvlNode* &root) {
	if (node->left && node->right) {
		AvlNode *p;
		for (p = node->left; p->right; p = p->right)
			;
		swap(node->key, p->key);
		node = p;
	}
	AvlNode *parent = node->parent;
	AvlNode *alt = NULL;
	if (node->left) {
		connect(parent, node->left, is_left(node));
		alt = node->left;
	} else {
		connect(parent, node->right, is_left(node));
		alt = node->right;
	}
	delete node;
	if (parent)
		return parent;
	else {
		root = alt;
		return alt;
	}
}

void adjust_param(AvlNode *x) {
	x->count = left_count(x) + right_count(x) + 1;
	x->height = max(left_height(x), right_height(x)) + 1;
}

void bring_up(AvlNode *child) {
	AvlNode *parent = child->parent;
	if (parent == NULL) return;
	AvlNode *grand = parent->parent;
	if (is_left(child)) {
		connect(parent, child->right, true);
		connect(child, parent, false);
	} else {
		connect(parent, child->left, false);
		connect(child, parent, true);
	}
	adjust_param(parent);
	adjust_param(child);
	if (grand)
		connect(grand, child, parent->key <= grand->key);
	else
		child->parent = NULL;
}

void rebalance(AvlNode *x) {
	AvlNode *y, *z;
	while (x) {
		adjust_param(x);
		if (abs(left_count(x) - right_count(x)) > 1) {
			y = left_count(x) > right_count(x) ? x->left : x->right;
			z = left_count(y) > right_count(y) ? y->left : y->right;
			if ((is_left(y) && is_right(z)) || (is_right(y) && is_left(z))) {
				bring_up(z);
				swap(y, z);
			}
			bring_up(y);
			swap(x, y);
		}
		x = x->parent;
	}
}

AvlNode* insert(AvlNode * &root, int key) {
	AvlNode *p = bst_insert(root, key);
	if (root == NULL)
		root = p;
	else {
		rebalance(p);
		AvlNode *x = root;
		while (x->parent)
			x = x->parent;
		root = x;
	}
	return p;
}

AvlNode* find(AvlNode *root, int key) {
	AvlNode* p = root;
	while (p) {
		if (p->key == key)
			return p;
		else if (key <= p->key)
			p = p->left;
		else
			p = p->right;
	}
	return NULL;
}

void erase(AvlNode * &root, int key) {
	AvlNode *p = find(root, key);
	if (p == NULL) return;
	p = bst_erase(p, root);
	if (p) {
		rebalance(p);
		AvlNode *x = root;
		while (x->parent)
			x = x->parent;
		root = x;
	}
}

AvlNode *kth_node(AvlNode *root, int kth) {
	while (true) {
		if (kth == left_count(root) + 1)
			return root;
		else if (kth > left_count(root) + 1) {
			kth -= left_count(root) + 1;
			root = root->right;
		} else {
			root = root->left;
		}
	}
	return NULL;
}

int max_element(AvlNode *root) {
	while (root->right)
		root = root->right;
	return root->key;
}

int count_less_than(AvlNode *root, int x) {
	AvlNode *lw_bnd = NULL, *p;
	int ans = 0;

	if (root == NULL)
		return 0;
	if (x > max_element(root))
		return root ? root->count : 0;

	p = root;
	while (p) {
		if (p->key == x) {
			lw_bnd = p;
			break;
		} else if (x < p->key) {
			if (not lw_bnd || p->key < lw_bnd->key)
				lw_bnd = p;
			p = p->left;
		} else {
			p = p->right;
		}
	}

	p = lw_bnd;
	ans = left_count(p);
	while (p != root) {
		if (is_right(p))
			ans += left_count(p->parent) + 1;
		p = p->parent;
	}

	return ans;
}

int main() {
	int n, x;
	char type[2];
	scanf("%d", &n);
	root = NULL;
	for (int i = 1; i <= n; i++) {
		scanf("%s %d", type, &x);
		if (type[0] == 'I') {
			if (find(root, x) == NULL)
				insert(root, x);
		} else if (type[0] == 'D') {
			erase(root, x);
		} else if (type[0] == 'K') {
			if (root == NULL || x > root->count)
				printf("invalid\n");
			else
				printf("%d\n", kth_node(root, x)->key);
		} else {
			printf("%d\n", count_less_than(root, x));
		} 
	}
	return 0;
}
