/*
 * PROB: Codeforces - 176B - Word Cut
 * LANG: C++
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

#define rp(i, a, b) \
    for(int i = int(a), n##i = int(b); i <= n##i; i++)
#define MOD 1000000007

typedef long long ll;

string x, y, s;
int k, good, bad;
ll G, B;

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif
    cin >> x >> y >> k;
    s = x+x;
    rp(i, 0, x.size()-1)
        if (s.compare(i, y.size(), y) == 0)
            good++;
    bad = x.size() - good;
    G = 0, B = 1;
    if (x == y)
        G = 1, B = 0;
    rp(i, 1, k) {
        ll _G = (G * (good - 1) + B * good) % MOD;
        ll _B = (G * bad + B * (bad - 1)) % MOD;
        G = _G, B = _B;
    }
    cout << G << endl;
    return 0;
}
