#include <bits/stdc++.h>
using namespace std;

#define SZ 100005

typedef long long ll;

int st[SZ * 4], n, q, bit[SZ];

void init() {
    memset(st, 0, sizeof(st));
}

void invert(int p, int L, int R, int u, int v) {
    if (v < L || R < u)
        return;
    if (u <= L && R <= v) {
        if (st[p] == 0)
            st[p] = 1;
        else
            st[p] = 0;
        return;
    }
    invert(2 * p, L, (L + R) / 2, u, v);
    invert(2 * p + 1, (L + R) / 2 + 1, R, u, v);
}

int get_sum(int p, int L, int R, int u) {
    if (L == R)
        return st[p];
    if (u <= (L + R) / 2)
        return st[p] + get_sum(2 * p, L, (L + R) / 2, u);
    else
        return st[p] + get_sum(2 * p + 1, (L + R) / 2 + 1, R, u);
}

int ith_bit(int i) {
    return (get_sum(1, 1, n, i) & 1) ? bit[i] ^ 1 : bit[i];
}

int main() {
    int T;
    char str[256];
    scanf("%d\n", &T);
    for (int no = 1; no <= T; no++) {
        printf("Case %d:\n", no);
        init();
		
        int c;
        while (!isdigit(c = getchar()))
            ;
        n = 1;
        bit[1] = c - '0';
        while (isdigit(c = getchar()))
            bit[++n] = c - '0';

        scanf("%d", &q);
        while (q--) {
            scanf(" %s ", str);
            if (str[0] == 'I') {
                int u, v;
                scanf("%d %d", &u, &v);
                invert(1, 1, n, u, v);
            } else {
                int i;
                scanf("%d", &i);
                printf("%d\n", ith_bit(i));
            }
        }
    }
    return 0;
}
