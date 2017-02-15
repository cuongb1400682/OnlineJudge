#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

#define SZ 100005

struct Query {
    int l, r, q;
};

int sum[31][SZ], n, m, st[4 * SZ];
Query query[SZ];
vector<int> a;

void bit_update(int *bit, int u, int value) {
    for (; u <= n; u += (u & -u))
	bit[u] += value;
}

int bit_query(int *bit, int u, int v) {
    int ans = 0;
    for (; v > 0; v -= (v & -v)) 
	ans += bit[v];
    for (u--; u > 0; u -= (u & -u))
	ans -= bit[u];
    return int(ans > 0);
}

int get_pos(int z) {
    int ans = 0;
    while (z > 1) {
	z >>= 1;
	ans++;
    }
    return ans;
}

void st_update(int p, int L, int R, int u, int value) {
    if (L == R) {
	st[p] = value;
	return;
    }
    int mid = (L + R) >> 1;
    if (u <= mid)
	st_update(2 * p, L, mid, u, value);
    else
	st_update(2 * p + 1, mid + 1, R, u, value);
    st[p] = st[2 * p] & st[2 * p + 1];
}

int st_query(int p, int L, int R, int u, int v) {
    if (v < L || R < u)
	return -1;
    if (u <= L && R <= v)
	return st[p];
    int mid = (L + R) >> 1;
    int left_ans = st_query(2 * p, L, mid, u, v);
    int right_ans = st_query(2 * p + 1, mid + 1, R, u, v);
    if (left_ans == -1)
	return right_ans;
    if (right_ans == -1)
	return left_ans;
    return left_ans & right_ans;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
	scanf("%d %d %d", &query[i].l, &query[i].r, &query[i].q);
	for (int z = query[i].q; z > 0; z -= (z & -z)) {
	    int pos = get_pos(z & -z);
	    bit_update(sum[pos], query[i].l, 1);
	    bit_update(sum[pos], query[i].r + 1, -1);
	}
    }

    memset(st, 0, sizeof(st));
    a.clear();
    for (int i = 1; i <= n; i++) {
	int entry = 0;
	for (int j = 0; j <= 30; j++) {
	    int bit = bit_query(sum[j], 1, i);
	    entry |= (bit << j);
	}
	st_update(1, 1, n, i, entry);
	a.push_back(entry);
    }
    bool is_ok = true;
    for (int i = 1; i <= m; i++) {
	if (st_query(1, 1, n, query[i].l, query[i].r) != query[i].q) {
	    is_ok = false;
	    break;
	}
    }
    if (not is_ok)
	puts("NO");
    else {
	puts("YES");
	for (int i = 0; i < (int) a.size(); i++)
	    printf("%d ", a[i]);
	printf("\n");
    }
    return 0;
}
