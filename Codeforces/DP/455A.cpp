/*
 * PROB: Codeforces - 455A - Boredom
 * LANG: C++
 */

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=int(a),n##i=int(b);i<=n##i;i++)
#define ms(f,a) memset(f,a,sizeof f)
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define SZ 100010

typedef long long ll;

ll f[SZ];

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt","rt",stdin);
    freopen("output.txt","wt",stdout);
#endif
    for(ll n,val,ans,lim;cin>>n;) {
        ms(f,0);
        rep(i,1,n) cin>>val,f[val]+=val;
        ans=0;
        rep(i,3,1e5) {
            f[i]+=max(f[i-2],f[i-3]);
            ans=max(f[i],ans);
        }
        cout<<ans<<endl;
    }
    return 0;
}
