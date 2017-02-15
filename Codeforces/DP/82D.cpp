/*
 * PROB: Codeforces - 82D - Two out of Three
 * LANG: C++
 */

#include <bits/stdc++.h>
using namespace std;

#define SZ 1001
#define INF 0x3f3f3f3f
#define rep(i,a,b) for(int i=int(a);i<=int(b);i++)
#define ms(a,v) memset(a,v,sizeof a)
#define min3(a,b,c) min(a,min(b,c))

int n,a[SZ],f[SZ][SZ];
int t[SZ][SZ];
bitset<SZ> vis;

int solve(int i,int k) {
    if(i>k) swap(i,k);
    if(i>n) return 0;
    if(k>n) return a[i];
    int& ans=f[i][k];
    if(ans!=INF) return ans;
    int t1=solve(k+1,k+2)+max(a[i],a[k]);
    int t2=solve(k,k+2)+max(a[i],a[k+1]);
    int t3=solve(i,k+2)+max(a[k],a[k+1]);
    t[i][k]=1;
    if(t2<t1) t1=t2,t[i][k]=2;
    if(t3<t1) t1=t3,t[i][k]=3;
    return ans=t1;
}

void bk(int i,int k) {
    if(i>k) swap(i,k);
    if(i>n||k>n) return;
    if(t[i][k]==1) {
        cout<<i<<" "<<k<<endl;
        vis[i]=vis[k]=true;
        bk(k+1,k+2);
    } else if(t[i][k]==2) {
        cout<<i<<" "<<k+1<<endl;
        vis[i]=vis[k+1]=true;
        bk(k,k+2);
    } else {
        cout<<k<<" "<<k+1<<endl;
        vis[k]=vis[k+1]=true;
        bk(i,k+2);
    }
}

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt","rt",stdin);
    freopen("output.txt","wt",stdout);
#endif
    while(cin>>n) {
        ms(a,0); ms(f,0x3f); ms(t,0);
        rep(i,1,n) cin>>a[i];
        int ans=solve(1,2);
        cout<<ans<<endl;
        vis.reset();
        bk(1,2);
        rep(i,1,n) if(!vis[i]) {cout<<i<<endl;break;}
        cout<<endl;
    }
    return 0;
}
