#include <bits/stdc++.h>
using namespace std;

#define SZ 50001
#define INF 0x3f3f3f3f

struct Node {
	int leftMax, rightMax, max, sum;
	Node(int leftMax = 0, int rightMax = 0, int max = 0, int sum = 0):
		leftMax(leftMax), rightMax(rightMax), max(max), sum(sum) { }
};

Node st[4 * SZ];
int a[SZ], n, q;

Node mix(Node left, Node right) {
	Node ans;
	ans.sum = left.sum + right.sum;
	ans.leftMax = max(left.leftMax, left.sum + right.leftMax);
	ans.rightMax = max(right.rightMax, right.sum + left.rightMax);
	ans.max = max(max(left.max, right.max), left.rightMax + right.leftMax);
	return ans;
}

void init(int p, int L, int R) {
	st[p] = Node();
	if (L == R) {
		st[p] = Node(a[L], a[L], a[L], a[L]);
		return;
	}
	int mid = (L + R) >> 1;
	init(2 * p, L, mid);
	init(2 * p + 1, mid + 1, R);
	st[p] = mix(st[2 * p], st[2 * p + 1]);
}

void update(int p, int L, int R, int u, int val) {
	if (L == R) {
		st[p] = Node(val, val, val, val);
		return;
	}
	int mid = (L + R) >> 1;
	if (u <= mid)
		update(2 * p, L, mid, u, val);
	else
		update(2 * p + 1, mid + 1, R, u, val);
	st[p] = mix(st[2 * p], st[2 * p + 1]);
}

Node query(int p, int L, int R, int u, int v) {
	if (v < L || R < u)
		return Node(INF, INF, INF, INF);
	if (u <= L && R <= v)
		return st[p];
	int mid = (L + R) >> 1;
	Node left = query(2 * p, L, mid, u, v);
	Node right = query(2 * p + 1, mid + 1, R, u, v);
	if (left.sum == INF)
		return right;
	if (right.sum == INF)
		return left;
	return mix(left, right);
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	init(1, 1, n);
	scanf("%d", &q);
	for (int i = 1; i <= q; i++) {
		int t, u, v;
		scanf("%d %d %d", &t, &u, &v);
		if (t == 0) {
			update(1, 1, n, u, v);
		} else {
			printf("%d\n", query(1, 1, n, u, v).max);
		}
	}
	return 0;
}
