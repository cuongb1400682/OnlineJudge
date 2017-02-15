/*
 * PROB: SPOJ - UPDATEIT - Update the array !
 * LANG: C++
 */

#include <cstdio>
#include <cstring>

using namespace std;

#define MAX_N 10000
#define REP(i, a, b) \
    for (int i = int(a); i <= int(b); i++)
#define LSOne(i) ((i) & (-(i)))

int bit[MAX_N + 1];
int bitlen;

void bit_create(int n) {
    bitlen = n;
    memset(bit, 0, sizeof bit);
}

void bit_update(int index, int val) {
    while (index <= bitlen) {
        bit[index] += val;
        index += LSOne(index);
    }
}

void bit_range_update(int L, int R, int val) {
    bit_update(L, +val);
    bit_update(R + 1, -val);
}

int bit_query(int index) {
    int retval = 0;
    while (index) {
        retval += bit[index];
        index -= LSOne(index);
    }
    return retval;
}

int main(void) {
    int t, n, u, l, r, q, val, index;

    // for debugging
    freopen("updateit.in", "r", stdin);
    freopen("updateit.out", "w", stdout);

    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &u);
        bit_create(n);

        REP(i, 1, u) {
            scanf("%d%d%d", &l, &r, &val);
            bit_range_update(l + 1, r + 1, val);
        }

        scanf("%d", &q);

        REP(i, 1, q) {
            scanf("%d", &index);
            printf("%d\n", bit_query(index + 1));
        }
    }
    return 0;
}


