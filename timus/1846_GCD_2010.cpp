#include <bits/stdc++.h>
using namespace std;

vector<int> lst;
int n, acnt[100005];
struct QQQ { int sign, num; } query[100005];
int st[4 * 100005];

int gcd(int a, int b) {
	while (a && b) {
		if (a > b)
			a %= b;
		else
			b %= a;
	}
	return a + b;
}

void update(int p, int L, int R, int u, int val) {
	if (L == R) {
		acnt[L] += val;
		st[p] = (acnt[L] > 0 ? lst[L] : 0);
		return;
	}
	int mid = (L + R) >> 1;
	if (u <= lst[mid])
		update(2 * p, L, mid, u, val);
	else
		update(2 * p + 1, mid + 1, R, u, val);
	st[p] = gcd(st[2 * p], st[2 * p + 1]);
}

int main() {
	scanf("%d", &n);
	vector<int> h;
	char sign[10];
	for (int i = 0; i < n; i++) { 
		scanf("%s %d", sign, &query[i].num);
		h.push_back(query[i].num);
		query[i].sign = (*sign == '-' ? -1 : 1);
	}

	sort(h.begin(), h.end());

	for (vector<int>::iterator it = h.begin(); it != h.end(); it++)
		if (lst.empty() || *it != lst.back())
			lst.push_back(*it);
	
	int cnt = 0;
	memset(st, 0, sizeof(st));
	for (int i = 0; i < n; i++) {
		update(1, 0, lst.size() - 1, query[i].num, query[i].sign);
		cnt += query[i].sign;
		if (cnt == 0)
			printf("1\n");
		else
			printf("%d\n", st[1]);
	}
	return 0;
}
