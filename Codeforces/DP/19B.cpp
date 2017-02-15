#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

#define SZ 2002

typedef long long ll;

int n,w[SZ],p[SZ];
ll f[2][SZ];

ll solve() {
    memset(f,0x3f,sizeof f);
    f[0][0]=f[1][0]=0;
    for(int i=w[0];i>=1;i--) f[0][i]=p[0];
    for(ll i=1;i<n;i++)
        for(ll k=2000,h=i&1;k>=1;k--) {
            f[h][k]=min(f[1-h][k],f[h][k+1]);
            if (k>=w[i])
                f[h][k]=min(f[h][k],f[1-h][k-w[i]]+p[i]);
        }
    ll ans=0x3f3f3f3f3f3f3f3f;
    for(int i=n;i<=2000;i++)
        ans=min(ans,f[(n-1)&1][i]);
    return ans;
}

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt","rt",stdin);
    freopen("output.txt","wt",stdout);
#endif
    while(cin>>n) {
        for(int i=0;i<n;i++) { cin>>w[i]>>p[i]; w[i]++; }
        cout<<solve();
    }
    return 0;
}
