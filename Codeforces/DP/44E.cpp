/*
 * PROB: Codeforces -  44E - Anfisa the Monkey
 * LANG: C++
 */

#include <bits/stdc++.h>
using namespace std;

#define SZ 201

int f[SZ][SZ], a, b, k, n;
char s[SZ];

int calc(int n, int k) {
    if (n <= 0 || k <= 0 || b*k < n)
        return -1;
    if (f[n][k] != -1)
        return f[n][k];
    for (int l = a; l <= b; l++)
        if (calc(n-l, k-1) != -1) {
            f[n][k] = n-l;
            break;
        }
    return f[n][k];
}

void solve() {
    memset(f, -1, sizeof f);
    for (int i = a; i <= b; i++)
        f[i][1] = 0;
    n = strlen(s+1);
    if (n >= k) calc(n, k);
}

void print() {
    int i = n, j = k;
    char nul = '\0';
    vector<char *> res;
    res.push_back(NULL);

    if (f[i][k] == -1)
        return (void)puts("No solution");

    while (i && j) {
        int L = i-f[i][j];
        res.push_back(s+i-L+1);
        i = f[i][j], j--;
    }

    for (i = (int)res.size()-1; i >= 1; i--) {
        if (res[i-1]) swap(*res[i-1], nul);
        puts(res[i]);
        if (res[i-1]) swap(*res[i-1], nul);
    }
}

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif
    scanf("%d%d%d%200s", &k, &a, &b, s+1);
    solve();
    print();
    return 0;
}
