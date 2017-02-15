#include<iostream>
#include<cstdio>
using namespace std;

#define rep(i,a,b) for(int i=int(a),n##i=int(b);i<=n##i;i++)
#define MOD 1000000007

long long c,t,n,I;

int main(void) {
    cin>>n;
    rep(i,1,n) cin>>t,c+=(t==1);
    I=1;
    for(long long I1=1,I2=1,i=2;i<=c;i++)
        I=(I1+I2*(i-1)%MOD)%MOD,I2=I1,I1=I;
    rep(i,c+1,n) I=(I*i)%MOD;
    cout<<I;
    return 0;
}
