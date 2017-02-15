#include <bits/stdc++.h>
using namespace std;

#define SZ 100005

typedef long long ll;

struct Node {
    ll lazy, sum;
};

Node st[4*SZ];
ll n, q, t;

void create(ll p, ll L, ll R) {
    st[p].lazy = st[p].sum = 0;
    if (L == R)
        return;
    create(2*p, L, (L+R)/2);
    create(2*p+1, (L+R)/2+1, R);
}

void propagate(ll p, ll L, ll R) {
    ll lazy, rLen, lLen;
    if (st[p].lazy != 0) {
        lazy = st[p].lazy;

        rLen = (R - L + 1) / 2;
        lLen = rLen + ((R - L + 1) & 1);

        st[p].lazy = 0;

        st[2*p].lazy += lazy;
        st[2*p].sum += lLen * lazy;

        st[2*p+1].lazy += lazy;
        st[2*p+1].sum += rLen * lazy;
    }
}

void update(ll p, ll L, ll R, ll u, ll v, ll val) {
    if (v < L || R < u)
        return;
    if (u <= L && R <= v) {
        st[p].lazy += val;
        st[p].sum += val * (R - L + 1);
        return;
    }
    propagate(p, L, R);
    update(2*p, L, (L+R)/2, u, v, val);
    update(2*p+1, (L+R)/2+1, R, u, v, val);
    st[p].sum = st[2*p].sum + st[2*p+1].sum;
}

ll query(ll p, ll L, ll R, ll u, ll v) {
    if (v < L || R < u)
        return 0;
    if (u <= L && R <= v)
        return st[p].sum;
    propagate(p, L, R);
    ll lAns = query(2*p, L, (L+R)/2, u, v);
    ll rAns = query(2*p+1, (L+R)/2+1, R, u, v);
    return lAns + rAns;
}

ll query(ll u, ll v) { return query(1, 0, n - 1, u, v); }

void update(ll u, ll v, ll val) { update(1, 0, n - 1, u, v, val); }

int main(void) {
    scanf("%lld", &t);
    for (ll caseNo = 1, x, y, v, tt; caseNo <= t; caseNo++) {
        scanf("%lld%lld", &n, &q);
        create(1, 0, n - 1);
        printf("Case %lld:\n", caseNo);
        for (ll i = 1; i <= q; i++) {
            scanf("%lld", &tt);
            if (tt == 0) {
                scanf("%lld%lld%lld", &x, &y, &v);
                update(x, y, v);
            } else {
                scanf("%lld%lld", &x, &y);
                printf("%lld\n", query(x, y));
            }
        }
    }
    return 0;
}
