/*
 * PROB: SPOJ - CLOPPAIR - Closest Point Pair
 * LANG: C++
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

#define INF 1000000000

struct point {
    double x, y;
    int idx;
    point(double _x = 0, double _y = 0, int _idx = 0) : x(_x), y(_y), idx(_idx) { }
};

typedef vector<point> vp;
typedef pair<int, int> ii;

vp P;

void readf() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        point p;
        scanf("%lf %lf", &p.x, &p.y);
        p.idx = i;
        P.push_back(p);
    }
}

double dist(point a, point b) {
    return hypot(a.x - b.x, a.y - b.y);
}

double brute_force(int L, int R, vp& P, ii& p) {
    double ans = INF;
    for (int i = L; i <= R-1; i++)
        for (int k = i+1; k <= R; k++)
            if (dist(P[i], P[k]) < ans) {
                ans = dist(P[i], P[k]);
                p = ii(P[i].idx, P[k].idx);
            }
    return ans;
}

bool cmp_x(point a, point b) { return a.x < b.x; }

bool cmp_y(point a, point b) { return a.y < b.y; }

double strip_util(vp& P, ii& p, double d) {
    int n = P.size();
    sort(P.begin(), P.end(), cmp_y);
    double ans = d;
    for (int i = 0; i < n-1; i++)
        for (int k = i+1; k < n; k++) {
            if (dist(P[i], P[k]) > ans)
                break;
            else {
                ans = dist(P[i], P[k]);
                p = ii(P[i].idx, P[k].idx);
            }
        }
    return ans;
}

double closest_pair(int L, int R, vp& P, ii& p) {
    if (R-L+1 <= 3) return brute_force(L, R, P, p);
    int M = (L + R) / 2;
    ii pL, pR;
    double dL = closest_pair(L, M, P, pL);
    double dR = closest_pair(M+1, R, P, pR);
    double d = dL;
    p = pL;
    if (d > dR)
        d = dR, p = pR;
    vp Q;

    for (int i = L; i <= R; i++)
        if (fabs(P[i].x - P[M].x) <= d)
            Q.push_back(P[i]);

    ii tmp_p;
    double tmp_d = strip_util(Q, tmp_p, d);
    if (tmp_d < d) {
        d = tmp_d;
        p = tmp_p;
    }
    return d;
}

void print() {
    ii p;
    sort(P.begin(), P.end(), cmp_x);
    double d = closest_pair(0, P.size()-1, P, p);
    if (p.first > p.second) swap(p.first, p.second);
    printf("%d %d %.6lf\n", p.first, p.second, d);
}

int main(void) {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    readf();
    print();
    return 0;
}
