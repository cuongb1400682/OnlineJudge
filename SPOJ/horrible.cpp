/*
 * PROB: SPOJ - HORRIBLE - Horrible Queries
 * LANG: C++
 */

#include <cstdio>
#include <cstring>

#define REP(i, a, b) \
    for (int i = int(a); i <= int(b); i++)
#define LSOne(i) ((i) & (-(i)))
#define MAX_N 100000

typedef long long ll;

struct bit_t {
    ll bit[MAX_N + 1];
    int n;
    void create(int _n) {
        n = _n;
        memset(bit, 0, (n + 1) * sizeof bit[0]);
    }
    void update(int index, ll value) {
        for (; index <= n; index += LSOne(index))
            bit[index] += value;
    }
    ll query(int index) {
        ll retval = 0;
        for (; index > 0; index -= LSOne(index))
            retval += bit[index];
        return retval;
    }
};

int n;
bit_t b1, b2;

void bit_update_range(int L, int R, ll value) {
    b1.update(L, value);
    b1.update(R + 1, -value);
    b2.update(L, value * (L - 1));
    b2.update(R + 1, -value * R);
}

ll bit_query(int index) {
    return b1.query(index) * index - b2.query(index);
}

ll bit_query_range(int L, int R) {
    return bit_query(R) - bit_query(L - 1);
}

int main(void) {
    int t, c, cmd, p, q, v;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &c);

        b1.create(n);
        b2.create(n);

        while (c--) {
            scanf("%d", &cmd);
            if (cmd == 0) {
                scanf("%d%d%d", &p, &q, &v);
                bit_update_range(p, q, v);
//                printf("%d %d %d\n", p, q, v);
//                REP(i, 1, n)
//                    printf("%lld\n", bit_query(i));
//                printf("\n");
            } else {
                scanf("%d%d", &p, &q);
                printf("%lld\n", bit_query_range(p, q));
            }
        }


    }
    return 0;
}

 
