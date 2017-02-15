/*
 * PROB: Codeforces - 17C - Balance
 * LANG: C++
 */

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=int(a),n##i=int(b);i<=n##i;i++)
#define xep(i,a,b) for(int i=int(a),n##i=int(b);i>=n##i;i--)
#define ms(f,a) memset(f,a,sizeof f)
#define MOD 51123987

typedef long long ll;

int N,M,f[155][55][55][55],nx[155][3];
char s[155],x[155];

void init() {
    ms(f,0),ms(nx,0),x[0]='*';
    M=0;
    rep(i,1,N) if(s[i]!=x[M]) x[++M]=s[i];
    x[M+1]='\0';
    xep(i,M,1) {
        nx[i][0]=nx[i+1][0];
        nx[i][1]=nx[i+1][1];
        nx[i][2]=nx[i+1][2];
        nx[i][x[i]-'a']=i;
    }
}

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt","rt",stdin);
    freopen("output.txt","wt",stdout);
#endif
    while(~scanf("%d %s",&N,s+1)) {
        init();
        int lim=(N+2)/3,j,tt;
        f[1][0][0][0]=1;
        int ans=0;
        rep(i,1,M) {
            rep(kA,0,lim)rep(kB,0,lim)rep(kC,0,lim) {
                tt=f[i][kA][kB][kC];
                (f[nx[i][0]][kA+1][kB][kC]+=tt)%=MOD;
                (f[nx[i][1]][kA][kB+1][kC]+=tt)%=MOD;
                (f[nx[i][2]][kA][kB][kC+1]+=tt)%=MOD;
                if((kA+kB+kC==N)&&abs(kA-kB)<2&&abs(kA-kC)<2&&abs(kC-kA)<2)
                    (ans+=tt)%=MOD;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
