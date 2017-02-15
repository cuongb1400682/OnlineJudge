#include <bits/stdc++.h>
using namespace std;

#define SZ 100005

typedef long long ll;

struct Node {
    ll lazy, sum[3];
    Node() {
        lazy = sum[0] = sum[1] = sum[2] = 0;
    }
    ll& operator[](ll i) {
        return sum[i];
    }
    void roll(int n = 1) {
        n %= 3;
        ll tmp;
        while (n-- > 0) {
            tmp = sum[2];
            sum[2] = sum[1];
            sum[1] = sum[0];
            sum[0] = tmp;
        }
    }
};

Node st[SZ * 4];
ll n, q;

void create(ll p, ll L, ll R) {
    st[p] = Node();
    if (L == R) {
        st[p][0] = 1;
        return;
    }
    create(2*p, L, (L+R)/2);
    create(2*p+1,(L+R)/2+1, R);
    st[p][0] = st[2*p][0] + st[2*p+1][0];
}

void propagate(ll p, ll L, ll R) {
    if (st[p].lazy != 0) {
        ll lazy = st[p].lazy;
        ll rLen = (R - L + 1) / 2;
        ll lLen = rLen + ((R - L + 1) & 1);
        st[p].lazy = 0;

        st[2*p].lazy += lazy;
        st[2*p].roll(lazy);

        st[2*p+1].lazy += lazy;
        st[2*p+1].roll(lazy);
    }
}

void update(ll p, ll L, ll R, ll u, ll v) {
    if (v < L || R < u) return;
    if (u <= L && R <= v) {
        st[p].lazy++;
        st[p].roll();
        return;
    }
    propagate(p, L, R);
    update(2*p, L, (L+R)/2, u, v);
    update(2*p+1, (L+R)/2+1, R, u, v);
    for (ll i = 0; i <= 2; i++)
        st[p][i] = st[2*p][i] + st[2*p+1][i];
}

ll query(ll p, ll L, ll R, ll u, ll v) {
    if (v < L || R < u) return 0;
    if (u <= L && R <= v) return st[p][0];
    propagate(p, L, R);
    ll lAns = query(2*p, L, (L+R)/2, u, v);
    ll rAns = query(2*p+1, (L+R)/2+1, R, u, v);
    return lAns + rAns;
}

int main(void) {
    freopen("input.txt", "rt", stdin);
    ll nCase, t, u, v;
    scanf("%lld", &nCase);
    for (ll caseNo = 1; caseNo <= nCase; caseNo++) {
        scanf("%lld%lld", &n, &q);
        create(1, 0, n - 1);
        printf("Case %lld:\n", caseNo);
        for (ll i = 1; i <= q; i++) {
            scanf("%lld%lld%lld", &t, &u, &v);
            if (t == 0) {
                update(1, 0, n - 1, u, v);
            } else {
                printf("%lld\n", query(1, 0, n - 1, u, v));
            }
        }
    }
    return 0;
}
