/*
 * PROB: Codeforces - 234F - Fence
 * LANG: C++
 */

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=int(a),n##i=int(b);i<=n##i;i++)
#define ms(f,v) memset(f,v,sizeof f)
#define INF 0x3f3f3f3f

int n,a,b,h,ph,ans,f[2][40001][2],S;

inline void upd(int& a,int b) { if(a>b) a=b; }

int main(void) {
    // input & output through text files
    freopen("input.txt","rt",stdin);
    freopen("output.txt","wt",stdout);
    while(~scanf("%d%d%d",&n,&a,&b)) {
        ms(f,0x3f);
        f[0][0][0]=f[0][0][1]=0;
        S=ph=0;
        rep(i,1,n) {
            scanf("%d",&h);
            S+=h;
            rep(j,max(S-b,h),min(a,S))
                upd(f[i&1][j][0],min(f[(i-1)&1][j-h][0],f[(i-1)&1][j-h][1]+min(h,ph)));
            rep(j,max(S-b,0),min(a,S))
                upd(f[i&1][j][1],min(f[(i-1)&1][j][1],f[(i-1)&1][j][0]+min(h,ph)));
            ms(f[(i-1)&1],0x3f);
            ph=h;
        }
        ans=INF;
        rep(j,max(S-b,0),a) upd(ans,min(f[n&1][j][0],f[n&1][j][1]));
        printf("%d\n",ans!=INF?ans:-1);
    }
    return 0;
}

