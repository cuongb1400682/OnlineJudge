/*
 * PROB: Codeforces - 49E - Common ancestor
 * LANG: C++
 */

// LESSON: DEBUG DEBUG DEBUG

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=int(a),n##i=int(b);i<=n##i;i++)
#define ms(f,a) memset(f,a,sizeof f)
#define SZ 55
#define INF 0x3f3f3f3f

char a[SZ],b[SZ];
int n,f[SZ][SZ],la,lb;
bool g1[SZ][SZ][256],g2[SZ][SZ][256];
string h[256][256];

void pre_calc(bool (*g)[SZ][256],char *a,int la) {
    rep(i,1,la) {
        g[i][i][a[i]]=true;
        if(i<la) {
            string& s=h[a[i]][a[i+1]];
            rep(j,0,s.size()-1)
                g[i][i+1][s[j]]=true;
        } }
    rep(l,2,la) {
        rep(i,1,la-l+1) {
            rep(k,i,i+l-2) {
                rep(c1,'a','z')rep(c2,'a','z') {
                    rep(m,0,h[c1][c2].size()-1) {
                        char c=h[c1][c2].at(m);
                        g[i][i+l-1][c]|=g[i][k][c1]&&g[k+1][i+l-1][c2];
                    } } } } }
}

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt","rt",stdin);
    freopen("output.txt","wt",stdout);
#endif
    for(char t1[2],t2[3];~scanf("%50s %50s",a+1,b+1);) {
        la=strlen(a+1),lb=strlen(b+1);
        scanf("%d",&n);
        rep(i,'a','z')rep(j,'a','z') h[i][j].clear();
        rep(i,1,n) {
            scanf("%1s -> %2s",t1,t2);
            h[(int)t2[0]][(int)t2[1]].push_back(*t1);
        }
        ms(g1,false),ms(g2,false);
        pre_calc(g1,a,la),pre_calc(g2,b,lb);
        ms(f,0x3f);
        f[0][0]=0;
        rep(i,1,la) f[i][1]=g1[1][i][b[1]]?1:INF;
        rep(i,1,lb) f[1][i]=g2[1][i][a[1]]?1:INF;
        rep(i,2,la) rep(j,2,lb) {
            rep(x,1,i) rep(y,1,j) {
                rep(c,'a','z') {
                    if(g1[x][i][c]&&g2[y][j][c])
                        f[i][j]=min(f[i][j],f[x-1][y-1]+1);
                }
            }
        }
        if(f[la][lb]>=INF)
            cout<<-1<<endl;
        else
            cout<<f[la][lb]<<endl;
    }
    return 0;
}
