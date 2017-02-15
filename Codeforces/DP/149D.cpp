/*
 * PROB: Codeforces - 149D - Coloring Brackets
 * LANG: C++
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <stack>
using namespace std;

#define rp(i,a,b) \
    for (int i=int(a),n##i=int(b);i<=n##i;i++)
#define SZ 800
#define BLACK 0
#define GREEN 1
#define RED   2
#define MOD 1000000007

typedef long long ll;

int partner[SZ], n;
ll f[SZ][SZ][3][3];
char s[SZ+1];

void analyse() {
    stack<int> stk;
    memset(partner,-1,sizeof partner);
    rp(i,0,strlen(s)-1)
        if(s[i]=='(')
            stk.push(i);
        else {
            partner[i] = stk.top();
            partner[stk.top()] = i;
            stk.pop();
        }
}

ll color(int p1, int p2, int c1, int c2) {
    ll& ans = f[p1][p2][c1][c2];
    if (p2==p1+1 && c1!=c2)
        return ans=1;
    if (ans!=-1)
        return ans;
    ans=0;
    ll BR, BG, RB, GB;
    for (int L=p1+1,R=partner[L],cnt=1; L<R; L=R+1,R=partner[L],cnt++) {
        if (cnt==1) {
            BR=color(L,R,BLACK,RED) % MOD;
            BG=color(L,R,BLACK,GREEN) % MOD;
            RB=color(L,R,RED,BLACK) % MOD;
            GB=color(L,R,GREEN,BLACK) % MOD;
            if (c1==RED) RB=0;
            if (c1==GREEN) GB=0;
        } else {
            ll a = color(L,R,BLACK,GREEN) % MOD;
            ll b = color(L,R,BLACK,RED) % MOD;
            ll c = color(L,R,GREEN, BLACK) % MOD;
            ll d = color(L,R,RED, BLACK) % MOD;

            ll BG_=(BG+BR+GB+RB)%MOD;
            ll BR_=(BG+BR+GB+RB)%MOD;
            ll GB_=(BR+GB+RB)%MOD;
            ll RB_=(BG+GB+RB)%MOD;

            BG=(BG_*a)%MOD, BR=(BR_*b)%MOD, GB=(GB_*c)%MOD, RB=(RB_*d)%MOD;
        }
    }
    if (c2==RED) BR=0;
    if (c2==GREEN) BG=0;
    return ans=(BG+BR+GB+RB)%MOD;
}

ll solve() {
    memset(f,-1,sizeof f);
    return color(0,n-1,BLACK, BLACK);
}

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif
    scanf("%700s",s+1);
    n = strlen(s+1);
    s[0]='(', s[n+1]=')', n+=2;
    analyse();
    cout << solve() << endl;
    return 0;
}
