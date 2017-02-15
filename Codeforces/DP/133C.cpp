/*
 * PROB: Codeforces - 133C - Logo Turtle
 * LANG: C++
 */

#include<bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=int(a),n##i=int(b);i<=n##i;i++)

const int d[2]={1,-1};

string s;
int n,f[105][55][2];

inline void Max(int& a,int b) { if(a<b) a=b; }

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt","rt",stdin);
    freopen("output.txt","wt",stdout);
#endif
    while(cin>>s>>n) {
        memset(f,-0x80,sizeof f);
        int aaa=0;
        s='*'+s;
        f[0][0][0]=f[0][0][1]=0;
        rep(i,1,s.size()-1) {
            rep(j,0,n) {
                rep(k,0,1) {
                    if(s[i]=='T') {
                        rep(h,0,j) {
                            if(h&1)
                                Max(f[i][j][k],f[i-1][j-h][k]+d[k]);
                            else
                                Max(f[i][j][k],f[i-1][j-h][!k]);
                        }
                    } else {
                        rep(h,0,j) {
                            if(h&1)
                                Max(f[i][j][k],f[i-1][j-h][!k]);
                            else
                                Max(f[i][j][k],f[i-1][j-h][k]+d[k]);
                        }
                    }
                }
            }
        }
        int M=s.size()-1;
        Max(aaa,f[M][n][0]);
        Max(aaa,f[M][n][1]);
        cout<<aaa<<endl;
    }
    return 0;
}
