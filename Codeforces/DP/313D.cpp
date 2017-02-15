/*
 * PROB: Codeforces - 313D - Ilya and Roads
 * LANG: C++
 */

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=int(a),n##i=int(b);i<=n##i;i++)
#define ms(a,b) memset(a,b,sizeof a)
#define SZ 301
#define SS 10001
#define INF 0x3f3f3f3f3f3f3f3f

typedef long long ll;

int n,m,k;
ll f[SZ][SZ],d[SZ][SZ];

void readf() {
    int L,R,cost;
    cin>>n>>m>>k;
    ms(d,0x3f);
    rep(i,1,m) {
        cin>>L>>R>>cost;
        d[L][R]=min(d[L][R],(ll)cost);
    }
}

void init() {
    for(int i=n;i>=2;i--)
        for(int x=1,y=i;y<=n;x++,y++) {
            d[x][y-1]=min(d[x][y-1],d[x][y]);
            d[x+1][y]=min(d[x+1][y],d[x][y]);
        }
}

void solve() {
    ms(f,0x3f);
    f[0][0]=0;
    rep(i,1,n) {
        f[i][0]=0;
        rep(j,1,min(k,i)) {
            ll tt=f[i-1][j];
            rep(h,1,j)
                tt=min(tt,f[i-h][j-h]+d[i-h+1][i]);
            f[i][j]=tt;
        }
    }
}

void print() {
    ll ans=INF;
    rep(i,k,n) rep(j,k,i) ans=min(ans,f[i][j]);
    cout<<((ans!=INF)?ans:-1)<<endl;
}

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt","rt",stdin);
    freopen("output.txt","wt",stdout);
#endif
    readf();
    init();
    solve();
    print();
    return 0;
}
