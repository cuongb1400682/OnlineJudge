/*
 * PROB: Codeforces - 204E. Little Elephant and Strings
 * LANG: C++
 * TAGS: data structures implementation string suffix structures 2-pts
 * BUGS: haven't been done
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <string>
using namespace std;

typedef pair<int, int> ii;
typedef set<ii> sii;

#define SZ 100001
#define INF 1000000009
#define DEBUG if (1)

char T[2*SZ], P[SZ];
int lT, lP, SA[2*SZ], RA[2*SZ], tSA[2*SZ], tRA[2*SZ], c[301], n, m, start;
sii f;

void sa_sort(int k) {
    int maxi = max(300, k);
    memset(c, 0, sizeof c);
    for (int i = 0; i < lT; i++) c[i+k < lT ? RA[i+k] : 0]++;
    int t, sum = 0;
    for (int i = 0; i < maxi; i++)
        t = c[i], c[i] = sum, sum += t;
    for (int i = 0; i < lT; i++)
        tSA[c[SA[i]+k < lT ? RA[SA[i]+k] : 0]++] = SA[i];
    memcpy(SA, tSA, lT * sizeof SA[0]);
}

void sa_create() {
    lT = strlen(T), lP = strlen(P);
    for (int i = 0; i < lT; i++)
        RA[i] = T[i] - '.', SA[i] = i;
    for (int k = 1; k <= lT; k <<= 1) {
        sa_sort(k);
        sa_sort(0);
        int r = 0;
        for (int i = 0; i < lT; i++)
            tRA[SA[i]] = (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r : ++r;
        memcpy(RA, tRA, lT * sizeof RA[0]);
        if (RA[lT-1] == lT-1) break;
    }
}

ii sa_find(const char *s, int len) {
    int lo = start, hi = lT - 1;
    while (lo < hi) {
        int mi = (lo + hi) / 2;
        int ret = strncmp(T+SA[mi], s, len);
        if (ret >= 0)
            hi = mi;
        else
            lo = mi+1;
    }
    if (strncmp(T+SA[lo], s, len) != 0) return ii(-1, -1);
    ii ans(lo, -1);

    lo = start, hi = lT - 1;
    while (lo < hi) {
        int mi = (lo + hi) / 2;
        int ret = strncmp(T+SA[mi], s, len);
        if (ret > 0)
            hi = mi;
        else
            lo = mi+1;
    }
    if (strncmp(T+SA[lo+1], s, len) != 0)
        hi--;
    ans.second = hi;
    return ans;
}

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    start = 1;
    for (int i = 0; i < n; i++) {
        scanf("%s", P);
        strcat(T, ".");
        strcat(T, P);
        start++;
    }
    strcat(T, ".");
    sa_create();

    char *p, *t;
    for (p = strpbrk(T, "."); p; p = t) {
        t = strpbrk(p+1, ".");
        if (!t) break;
        int len = t - p, ans = 0;
        f.clear();
        for (int i = 1; i <= len-1; i++) {
            for (int k = 1; k <= len-i; k++) {
                ii ret = sa_find(&p[k], i);
                if (f.count(ret) == 0) {
                    if (ret.second-ret.first+1>=m)
                        ans++;
                    f.insert(ret);
                }
            }
        }
        printf("%d ", ans);
    }
    return 0;
}
