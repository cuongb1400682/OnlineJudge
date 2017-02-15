/*
 * PROB: Codeforces - 436D - Pudding Monsters
 * LANG: C++
 */

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=int(a);i<=int(b);i++)
#define per(i,a,b) for(int i=int(a);i>=int(b);i--)
#define ms(a,v) memset(a,v,sizeof a)

int n,m,a[100005],b[2005],d[100005],z[100005],L[100005];

inline void upd(int &a,int b) { if(a<b) a=b; }

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt","rt",stdin);
    freopen("output.txt","wt",stdout);
#endif
    while(cin>>n>>m) {
        rep(i,1,n) cin>>a[i];
        rep(i,1,m) cin>>b[i];
        sort(a+1,a+n+1);
        sort(b+1,b+m+1);
        ms(d,0),ms(z,0),ms(L,0);
        rep(i,1,n) {
            if(i>1 && a[i]-1==a[i-1]) L[i]=L[i-1]; else L[i]=i;
            int x=upper_bound(b+1,b+m+1,a[i])-b;
            upd(d[i],z[L[i]-1]);
            per(j,x,1) {
                if(i<=a[i]-b[j]) break;
                upd(d[i],z[L[i-a[i]+b[j]]-1]+x-j);
            }
            upd(z[i],max(z[i-1],d[i]));
            rep(j,x,m) {
                if(i+b[j]-a[i]>n) break;
                upd(z[i+b[j]-a[i]],d[i]+j-x+1);
            }
        }
        cout<<z[n]<<endl;
    }
    return 0;
}
