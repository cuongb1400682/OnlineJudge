/*
 * PROB: Codeforces - 14E - Camels
 * LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

#define rp(i,a,b) \
    for (int i = int(a), n##i = int(b); i <= n##i; i++)

int n, t, f[70][6][20];

void pre_calc() {
    memset(f, 0, sizeof f);
    f[1][1][0] = f[1][2][0] = f[1][3][0] = 1;
    rp(i,2,4)rp(k,i,4)rp(h,i-1,k-1)
        f[i][k][0] += f[i-1][h][0];
}

int solve() {
    pre_calc();
    rp(b,1,2*t-1)
        rp(i,b+2,3*b+4)
            rp(h,1,4) {
                if (b&1) {
                    if (h<4) f[i][h][b] = f[i-1][4][b-1];
                    rp(H,h+1,3)
                        f[i][h][b] += f[i-1][H][b-1] + f[i-1][H][b];
                } else {
                    if (h>1) f[i][h][b] = f[i-1][1][b-1];
                    rp(H,2,h-1)
                        f[i][h][b] += f[i-1][H][b-1] + f[i-1][H][b];
                }
            }
    int ans = 0;
    rp(i,1,4)
        ans += f[n][i][2*t-1];
    return ans;
}

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif
    cin >> n >> t;
    int ans = 0;
    ans += solve();
    cout << ans;
    return 0;
}

