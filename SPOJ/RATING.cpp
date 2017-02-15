#include <stdio.h>
#include <string.h>
#include <map>
#include <algorithm>
using namespace std;

#define SZ 300005

struct Answer {
	int x, y, i, ans;
};

int n, st[3 * SZ];
Answer a[SZ];

bool cmp_x(Answer a, Answer b) {
	if (a.x != b.x)
		return a.x < b.x;
	else
		return a.y < b.y;
}

bool cmp_i(Answer a, Answer b) {
	return a.i <  b.i;
}

void insert(int p, int L, int R, int u) {
	if (L == R) {
		st[p]++;
		return;
	}
	int mid = (L + R) >> 1;
	if (u <= mid)
		insert(2 * p, L, mid, u);
	else
		insert(2 * p + 1, mid + 1, R, u);
	st[p] = st[2 * p] + st[2 * p + 1];
}

int get_sum(int p, int L, int R, int u, int v) {
	if (v < L || R < u)
		return 0;
	if (u <= L && R <= v)
		return st[p];
	int mid = (L + R) >> 1;
	int leftVal = get_sum(2 * p, L, mid, u, v);
	int rightVal = get_sum(2 * p + 1, mid + 1, R, u, v);
	return leftVal + rightVal;
}

int main() {
	scanf("%d", &n);
	map<int, int> map_x, map_y;
	
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &a[i].x, &a[i].y);
		a[i].i = i;
		map_x[a[i].x] = -1;
		map_y[a[i].y] = -1;
	}	
	
	int cnt = 0;
	for (map<int, int>::iterator it = map_x.begin(); it != map_x.end(); it++)
		map_x[it->first] = ++cnt;
	cnt = 0;
	for (map<int, int>::iterator it = map_y.begin(); it != map_y.end(); it++)
		map_y[it->first] = ++cnt;

	for (int i = 0; i < n; i++) {
		a[i].x = map_x[a[i].x];
		a[i].y = map_y[a[i].y];		
	}

	sort(a, a + n, cmp_x);

	memset(st, 0, sizeof(st));
	for (int i = 0; i < n; i++) {
//		printf("at %d %d\n", a[i].x, a[i].y);
		a[i].ans = (a[i].y == 0 ? 0 : get_sum(1, 0, SZ, 0, a[i].y));
//	printf("ans = %d\n\n", a[i].ans);
		insert(1, 0, SZ, a[i].y);
	}

	for (int i = 1; i < n; i++)
		if (a[i].x == a[i - 1].x && a[i].y == a[i - 1].y)
			a[i].ans = a[i - 1].ans;
	
	sort(a, a + n, cmp_i);

	for (int i = 0; i < n; i++)
		printf("%d\n", a[i].ans);
		
	return 0;
}
