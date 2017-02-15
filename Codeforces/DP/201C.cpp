/*
 * PROB: Codeforce - 201C - Fragile Bridges
 * LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

#define SZ 100001

typedef long long ll;

int n,a[SZ];
ll L[SZ],R[SZ];

void readf() {
    scanf("%d",&n);
    for (int i=1;i<=n-1;i++) scanf("%d",&a[i]);
}

void pre_calc() {
    ll val=0,even=0;
    for (int i=1;i<=n-1;i++) {
        even+=a[i]&(~1);
        if (a[i]==1) even=0;
        val+=a[i];
        if (!(a[i]&1)) val--;
        if (val<even) val=even;
        L[i]=val;
    }
    val=even=0;
    for (int i=n-1;i>=1;i--) {
        even+=a[i]&(~1);
        if (a[i]==1) even=0;
        val+=a[i];
        if (!(a[i]&1)) val--;
        if (val<even) val=even;
        R[i]=val;
    }
}

ll solve() {
    ll ans=R[1];
    for (int i=1;i<=n-1;i++)
        ans=max(ans,L[i]+R[i]-a[i]);
    return ans;
}

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt","rt",stdin);
    freopen("output.txt","wt",stdout);
#endif
    readf();
    pre_calc();
    cout<<solve();
    return 0;
}
