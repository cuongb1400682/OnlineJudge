#include <stdio.h>
#include <algorithm>
#include <string>
using namespace std;

#define SZ 30005

struct Node {
	int n_open, n_close, cnt;
	Node() :
		n_open(0), n_close(0), cnt(0) { }
};

Node st[4 * SZ];
char s[SZ];
int n, q, m;

Node mix(Node a, Node b) {
	Node ans;
	int diff = min(a.n_open, b.n_close);
	a.n_open -= diff;
	b.n_close -= diff;
	ans.cnt = a.cnt + b.cnt + diff;
	ans.n_open += a.n_open + b.n_open;
	ans.n_close += a.n_close + b.n_close;
	return ans;
}

void init(int p, int L, int R) {
	st[p] = Node();
	if (L == R) {
		st[p].n_open = (s[L] == '(' ? 1 : 0);
		st[p].n_close = (s[L] == ')' ? 1 : 0);
		return;
	}
	int mid = (L + R) >> 1;
	init(2 * p, L, mid);
	init(2 * p + 1, mid + 1, R);
	st[p] = mix(st[2 * p], st[2 * p + 1]);
}

void toggle(int p, int L, int R, int u) {
	if (L == R) {
		st[p].n_open = 1 - st[p].n_open;
		st[p].n_close = 1 - st[p].n_close;
		return;
	}
	int mid = (L + R) >> 1;
	if (u <= mid)
		toggle(2 * p, L, mid, u);
	else
		toggle(2 * p + 1, mid + 1, R, u);
	st[p] = mix(st[2 * p], st[2 * p + 1]);
}

bool is_ok() {
	return (n % 2 == 0)  && (st[1].cnt == (n >> 1));
}

void print(int p, int L, int R, string ind="") {
	printf("%s[%d, %d] -> o = %d, c = %d, cnt = %d\n",
		   ind.c_str(), L, R, st[p].n_open, st[p].n_close, st[p].cnt);
	if (L == R)
		return;
	int mid = (L + R) >> 1;
	print(2 * p, L, mid, ind + "   .");
	print(2 * p + 1, mid + 1, R, ind + "   .");
}

int main() {
	for (int no = 1; scanf("%d", &n) != EOF; no++) {
		printf("Test %d:\n", no);
		scanf("%s", s);
		scanf("%d", &m);
		init(1, 0, n - 1);
		for (int i = 0; i < m; i++) {
			int query;
			scanf("%d", &query);
			if (query == 0)
				puts(is_ok() ? "YES" : "NO");
			else {
				toggle(1, 0, n - 1, query - 1);
			}
		}
	}
	return 0;
}
