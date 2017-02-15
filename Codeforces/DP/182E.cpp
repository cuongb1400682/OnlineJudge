/*
 * PROB: Codeforces - 182E - Wooden Fence
 * LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

#define MOD 1000000007

int f[101][2][3001],N,L,a[101][2];

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt","rt",stdin);
    freopen("output.txt","wt",stdout);
#endif
    cin>>N>>L;
    memset(f,0,sizeof f);
    for (int i=1;i<=N;i++) {
        cin>>a[i][0]>>a[i][1];
        f[i][0][a[i][0]]=1;
        if (a[i][0]!=a[i][1])
            f[i][1][a[i][1]]=1;
    }

    /*
     * LESSON: the order of parameters in f is the most important
     * when using bottom up technique
     */
    for (int l=0;l<=L;l++) // l must be evaluated increasingly
        for (int i=1;i<=N;i++)
            for (int b=0;b<=1;b++) {
                for (int k=1;k<=N;k++) {
                    if (i==k) continue;
                    for (int h=0;h<=1;h++) {
                        if (a[k][h]==a[i][1-b])
                            /*
                            - This is a slower style:
                            f[i][b][l]=(f[i][b][l]%MOD + f[k][h][l-a[i][b]]%MOD)%MOD
                            */
                            if ((f[i][b][l]+=f[k][h][l-a[i][b]])>=MOD)
                                f[i][b][l]-=MOD;
                        if (a[k][0]==a[k][1]) break;
                    }
                }
                if (a[i][0]==a[i][1]) break;
            }

    int ans=0;
    for (int i=1;i<=N;i++) {
        ans=(ans+f[i][0][L]%MOD)%MOD;
        if (a[i][0]!=a[i][1])
            ans=(ans+f[i][1][L]%MOD)%MOD;
    }
    cout<<ans;
    return 0;
}
