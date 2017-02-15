#include <bits/stdc++.h>
using namespace std;

#define SZ 250001
#define INF 0x3f3f3f3fLL

typedef long long ll;

class Console {
public:
    static void read(char *s) {
        while (isspace(*s = getchar()))
            ;
        s++;
        while (!isspace(*s++ = getchar()))
            ;
        *--s = '\0';
    }

    static long long readLongLong() {
        int chr = -1, prev_chr = 0;
        long long ans;
        while (!isdigit(chr = getchar()))
            prev_chr = chr;
        ans = chr - '0';
        while (isdigit(chr = getchar()))
            ans = ans * 10LL + chr - 48;
        return ans * (prev_chr == '-' ? -1 : 1);
    }

    static void write(long long x) {
        int stk[20], top;
		
        if (x == 0LL) {
            putchar('0');
            return;
        }

        top = -1;
        if (x < 0) {
            putchar('-');
            stk[++top] = abs(x % 10);
            x /= 10;
            x = -x;
        }
		
        while (x > 0) {
            stk[++top] = x % 10LL;
            x /= 10LL;
        }
		
        while (top >= 0) 
            putchar(stk[top--] + '0');
    }

    static void write(const char *s) {
        while (*s)
            putchar(*s++);
    }

    static void writeLine(long long x) {
        write(x);
        putchar('\n');
    }
};

struct Node {
    ll a, aD, b, bD, c, sum;
    Node() {
        a = 0;
        b = 0;
        aD = 0;
        bD = 0;
        c = INF;
        sum = 0;
    }
};

Node st[4 * SZ];

ll sum(ll n) {
    return (ll) n * (n + 1) / 2;
}

ll calc_sum(ll cover, ll delta, ll len) {
    return (ll) cover * sum(len) + delta * len;
}

void init(ll p, ll L, ll R) {
    st[p] = Node();
    if (L == R)
        return;
    ll mid = (L + R) >> 1;
    init(2 * p, L, mid);
    init(2 * p + 1, mid + 1, R);
}

void propagate(ll p, ll L, ll R) {
    if (L == R) return;

    ll rightLen = (R - L + 1) >> 1;
    ll leftLen = rightLen + ((R - L + 1) & 1);
	
    if (st[p].c != INF) {
        st[2 * p] = Node();
        st[2 * p].c = st[p].c;
        st[2 * p].sum = st[p].c * leftLen;

        st[2 * p + 1] = Node();
        st[2 * p + 1].c = st[p].c;
        st[2 * p + 1].sum = st[p].c * rightLen;

        st[p].c = INF;
    }

    if (st[p].a != 0) {
        st[2 * p].a += st[p].a;
        st[2 * p].aD += st[p].aD;
        st[2 * p].sum += calc_sum(st[p].a, st[p].aD, leftLen);

        ll tmp = st[p].aD + leftLen * st[p].a;
        st[2 * p + 1].a += st[p].a;
        st[2 * p + 1].aD += tmp;
        st[2 * p + 1].sum += calc_sum(st[p].a, tmp, rightLen);

        st[p].a = 0;
        st[p].aD = 0;
    }

    if (st[p].b != 0) {
        ll tmp = st[p].bD + rightLen * st[p].b;
        st[2 * p].b += st[p].b;
        st[2 * p].bD += tmp;
        st[2 * p].sum += calc_sum(st[p].b, tmp, leftLen);

        st[2 * p + 1].b += st[p].b;
        st[2 * p + 1].bD += st[p].bD;
        st[2 * p + 1].sum += calc_sum(st[p].b, st[p].bD, rightLen);

        st[p].b = 0;
        st[p].bD = 0;
    }	
}

void update(ll p, ll L, ll R, ll u, ll v, char type, ll val = 0) {
    if (v < L || R < u)
        return;
    if (u <= L && R <= v) {
        if (type == 'C') {
            st[p] = Node();
            st[p].c = val;
            st[p].sum = val * (R - L + 1);
        } else if (type == 'A') {
            st[p].a++;
            st[p].aD += L - u;
            st[p].sum += calc_sum(1, L - u, R - L + 1);
        } else if (type == 'B') {
            st[p].b++;
            st[p].bD += v - R;
            st[p].sum += calc_sum(1, v - R, R - L + 1);
        }
        return;
    }
    propagate(p, L, R);
    ll mid = (L + R) >> 1;
    update(2 * p, L, mid, u, v, type, val);
    update(2 * p + 1, mid + 1, R, u, v, type, val);
    st[p].sum = st[2 * p].sum + st[2 * p + 1].sum;
}

ll query(ll p, ll L, ll R, ll u, ll v) {
    if (v < L || R < u)
        return 0;
    if (u <= L && R <= v)
        return st[p].sum;
    propagate(p, L, R);
    ll mid = (L + R) >> 1;
    return query(2 * p, L, mid, u, v) +
            query(2 * p + 1, mid + 1, R, u, v);
}

int main() {
    ll t, n, st, nd, x;
    char type[2];

    t = Console::readLongLong();
    for (ll no = 1; no <= t; no++) {
        init(1, 1, SZ - 1);

        Console::write("Case ");
        Console::write(no);
        Console::write(":\n");
		
        n = Console::readLongLong();
		
        for (ll i = 1; i <= n; i++) {
            Console::read(type);
            st = Console::readLongLong();
            nd = Console::readLongLong();
			
            if (*type == 'S') {
                Console::writeLine(query(1, 1, SZ - 1, st, nd));
            } else {
                if (*type == 'C') 
                    x = Console::readLongLong();
                else
                    x = 0;
                update(1, 1, SZ - 1, st, nd, *type, x);
            }
        }
    }
    return 0;
}
