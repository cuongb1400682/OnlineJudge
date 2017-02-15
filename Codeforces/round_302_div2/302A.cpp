/*
 * PROB: Codeforces - 302A - Set of Strings
 * LANG: C++
 */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int k;
char ln[256];
vector<char *> P;
bool vis[256];

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif
    scanf("%d%100s", &k, ln);

    for (char *p = ln; *p; p++)
        if (!vis[(int)*p]) {
            vis[(int)*p] = true;
            P.push_back(p);
        }
    P.push_back(ln+255);

    if ((int)P.size() < k+1)
        puts("NO");
    else {
        puts("YES");
        char nul = '\0';
        for (int i = 0; i < k; i++) {
            if (i < k-1) swap(nul, *P[i+1]);
            puts(P[i]);
            if (i < k-1) swap(nul, *P[i+1]);
        }
    }
    return 0;
}
