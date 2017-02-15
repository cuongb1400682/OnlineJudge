/*
 * PROB: Codeforces - 366C - Dima and Salad
 * LANG: C++
 */

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=int(a),n##i=int(b);i<=n##i;i++)
#define ms(a,b) memset(a,b,sizeof a)
#define INF 0x3f3f3f3f

typedef pair<int,int> ii;

int n,k,a[105],d[105][200005],b;

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt","rt",stdin);
    freopen("output.txt","wt",stdout);
#endif
    while(cin>>n>>k) {
        int p=100000;
        rep(i,1,n) cin>>a[i];
        ms(d,-0x3f);
        d[0][p]=0;
        rep(i,1,n) {
            cin>>b;b=a[i]-b*k;
            for(int j=0;j<=2*p;j++)
                if(j-b>=0)
                    d[i][j]=max(d[i-1][j],d[i-1][j-b]+a[i]);
        }
        cout<<(d[n][p]?d[n][p]:-1)<<endl;
    }
    return 0;
}

