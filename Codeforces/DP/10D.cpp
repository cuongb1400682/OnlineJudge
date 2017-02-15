/*
 * PROB: Codeforces - 10D - LCIS
 * LANG: C++
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

#define INF 1000000000

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

vi a, b, L, P;
vii c;
int n, m;

bool operator<(ii i, ii k) {
    return i.first < k.first && i.second < k.second && a[i.first] < a[k.first];
}

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif
    cin >> n; a.resize(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    cin >> m; b.resize(m);
    for (int i = 0; i < m; i++) cin >> b[i];

    for (int i = 0; i < n; i++)
        for (int k = 0; k < m; k++)
            if (a[i] == b[k]) c.push_back(ii(i, k));

    if (c.empty()) {
        printf("0");
        return 0;
    }

    int n_c = (int)c.size(), ans, ans_val;
    ans_val = 1, ans = 0;
    L.assign(n_c, 1), P.assign(n_c, -1);
    for (int i = 0; i < n_c; i++) {
        int val = 1, pos = -1;
        for (int k = 0; k < i; k++)
            if (c[k] < c[i] && val < L[k]+1) {
                val = L[k]+1;
                pos = k;
            }
        if (pos > -1) {
            L[i] = val;
            P[i] = pos;
            if (ans_val < L[i]) {
                ans_val = L[i];
                ans = i;
            }
        }
    }

    printf("%d\n", L[ans]);
    vi ret;
    ret.clear();
    for (int i = ans; i >= 0; i = P[i])
        ret.push_back(a[c[i].first]);
    reverse(ret.begin(), ret.end());
    ostream_iterator<int> out_it(cout, " ");
    copy(ret.begin(), ret.end(), out_it);
    return 0;
}

/*
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
using namespace std;

#define SZ 500

typedef vector<int> vi;

vi a(SZ), b(SZ), L(SZ), P(SZ, -1);
int n, m;

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    cin >> m;
    for (int i = 0; i < m; i++) cin >> b[i];

    for (int i = 0; i < n; i++) {
        int id = -1, len = 0;
        for (int j = 0; j < m; j++) {
            if (a[i] == b[j] && L[j] < len+1)
                L[j] = len+1, P[j] = id;
            if (a[i] > b[j] && len < L[j])
                len = L[j], id = j;
        }
    }

    int id = -1, len = 0;
    for (int i = 0; i < m; i++)
        if (len < L[i])
            len = L[i], id = i;
    vi ret;
    for (; id >= 0; id = P[id])
        ret.push_back(b[id]);
    reverse(ret.begin(), ret.end());
    cout << ret.size() << endl;
    copy(ret.begin(), ret.end(), ostream_iterator<int>(cout, " "));
    return 0;
}
*/
