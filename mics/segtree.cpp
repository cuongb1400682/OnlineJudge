#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <climits>

using namespace std;

typedef vector<int> vi;

#define UNCHANGE INT_MAX

vi st, a, lazy;
int n;

#define st_sum(vertex, i, j) \
        st_query(vertex, 0, n - 1, i, j)

void st_build(int vertex, int L, int R) {
    if (L == R)
        st[vertex] = a[L];
    else {
        st_build(2 * vertex, L, (L + R) / 2);
        st_build(2 * vertex + 1, (L + R) / 2 + 1, R);
        st[vertex] = st[2 * vertex] + st[2 * vertex + 1];
    }
}

void st_create() {
    n = a.size();
    int len = 2 * pow(2, floor(log((double) n) / log(2.0)) + 1);
    st.assign(len, 0);
    lazy.assign(len, UNCHANGE);
    st_build(1, 0, n - 1);
}

int st_query(int vertex, int L, int R, int i, int j) {
    if (j < L || i > R)
        return -1;

    if (lazy[vertex] != UNCHANGE) {
        st[vertex] = (R - L + 1) * lazy[vertex];
        if (L != R) {
            lazy[2 * vertex] = lazy[vertex];
            lazy[2 * vertex + 1] = lazy[vertex];
        }
        lazy[vertex] = UNCHANGE;
        return st[vertex];
    }

    if (i <= L && j >= R)
        return st[vertex];

    int q1 = st_query(2 * vertex, L, (L + R) / 2, i, j);
    int q2 = st_query(2 * vertex + 1, (L + R) / 2 + 1, R, i, j);

    if (q1 == -1) return q2;
    if (q2 == -1) return q1;

    return q1 + q2;
}

void st_out(int vertex, int L, int R) {
    printf("[%d, %d] = %d\n", L, R, st[vertex]);
    if (L == R) return;
    st_out(2 * vertex, L, (L + R) / 2);
    st_out(2 * vertex + 1, (L + R) / 2 + 1, R);
}

void st_update(int vertex, int L, int R, int i, int j, int val) {
    if (lazy[vertex] != UNCHANGE) {
        st[vertex] = (R - L + 1) * lazy[vertex];
        if (R != L) {
            lazy[2 * vertex] = lazy[vertex];
            lazy[2 * vertex + 1] = lazy[vertex];
        }
        lazy[vertex] = UNCHANGE;
    }

    if (i > R || j < L) return;

    if (i <= L && R <= j) {
        st[vertex] = (R - L + 1) * val;
        if (L != R) {
            lazy[2 * vertex] = val;
            lazy[2 * vertex + 1] = val;
        }
    } else {
        st_update(2 * vertex, L, (L + R) / 2, i, j, val);
        st_update(2 * vertex + 1, (L + R) / 2 + 1, R, i, j, val);
        st[vertex] = st[2 * vertex] + st[2 * vertex + 1];
    }
}

int main(void) {
    freopen("input", "r", stdin);
    freopen("output", "w", stdout);
    int i;
    cin >> n;
    a.assign(n, 0);
    for (i = 0; i < n; i++)
        cin >> a[i];
    st_create();
    return 0;
}
