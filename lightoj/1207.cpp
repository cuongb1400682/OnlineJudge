#include <bits/stdc++.h>
using namespace std;
 
#define debug(x) cerr << #x " = " << (x) << '\n'
#define arr(x, n) {cerr<<#x<<" = "<<"["<<(n)<<"]"<<"(";for(ll _=0;_<(n);_++) cerr<<(x)[_]<<(_!=(n)-1?", ":")\n");}
#define iarr(x, m, n) {cerr<<#x":\n";for(ll _=(m);_<=(n);_++) cerr<<_<<": "<<(x)[_]<<'\n';}
#define err(...) fprintf(stderr, __VA_ARGS__)
#define SZ 200005
 
typedef long long ll;
 
struct Segment {
    int x, y;
    Segment(int _x = 0, int _y = 0):
        x(_x), y(_y) { }
};
 
int t, n, st[8 * SZ];
vector<Segment> seg;
bitset<2 * SZ> vis;
 
void update(int p, int L, int R, int u, int v, int clr) {
    if (v < L || R < u)
        return;
    if (u <= L && R <= v) {
        st[p] = clr;
        return;
    }
    if (st[p] != 0) {
        st[2 * p] = st[p];
        st[2 * p + 1] = st[p];
        st[p] = 0;
    }
    int mid = (L + R) >> 1;
    update(2 * p, L, mid, u, v, clr);
    update(2 * p + 1, mid + 1, R, u, v, clr);
}
 
int query(int p, int L, int R, int u) {
    if (L == R)
        return st[p];
    if (st[p] != 0) {
        st[2 * p] = st[p];
        st[2 * p + 1] = st[p];
        st[p] = 0;
    }
    int mid = (L + R) >> 1;
    if (u <= mid)
        return query(2 * p, L, mid, u);
    else
        return query(2 * p + 1, mid + 1, R, u);
}
 
int main() {
    scanf("%d", &t);
    for (int no = 1; no <= t; no++) {
        scanf("%d", &n);
        memset(st, 0, sizeof(st));
       
        int max_uv = 0;
        seg.clear();
        for (int i = 1; i <= n; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            max_uv = max(max_uv, max(u, v));
            seg.push_back(Segment(u, v));
        }
       
        for (int i = 0; i < seg.size(); i++) {
            update(1, 1, max_uv, seg[i].x, seg[i].y, i + 1);
        }
 
        vis.reset();
        int ans = 0;
        for (int i = 1; i <= max_uv; i++) {
            int clr = query(1, 1, max_uv, i);
            if (clr != 0 && not vis[clr]) {
                vis[clr] = true;
                ++ans;
            }
        }
        printf("Case %d: %d\n", no, ans);
    }
    return 0;
}
 
