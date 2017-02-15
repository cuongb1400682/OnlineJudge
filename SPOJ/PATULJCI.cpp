#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

#define SZ 300005
#define INF 0x3f3f3f3f

struct Node {
	int count, number;
	Node(int val = 0) { count = number = val; }
};

typedef pair<int, int> ii;

Node st[4 * SZ];
int a[SZ], n, q, c;
ii A[SZ];

Node mix(Node a, Node b) {
	if (a.number == INF)
		return b;
	if (b.number == INF)
		return a;
	Node ans;
	if (a.number == b.number) {
		ans.number = a.number;
		ans.count = a.count + b.count;
	} else {
		if (a.count < b.count) {
			ans.count = b.count - a.count;
			ans.number = b.number;
		} else {
			ans.count = a.count - b.count;
			ans.number = a.number;
		}
	}
	return ans;
}

void init(int p, int L, int R) {
	st[p] = Node();
	if (L == R) {
		st[p].count = 1;
		st[p].number = a[L];
		return;
	}
	int mid = (L + R) >> 1;
	init(2 * p, L, mid);
	init(2 * p + 1, mid + 1, R);
	st[p] = mix(st[2 * p], st[2 * p + 1]);
}

Node query(int p, int L, int R, int u, int v) {
	if (v < L || R < u) {
		Node ans;
		ans.number = INF;
		ans.count = 0;
		return ans;
	}
	if (u <= L && R <= v)
		return st[p];
	int mid = (L + R) >> 1;
	return mix(query(2 * p, L, mid, u, v),
			   query(2 * p + 1, mid + 1, R, u, v));
}

int main() {
	scanf("%d %d", &n, &c);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		A[i - 1] = ii(a[i], i);
	}
	init(1, 1, n);
	scanf("%d", &q);
	sort(A, A + n);
	for (int i = 1; i <= q; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		Node node = query(1, 1, n, u, v);
		int nu = node.number;
		int r = upper_bound(A, A + n, ii(nu, v)) -
			lower_bound(A, A+ n, ii(nu, u));
		if (r * 2 > v - u + 1)
			printf("yes %d\n", nu);
		else
			printf("no\n");
			
	}
	return 0;
}
