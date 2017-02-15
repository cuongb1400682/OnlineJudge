#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;

#define SZ 1000005

struct Node {
	int open, close, correct;
	Node() {
		open = close = correct = 0;
	}
};

char bracket[SZ];
Node st[4 * SZ];
int n, q;

Node mix(Node a, Node b) {
	Node ans;
	int new_correct = min(a.open, b.close);
	a.open -= new_correct;
	b.close -= new_correct;	
	ans.correct = a.correct + b.correct + new_correct;
	ans.open = a.open + b.open;
	ans.close = a.close + b.close;
	return ans;
}

void init(int p, int L, int R) {
	if (L == R) {
		st[p].open = bracket[L] == '(';
		st[p].close = bracket[L] == ')';
		st[p].correct = 0;
		return;
	}
	int mid = (L + R) >> 1;
	init(2 * p, L, mid);
	init(2 * p + 1, mid + 1, R);
	st[p] = mix(st[2 * p], st[2 * p + 1]);
}

Node query(int p, int L, int R, int u, int v) {
	if (v < L || R < u)
		return Node();
	if (u <= L && R <= v)
		return st[p];
	int mid = (L + R) >> 1;
	return mix(query(2 * p, L, mid, u, v),
			   query(2 * p + 1, mid + 1, R, u, v));
}

int main() {
	scanf("%s", bracket + 1);
	bracket[0] = '$';
	n = strlen(bracket + 1);
	init(1, 1, n);
	scanf("%d", &q);
	while (q--) {
		int u, v;
		scanf("%d %d", &u, &v);
		printf("%d\n", query(1, 1, n, u, v).correct * 2);
	}
	return 0;
}
