/*
 * PROB: Codeforces - 500C. New Year Book Reading
 * LANG: C++
 */

#include <cstdio>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

typedef vector<int> vi;
typedef long long ll;
#define REP(i, a, b) \
    for (int i = int(a); i <= int(b); i++)
#define DEBUG if (1)

int n, m, b;
ll ans, tweight;
vi w;
list<int> q;
bool in_list[1024];

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    w.resize(n + 1);
    REP(i, 1, n) scanf("%d", &w[i]);
    ans = 0;
    REP(i, 1, m) {
        scanf("%d", &b);
        if (in_list[b]) {
            list<int>::iterator lim, it;
            int sum = 0;
            lim = find(q.begin(), q.end(), b);
            for (it = q.begin(); it != lim; it++)
                sum += w[*it];
            ans += sum;
            q.push_front(*lim);
            q.erase(lim);
        } else {
            ans += tweight;
            q.push_front(b);
            tweight += w[b];
            in_list[b] = true;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
