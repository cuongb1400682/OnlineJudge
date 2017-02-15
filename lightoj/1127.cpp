#include <bits/stdc++.h>
using namespace std;

#define dbg(x) cerr << "[" #x " = " << x << "]" << endl
template<class T>
void __dba(const T* a, int n) {
    cerr << "[";
    for (int i = 0; i < n; i++)
        cerr << (i > 0 ? ", " : "" ) << a[i];
    cerr << "]" << endl;
}
#define dba(a, n) { cerr << #a " = "; __dba(a, n); }

#define SZ 512
typedef long long ll;

ll n, K, a[SZ], L1[40000], L2[40000], nL1, nL2;

void makeList(ll pos, ll end, ll x, ll *L, ll &nL) {
    ll len = end - pos;
    ll lim = (1 << len) - 1;
    
    nL = 0;
    if (len == 0) return;
    for (ll state = 0; state <= lim; state++) {
        ll elm = 0;
        for (ll i = 0; i < len; i++)
            if (state & (1 << i))
                elm += a[i + pos];
        L[nL++] = elm;
    }
}

ll solve() {
    nL1 = nL2 = 0;
    makeList(0, n/2, 0, L1, nL1);
    makeList(n/2, n, 0, L2, nL2);

    if (nL1 == 0)
        L1[nL1++] = 0;

    sort(L2, L2 + nL2);

    L2[nL2++] = LLONG_MAX;
    ll ans = 0;
    for (ll i = 0, *p; i < nL1; i++) {  
        p = upper_bound(L2, L2 + nL2, K - L1[i]);
	if (*p > K - L1[i])
	    ans += p - L2;
	else
	    ans += p - L2 + 1;
    }
    return ans;
}

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
#endif
    ll nCase;
    scanf("%lld", &nCase);
    for (ll no = 1; no <= nCase; no++) {
        scanf("%lld%lld", &n, &K);
        for (ll i = 0; i < n; i++)
            scanf("%lld", &a[i]);
        printf("Case %lld: %lld\n", no, solve());
    }
    return 0;
}
