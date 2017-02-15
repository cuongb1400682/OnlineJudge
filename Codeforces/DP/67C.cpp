/*
 * PROB: Codeforces - 67C - Sequence of Balls
 * LANG: C++
 */

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=int(a),n##i=int(b);i<=n##i;i++)
#define min3(a,b,c) min(a,min(b,c))
#define ms(f,a) memset(f,a,sizeof f)
#define SZ 4004
#define INF 0x3f3f3f3f

int ti,td,tr,te,f[SZ][SZ],n,m,ca[SZ][256],cb[SZ][256];
char a[SZ],b[SZ];

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt","rt",stdin);
    freopen("output.txt","wt",stdout);
#endif
    while(cin>>ti>>td>>tr>>te) {
        cin>>(a+1)>>(b+1);
        n=strlen(a+1),m=strlen(b+1);
        ms(f,0);
        rep(i,1,n) {
            f[i][0]=i*td;
            rep(c,'a','z')
                ca[i][c]=ca[i-1][c];
            ca[i][a[i]]=i;
        }
        rep(i,1,m) {
            f[0][i]=i*ti;
            rep(c,'a','z')
                cb[i][c]=cb[i-1][c];
            cb[i][b[i]]=i;
        }
        rep(i,1,n)rep(k,1,m) {
            f[i][k]=min3(f[i-1][k]+td,
                         f[i-1][k-1]+tr*(a[i]!=b[k]),
                         f[i][k-1]+ti);
            if(i>1&&k>1) {
                int ii=ca[i-1][b[k]];
                int kk=cb[k-1][a[i]];
                if(ii&&kk)
                    f[i][k]=min(f[i][k],
                                f[ii-1][kk-1]+te+(i-ii-1)*td+(k-kk-1)*ti);
            }
        }
        cout<<f[n][m]<<endl;
    }
    return 0;
}
