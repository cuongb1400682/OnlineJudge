#include <bits/stdc++.h>
using namespace std;

#define TR(it,c) for(__typeof((c).begin()) it=(c).begin();it!=(c).end();it++)
#define ms(f,a)  memset(f,a,sizeof(f))
#define LINF     0x3f3f3f3f3f3f3f3fLL

#define DBS(s) cerr << "["  #s << "]" << endl
#define DBG(S) cerr << "[" #S " = " << (S) << "]" << endl
#define DBL    cerr << endl

#define fi first
#define se second
#define pb push_back

typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef vector<ll> vll;

struct triple {
    triple(ll _total = 0, ll _left = 0, ll _right = 0, ll _sum = 0) :
            total(_total), left(_left), right(_right), sum(_sum) {
    }
    ll total, left, right, sum;
};

class bit_t {
private:
    vector<ll> ft;
public:
    bit_t(ll N = -1) {
        ft.assign(N + 1, 0LL);
    }

    template<class IterType>
    bit_t(IterType b, IterType e) {
        ll N = distance(b, e) + 1;
        ft.assign(N + 1, 0ll);
        ll pos = 1;
        for (IterType it = b; it != e; it++) {
            adjust(pos, *it);
            pos++;
        }
    }

    void adjust(ll pos, ll val) {
        pos++;
        for (ll i = pos; i < (ll) ft.size(); i += i & -i)
            ft[i] += val;
    }

    ll query(ll L, ll R) {
        return (*this)[R] - (*this)[L - 1];
    }

    ll operator[](ll idx) const {
        ll ans = 0LL;
        if (idx < -1)
            idx = -1;
        for (idx++; idx; idx -= idx & -idx)
            ans += ft[idx];
        return ans;
    }

    ll size() const {
        return ft.size() - 1;
    }
};

class segtree_t {
public:
    segtree_t() {
    }

    template<class ArrayType>
    segtree_t(const ArrayType& a) {
        n = a.size();
        st.assign(4 * n, triple());
        init(1, 0, n - 1, a);
    }

    void update(ll index, ll value) {
        update(1, 0, n - 1, index, value);
    }

    ll query(ll u, ll v) {
        return query(1, 0, n - 1, u, v).total;
    }

private:
    ll left(ll p) {
        return p << 1;
    }
    ll right(ll p) {
        return (p << 1) + 1;
    }

    triple newTriple(triple leftSeg, triple rightSeg) {
        triple ans;
        ans.left = max(leftSeg.left, leftSeg.sum + rightSeg.left);
        ans.right = max(rightSeg.right, rightSeg.sum + leftSeg.right);
        ans.total = max(max(leftSeg.total, rightSeg.total),
                leftSeg.right + rightSeg.left);
        ans.sum = leftSeg.sum + rightSeg.sum;
        return ans;
    }

    template<class ArrayType>
    triple init(ll p, ll L, ll R, const ArrayType& a) {
        if (L == R)
            return st[p] = triple(a[L], a[L], a[L], a[L]);
        return st[p] = newTriple(init(left(p), L, (L + R) / 2, a),
                init(right(p), (L + R) / 2 + 1, R, a));
    }

    // 1 point updating
    triple update(ll p, ll L, ll R, ll node, ll val) {
        if (node < L || node > R)
            return st[p];
        if (L == R && L == node)
            return st[p] = triple(val, val, val, val);
        return st[p] = newTriple(update(left(p), L, (L + R) / 2, node, val),
                update(right(p), (L + R) / 2 + 1, R, node, val));
    }

    triple query(ll p, ll L, ll R, ll u, ll v) {
        if (v < L || R < u)
            return triple(-LINF, -LINF, -LINF, -LINF);
        if (u <= L && R <= v)
            return st[p];

        triple leftSeg = query(left(p), L, (L + R) / 2, u, v);
        triple rightSeg = query(right(p), (L + R) / 2 + 1, R, u, v);

        if (leftSeg.sum == -LINF)
            return rightSeg;
        else if (rightSeg.sum == -LINF)
            return leftSeg;
        else
            return newTriple(leftSeg, rightSeg);
    }

    vector<triple> st;
    ll n;
};

segtree_t s;
bit_t cost;
ll h[500005], N, Q;
vector<ll> fun;

ll get_fun(ll h1, ll h2) {
    return (h1 - h2) * (h1 - h2) * (h1 < h2 ? -1 : 1);
}

ll new_cost(ll i, ll h1, ll h2) {
    ll new_c = h1 + h2;
    ll old_c = h[i - 1] + h[i];
    ll diff = new_c - old_c;
    return diff;
}

ll find_p(ll x, ll k) {
    if (x >= N)
        return N;
    ll L = x, R = N, ans = x;
    while (L <= R) {
        ll M = (L + R) >> 1;
        if (cost.query(x, M) <= k) {
            ans = M;
            L = M + 1;
        } else
            R = M - 1;
    }
    return ans;
}

int main(void) {
    scanf("%lld %lld", &N, &Q);
    cost = bit_t(N + 1);
    fun.assign(N + 1, 0);
    for (ll i = 0; i <= N; i++) {
        scanf("%lld", &h[i]);
        if (i >= 1) {
            cost.adjust(i, h[i] + h[i - 1]);
            fun[i] = get_fun(h[i - 1], h[i]);
        }
    }
    s = segtree_t(fun);

    ll i, V, X;
    ll K;

    for (ll type; Q--;) {
        scanf("%lld", &type);
        if (type == 0) {
            scanf("%lld %lld", &i, &V);
            if (i > 0) {
                cost.adjust(i, new_cost(i, h[i - 1], V));
                fun[i] = get_fun(h[i - 1], V);
                s.update(i, fun[i]);
            }
            if (i < N) {
                cost.adjust(i + 1, new_cost(i + 1, V, h[i + 1]));
                fun[i] = get_fun(V, h[i + 1]);
                s.update(i + 1, fun[i]);
            }
            h[i] = V;
        } else {
            scanf("%lld %lld", &X, &K);
            ll p = find_p(X + 1, K);
            printf("%lld\n", s.query(0, p));
        }
    }
    return 0;
}

