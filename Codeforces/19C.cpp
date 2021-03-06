/*
 * PROB: Codeforces - 19C. Deletion of Repeats
 * LANG: C++
 * TAGS: string suffix structures gready
 */

#include <cstdio>
#include <cstring>
#include <map>
using namespace std;

#define SZ 100001
#define INF 1000000000

typedef map<int, int> mii;

int n, a[SZ], start, prev[SZ];
mii f;

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        prev[i] = -1;
        if (f.count(a[i]))
            prev[i] = f[a[i]];
        f[a[i]] = i;
    }

    for (int i = start = 0; i < n; i++) {
        int min_len = INF, pos = -1;
        for (int k = prev[i]; k > -1 && k >= start; k = prev[k]) {
            if (i-k >= min_len) break;
            int m;
            for (m = 0; m < i-k; m++)
                if (a[i+m] != a[k+m] || i+m >= n) break;
            if (m == i-k && min_len > m)
                min_len = m, pos = i;
        }
        if (pos != -1)
            start = max(start, pos);
    }

    printf("%d\n", n - start);
    for (int i = start; i < n; i++)
        printf("%d%s", a[i], i == n - 1 ? "\n" : " ");
    return 0;
}
