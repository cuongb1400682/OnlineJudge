/*
 * PROB: Codeforces - 268D - Wall Bars
 * LANG: C++
 */

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=int(a),n##i=int(b);i<=n##i;i++)
#define ms(f,a) memset(f,a,sizeof f)
#define pb(x) push_back(x)
#define MOD 1000000009
#define INF 0x3f3f3f3f
#define SZ  2

int n,h,f[SZ][2][31][31][31];

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt","rt",stdin);
    freopen("output.txt","wt",stdout);
#endif
    while(cin>>n>>h) {
        ms(f,0);
        f[0][1][0][0][0]=1;
        rep(i,0,n) {
            ms(f[1-(i&1)],0);
            rep(a,0,h)rep(b,0,h)rep(c,0,h)
                rep(k,0,1) {
                    int z=i&1,v=f[z][k][a][b][c],d=k?1:h;
                    if(v==0) continue;
                    (f[1-z][a<h][min(b+1,h)][min(c+1,h)][d]+=v)%=MOD; // direction a
                    (f[1-z][b<h][min(a+1,h)][min(c+1,h)][d]+=v)%=MOD; // direction b
                    (f[1-z][c<h][min(a+1,h)][min(b+1,h)][d]+=v)%=MOD; // direction c
                    (f[1-z][k][min(a+1,h)][min(b+1,h)][min(c+1,h)]+=v)%=MOD;
                }
        }
        int ans=0;
        rep(a,0,h)rep(b,0,h)rep(c,0,h)rep(k,0,1)
            if(a<h||b<h||c<h||k) (ans+=f[n&1][k][a][b][c])%=MOD;
        cout<<ans<<endl;
    }
    return 0;
}
