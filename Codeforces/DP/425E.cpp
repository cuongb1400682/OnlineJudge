/*
 * PROB: Codeforces - 425E - Sereja and Sets
 * LANG: C++
 */

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=int(a),n##i=int(b);i<=n##i;i++)
#define ms(f,a) memset(f,a,sizeof f)
#define M 1000000007
#define SZ 550

typedef long long ll;

int N,K,f[SZ][SZ],p[SZ*SZ];

int main(void) {
    scanf("%d%d",&N,&K);
    ms(f,0),p[0]=1;
    rep(i,1,500*500) p[i]=2*p[i-1]%M;
    rep(i,0,N) f[i][0]=1;
    rep(i,1,N)rep(k,1,min(i,K))rep(j,0,i-1) {
        ll t=(ll)p[(i-j)*j]*(p[i-j]-1)%M;
        (f[i][k]+=(ll)f[j][k-1]*t%M)%=M;
    }
    printf("%d",f[N][K]);
    return 0;
}

