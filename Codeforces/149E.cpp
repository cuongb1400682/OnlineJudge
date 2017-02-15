/*
 * PROB: Codeforces - 149E. Martian Strings
 * LANG: C++
 * TAGS: string suffix structures kmp
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAX_T 200001
#define MAX_P 2001

char P[MAX_P], T[MAX_T];
int back[MAX_P], a[MAX_T], b[MAX_T], n, m;

void pre_kmp() {
    int i = 0, j = -1;
    back[0] = -1;
    while (i < m) {
        while (j >= 0 && P[i] != P[j])
            j = back[j];
        i++, j++;
        back[i] = j;
    }
}

void calc(int *a) {
    pre_kmp();
    int i = 0, j = 0;
    while (i < n) {
        while (j >= 0 && T[i] != P[j])
            j = back[j];
        j++, a[i] = j, i++;
        if (j == m)
            j = back[j];
    }
}

int solve() {
    if (m < 2) return 0;
    reverse(P, P + m), reverse(T, T + n), calc(a);
    reverse(P, P + m), reverse(T, T + n), calc(b);
    for (int i = 1; i < n; i++) {
        a[i] = max(a[i], a[i - 1]);
        b[i] = max(b[i], b[i - 1]);
    }
    reverse(a, a + n);
    for (int i = 0; i < n; i++)
        if (a[i + 1] + b[i] >= m)
            return 1;
    return 0;
}

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int n_case, ans;
    scanf("%s", T);
    scanf("%d", &n_case);
    ans = 0;
    while (n_case--) {
        scanf("%s", P);
        n = strlen(T), m = strlen(P);
        ans += solve();
    }
    printf("%d\n", ans);
    return 0;
}
