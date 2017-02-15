/*
 * PROB: Codeforces - 543A - Writing Code
 * LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

#define SZ 501

int n,m,b,mod,a,f[SZ][SZ];

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt","rt",stdin);
    freopen("output.txt","wt",stdout);
#endif
    while(cin>>n>>m>>b>>mod) {
        memset(f,0,sizeof f);
        for(int i=0;i<=b;i++) f[0][i]=1;
        for(int i=0;i<n;i++) {
            cin>>a;
            for(int j=1;j<=m;j++)
                for(int k=a;k<=b;k++) {
                    f[j][k]+=f[j-1][k-a];
                    if(f[j][k]>=mod) f[j][k]-=mod;
                }
        }
        cout<<f[m][b]<<endl;
    }
    return 0;
}
