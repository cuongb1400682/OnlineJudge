/*
 * PROB: Codeforces - 383D - Antimatter
 * LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

#define rep(i,a,b) for(int i=int(a);i<=int(b);i++)
#define ms(a,v) memset(a,v,sizeof a)
#define SZ 1001
#define CPL int(1e4)
#define MOD (int(1e9)+7)

int n,a[SZ],f[SZ][2][20001];

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt","rt",stdin);
    freopen("output.txt","wt",stdout);
#endif
    while(cin>>n) {
        ms(f,0);
        rep(i,1,n) cin>>a[i],f[i][1][a[i]+CPL]=f[i][0][CPL-a[i]]=1;
        int sum=a[1];
        rep(i,2,n) {
            sum+=a[i];
            rep(b,0,1)
                rep(S,a[i],sum+CPL) {
                    int& tt=f[i][b][S];
                    if(b==1)
                        tt+=f[i-1][1][S-a[i]]+f[i-1][0][S-a[i]];
                    else
                        tt+=f[i-1][1][S+a[i]]+f[i-1][0][S+a[i]];
                    if(tt>=MOD) tt-=MOD;
                }
        }
        int ans=0;
        // add f[][][] to 'ans' separately
        rep(i,1,n) (ans+=f[i][0][CPL])%=MOD,(ans+=f[i][1][CPL])%=MOD;
        cout<<ans<<endl;
    }
    return 0;
}
