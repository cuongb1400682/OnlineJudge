/*
 * PROB: Codeforces - 18E - Flag 2
 * LANG: C++
 */

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=int(a),n##i=int(b);i<=n##i;i++)
#define ms(f,a) memset(f,a,sizeof f)
#define INF 0x3f3f3f3f
#define SZ 505

int n,m,d[26][26],f[SZ][26][26],t[SZ][26][26],ln[SZ];
char buf[SZ];

int diff(int c1,int c2) {
    if(c1==c2) return INF;
    int ans=0;
    for(int i=1;i<=m;i+=2) {
        ans+=(ln[i]!=c1);
        if(i+1<=m) ans+=(ln[i+1]!=c2);
    }
    return ans;
}

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt","rt",stdin);
    freopen("output.txt","wt",stdout);
#endif
    while(cin>>n>>m) {
        ms(f,0),ms(d,0);
        rep(i,1,n) {
            // cin -> buf
            (cin>>(buf+1)).ignore();
            rep(j,1,m) ln[j]=buf[j]-'a';
            // tno changes d[][]
            rep(c1,0,25)rep(c2,0,25) d[c1][c2]=diff(c1,c2);
            // DP
            if(i==1) {
                memcpy(f[1],d,sizeof d);
            } else {
                rep(c1,0,25)rep(c2,0,25) { // CURRENT row
                    int tmp=INF,zz,zzz;
                    if(c1!=c2) rep(c3,0,25)rep(c4,0,25) { // PREVIOUS row
                        if(c3!=c4&&c3!=c1&&c4!=c2)
                            if(tmp>f[i-1][c3][c4]+d[c1][c2]) {
                                tmp=f[i-1][c3][c4]+d[c1][c2];
                                zz=c3,zzz=c4;
                            }
                    }
                    f[i][c1][c2]=tmp;
                    t[i][c1][c2]=zz*100+zzz;
                }
            }
        }
        int ans=INF,zz,zzz;
        rep(c1,0,25)rep(c2,0,25) if(ans>f[n][c1][c2])
            ans=f[n][c1][c2],zz=c1,zzz=c2;
        cout<<ans<<endl;
        string s="";
        for(int i=n;i>0;i--) {
            char c1=zz+'a',c2=zzz+'a';
            string ts="";
            for(int j=1;j<=m;j+=2) {
                ts.push_back(c1);
                if(j+1<=m) ts.push_back(c2);
            }
            s=ts+'\n'+s;
            // trace backward
            c1=t[i][zz][zzz]/100;
            c2=t[i][zz][zzz]%100;
            zz=c1,zzz=c2;
        }
        cout<<s<<endl;
    }
    return 0;
}
