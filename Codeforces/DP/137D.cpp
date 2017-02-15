/*
 * PROB: Codeforces - 137D - Palindromes
 * LANG: C++
 */

#include <bits/stdc++.h>
using namespace std;

#define SZ 501
#define INF 1000000000
#define RP(i,a,b) \
        for (int i=int(a),n##i=int(b);i<=n##i;i++)
#define MS(a,n) memset(a,n,sizeof(a))

char s[SZ];
int k, n, h[SZ][SZ], f[SZ][SZ], prev[SZ][SZ];

int d(int lo, int hi) {
    if (lo>hi) swap(lo,hi);
    int& ans=h[lo][hi];
    if (ans!=-1) return ans;
    for (ans=0; lo<hi; lo++,hi--)
        if (s[lo]!=s[hi]) ans++;
    return ans;
}

void init() {
    MS(h,-1);
    MS(prev,-1);
    n=strlen(s);
    RP(i,0,n) RP(k,0,n) {
        f[i][k]=INF;
        d(i,k);
    }
}

int solve(int i, int K) {
    if (K>i+1) return INF;
    if (f[i][K]!=INF)
        return f[i][K];
    int& ans=f[i][K]=h[0][i];
    if (K<=1) return ans;
    for (int m=0,tmp; m<i; m++) {
        tmp=solve(m,K-1)+h[m+1][i];
        if (ans>tmp)
            ans=tmp, prev[i][K]=m;
    }
    return ans;
}

void change(int L, int R) {
    for (; L<R; L++,R--)
        if (s[L]!=s[R]) s[L]=s[R];
}

void print(int i, int k) {
    if (i<0)
        return;
    else {
        print(prev[i][k], k-1);
        change(prev[i][k]+1,i);
        for (int h=prev[i][k]+1; h<=i; h++)
            putchar(s[h]);
        if (i!=n-1) putchar('+');
    }
}

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif
    int ans, i, KK;
    while (~scanf("%s%d",s,&k)) {
        init();
        for (i=1,ans=INF; i<=k; i++)
            if (ans>solve(n-1,i))
                ans=solve(n-1,i), KK=i;
        cout<<ans<<endl;
        print(n-1,KK);
    }
    return 0;
}
