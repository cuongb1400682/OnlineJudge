/*
 * PROB: Codeforces - 331C2/331C3 - The Great Julya Calendar
 * LANG: C++
 */

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=int(a),n##i=int(b);i<=n##i;i++)
#define ms(f,a) memset(f,a,sizeof f)
#define INF 0x3f3f3f3f

typedef long long ll;
typedef pair<ll,int> ii;

map<ii,ii> h;

ii solve(ll val,int mx) {
    ii ans(0,0),st(val,mx);
    if(val==0) return ans;
    if(val<10) {
        ans=ii(1,0);
        if(val<mx) ans.second=val-mx;
        return ans;
    }
    map<ii,ii>::iterator it=h.find(st);
    if(it!=h.end()) return it->second;
    for(;;) {
        ll p10=1;
        for(ll i=val;i>=10;i/=10,p10*=10)
            ;
        int new_max=mx;
        if(new_max<val/p10) new_max=val/p10;
        ii tt=solve(val%p10,new_max);
        ans.first+=tt.first;
        val-=val%p10;
        if(tt.second<0)
            val+=tt.second;
        else {
            val-=new_max;
            ans.first++;
        }
        if(val<=0) break;
    }
    ans.second=val;
    h[st]=ans;
    return ans;
}

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif
    for(ll n;cin>>n;) {
        h.clear();
        cout<<solve(n,0).first<<endl;
    }
    return 0;
}
