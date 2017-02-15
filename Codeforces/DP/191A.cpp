/*
 * PROB: Codeforces - 191A - Dynasty Puzzles
 * LANG: C++
 */

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=int(a),n##i=int(b);i<=n##i;i++)
#define ms(f,a) memset(f,a,sizeof f)
#define INF 0x3f3f3f3f

int n,f[26][26],l,c0,cl;
char s[16];

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt","rt",stdin);
    freopen("output.txt","wt",stdout);
#endif
    while(~scanf("%d\n",&n)) {
        ms(f,0);
        while(n--) {
            for(l=0;(s[l++]=getchar())!='\n';);l--;
            c0=s[0]-'a',cl=s[l-1]-'a';
            rep(c,0,25) if(f[c][c0] && f[c][cl]<f[c][c0]+l) f[c][cl]=f[c][c0]+l;
            if (f[c0][cl]<l) f[c0][cl]=l;
        }
        int ans=0;
        rep(i,0,25) if(ans<f[i][i]) ans=f[i][i];
        printf("%d\n",ans);
    }
    return 0;
}
