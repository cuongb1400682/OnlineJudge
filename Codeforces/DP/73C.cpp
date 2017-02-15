/*
 * PROB: Codeforces - 73C - LionAge II
 * LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

#define REP(i,a,b) \
    for (int i=int(a),n##i=int(b);i<=n##i;i++)
#define INF 0x3f3f3f3f

int nS,n,k,bonus[27][27],f[200][200][200];
char s[101];

int solve(int k,int x,int h) {
    if (k<0) return 0;
    if (f[k][x][h]!=-1) return f[k][x][h];
    int ans=solve(k-1,s[k]-'a',h)+bonus[s[k]-'a'][x];
    REP(c,'a','z') {
        if (h==0) break;
        ans=max(ans,solve(k-1,c-'a',h-1)+bonus[c-'a'][x]);
    }
    return f[k][x][h]=ans;
}

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt","rt",stdin);
    freopen("output.txt","wt",stdout);
#endif
    scanf("%s%n%d%d",s,&nS,&k,&n);
    REP(i,1,n) {
        char c1,c2; int b;
        scanf(" %c %c %d ",&c1,&c2,&b);
        bonus[c1-'a'][c2-'a']=b;
    }
    memset(f,-1,sizeof f);
    cout << solve(nS-1,26,k);
    return 0;
}
