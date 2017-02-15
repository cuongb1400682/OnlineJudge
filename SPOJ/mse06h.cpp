/*
 * PROB: SPOJ - MSE06H - Japan
 * LANG: C++
 */

#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;

#define MAX_N 1200
#define REP(i, a, b) \
    for (int i = int(a); i <= int(b); i++)
#define LSOne(i) (i & (-(i)))

struct segment_t { int x, y; };
struct bit_t {
    int bit[MAX_N + 1];
    ll n;
    void create(int n) {
        this->n = n;
        memset(bit, 0, (n + 2) * sizeof bit[0]);
    }
    void update(int index, ll value = 1) {
        if (index <= 0) return;
        while (index <= n) {
            bit[index] += value;
            index += LSOne(index);
        }
    }
    ll query(int index) {
        ll retval = 0;
        while (index) {
            retval += bit[index];
            index -= LSOne(index);
        }
        return retval;
    }
};

int m, n, k;
segment_t a[MAX_N * MAX_N];
bit_t b;

inline int compare(segment_t *i, segment_t *k) {
    if (i->x != k->x)
        return i->x - k->x;
    else
        return i->y - k->y;
}

void sort(int L, int R) {
    if (L >= R) return;
    ll i = L, j = R;
    segment_t p = a[(i + j) / 2];

    do {
        while (compare(&p, &a[i]) > 0) i++;
        while (compare(&p, &a[j]) < 0) j--;
        if (i <= j) {
            segment_t t = a[i];
            a[i] = a[j];
            a[j] = t;
            i++, j--;
        }
    } while (i <= j);

    sort(L, j);
    sort(i, R);
}

void readf() {
    scanf("%d%d%d", &n, &m, &k);
    REP(i, 0, k - 1)
        scanf("%d%d", &a[i].x, &a[i].y);
    sort(0, k - 1);
}

ll solve() {
    int y;
    ll retval;

    b.create(m + 1);
    retval = 0;

    REP(i, 0, k - 1) {
        y = m - a[i].y + 1;
        retval += b.query(y);
        b.update(y + 1);
    }

    return retval;
}

int main(void) {
    // for debugging
    freopen("mse06h.in", "r", stdin);
    freopen("mse06h.out", "w", stdout);
    int t;
    ll result;
    scanf("%d", &t);
    REP(i, 1, t) {
        readf();
        result = solve();
        printf("Test case %d: %lld\n", i, result);
    }
}
