/*
 * PROB: Codeforces - 392B - Tower of Hanoi
 * LANG: C++
 */

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=int(a),n##i=int(b);i<=n##i;i++)
#define ms(f,v) memset(f,v,sizeof f)
#define INF 0x3f3f3f3f

typedef long long ll;

ll c[4][4],n,f[41][4][4];

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt","rt",stdin);
    freopen("output.txt","wt",stdout);
#endif
    rep(i,1,3) rep(k,1,3) cin>>c[i][k];
    cin>>n;
    ms(f,0);
    rep(a,1,3) rep(b,1,3) if (a!=b) {
        int m=6-(a+b);
        f[1][a][b]=min(c[a][b],c[a][m]+c[m][b]);
    }

    rep(i,2,n) rep(a,1,3) rep(b,1,3) if(a!=b) {
        int o=6-(a+b);
        ll p1=c[a][o]+f[i-1][b][a]+c[o][b]+min(f[i-1][a][b],f[i-1][a][o]+f[i-1][o][b])*2;
        ll p2=c[a][b]+min(f[i-1][a][b]+f[i-1][b][o],f[i-1][a][o])+
                       min(f[i-1][o][a]+f[i-1][a][b],f[i-1][o][b]);
        f[i][a][b]=min(p1,p2);
    }
    cout<<f[n][1][3]<<endl;
    return 0;
}
