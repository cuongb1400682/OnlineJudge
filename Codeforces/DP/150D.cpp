/*
 * PROB: Codeforces - 150D - Mission Impassable
 * LANG: C++
 */

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=int(a),n##i=int(b);i<=n##i;i++)
#define ms(f,a) memset(f,a,sizeof(f))
#define INF 0x3f3f3f3f

typedef long long ll;

int n,a[155],f[155][155][155],g[155][155];
bool vis[155][155];
char s[155];

void solve(int l,int r) {
    if(l>r) return;
    if(vis[l][r]) return;
    vis[l][r]=true;
    if(l==r) {
        f[l][r][0]=a[1];
        f[l][r][1]=0;
        g[l][r]=max(0,a[1]);
        return;
    }
    if(l+1==r && s[l]==s[r])
        f[l][r][2]=0;
    if(r-l+1>=3) solve(l+1,r-1);
    rep(m,l,r-1) {
        solve(l,m);
        solve(m+1,r);
    }
    rep(len,1,r-l+1) {
        rep(m,l+1,r) {
            if(f[l][m-1][0]>-1 && f[m][r][len]>-1)
                f[l][r][len]=max(f[l][r][len],f[l][m-1][0]+f[m][r][len]);
            if(f[l][m-1][len]>-1 && f[m][r][0]>-1)
                f[l][r][len]=max(f[l][r][len],f[l][m-1][len]+f[m][r][0]);
        }
        if(len>1 && s[l]==s[r] && f[l+1][r-1][len-2]>-1)
            f[l][r][len]=max(f[l][r][len],f[l+1][r-1][len-2]);
        if(a[len]>-1&&f[l][r][len]>-1)
            f[l][r][0]=max(f[l][r][0],f[l][r][len]+a[len]);
    }
    g[l][r]=f[l][r][0];
    rep(m,l,r-1) g[l][r]=max(g[l][r],g[l][m]+g[m+1][r]);
}

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt","rt",stdin);
    freopen("output.txt","wt",stdout);
#endif
    while(cin>>n) {
        rep(i,1,n) cin>>a[i];
        (cin>>(s+1)).ignore(); s[0]='*';
        ms(f,-1),ms(g,-1),ms(vis,false);
        solve(1,n);
        if(g[1][n]==-1)
            cout<<0<<endl;
        else
            cout<<g[1][n]<<endl;
    }
    return 0;
}
