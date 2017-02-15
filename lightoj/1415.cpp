#include <bits/stdc++.h>
using namespace std;

#define SZ 200005
#define INF 0x3f3f3f3f3f3f3f3fLL

typedef long long ll;

#define dbg(x) cerr << "[" #x " = " << x << "]" << endl
template<class T>
void __dba(const T* a, ll n) {
    cerr << "[";
    for (ll i = 0; i < n; i++)
    cerr << (i > 0 ? ", " : "" ) << a[i];
    cerr << "]" << endl;
}
#define dba(a, n) { cerr << #a " = "; __dba(a, n); }
#define err(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)

typedef pair<ll, ll> ii;


struct Node {
   ll height;
   ll f, fh;
};

ll n, type[SZ], height[SZ], before[SZ], prev[SZ];
ll F[SZ];
Node st[4 * SZ];

void init(ll p, ll L, ll R) {
    st[p].height = st[p].f = st[p].fh = 0;
    if (L == R)
        return;
    init(2 * p, L, (L + R) / 2);
    init(2 * p + 1, (L + R) / 2 + 1, R);
}

void propagate(ll p, ll L, ll R) {
    if (st[p].height != 0) {
        ll height = st[p].height;
        st[2 * p].height = height;
        st[2 * p].fh = st[2 * p].f + height;
        st[2 * p + 1].height = height;
        st[2 * p + 1].fh = st[2 * p + 1].f + height;
        st[p].height = 0;
    }
}

void mix(ll p) {
    st[p].f = min(st[2 * p].f, st[2 * p + 1].f);
    st[p].fh = min(st[2 * p].fh, st[2 * p + 1].fh);
}

void insert(ll p, ll L, ll R, ll i, ll height) {
    if (L == R) {
        st[p].height = height;
        st[p].fh = F[i-1] + height;
        st[p].f = F[i-1];
        return;
    }
    propagate(p, L, R);
    if (i <= (L + R) / 2)
        insert(2 * p, L, (L + R) / 2, i, height);
    else
        insert(2 * p + 1, (L + R) / 2 + 1, R, i, height);
    mix(p);
}

void update(ll p, ll L, ll R, ll u, ll v, ll height) {
    if (v < L || R < u)
        return;
    if (u <= L && R <= v) {
        st[p].height = height;
        st[p].fh = st[p].f + height;
        return;
    }
    propagate(p, L, R);
    update(2 * p, L, (L + R) / 2, u, v, height);
    update(2 * p + 1, (L + R) / 2 + 1, R, u, v, height);
    mix(p);
}

ll query(ll p, ll L, ll R, ll u, ll v) {
    if (v < L || R < u)
        return INF;
    if (u <= L && R <= v)
        return st[p].fh;
    propagate(p, L, R);
    return min(query(2 * p, L, (L + R) / 2, u, v),
               query(2 * p + 1, (L + R) / 2 + 1, R, u, v));
}

void calc_prev() {
    static ll type_pos[SZ];
    memset(type_pos, -1, sizeof(type_pos));
    memset(prev, 0, sizeof(prev));
    prev[0] = 0;
    type_pos[type[0]] = 0;
    for (ll i = 1; i < n; i++) {
        prev[i] = prev[i - 1];
        if (type_pos[type[i]] != -1)
            prev[i] = max(prev[i], type_pos[type[i]] + 1);
        type_pos[type[i]] = i;
    }
}

void calc_before() {
    memset(before, 0, sizeof(before));
    for (ll i = 1; i < n; i++) {
        if (height[i] < height[i - 1])
            before[i] = i;
        else {
            ll j;
            for (j = before[i - 1] - 1; j >= 0 && height[j] <= height[i]; j = before[j] - 1)
                ;
            before[i] = j + 1;
        }
    }
}

void bruteForce() {
    static ll F_inBruteForce[SZ];
    memset(F_inBruteForce, 0, sizeof(F_inBruteForce));
    for (ll i = 1; i <= n; i++) {
        F_inBruteForce[i] = INF; ll h = 0;
        for (ll j = prev[i]; j <= i; j++) {
            h = max(h, height[j]);
            F_inBruteForce[i] = min(F_inBruteForce[i], F_inBruteForce[j - 1] + h);
        }
    }
    dba(F_inBruteForce, n);
}

int main(void) {
    ll nTest;
    scanf("%lld", &nTest);
    for (ll no = 1; no <= nTest; no++) {
        scanf("%lld", &n);
        memset(F, 0, sizeof(F));
        init(1, 0, n - 1);
        for (ll i = 0; i < n; i++)
            scanf("%lld%lld", &type[i], &height[i]);
        calc_before();
        calc_prev();
        //bruteForce();
        for (ll i = 0; i < n; i++) {
            insert(1, 0, n - 1, i, height[i]);
            update(1, 0, n - 1, before[i], i, height[i]);
            F[i] = query(1, 0, n - 1, prev[i], i);
        }
        //dba(F, n);
        printf("Case %lld: %lld\n", no, F[n - 1]);
    }
    return 0;
}
