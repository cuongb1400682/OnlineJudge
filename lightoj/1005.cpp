#include<stdio.h>
#include<string.h>

typedef long long ll;

int n_test,n,k;
ll f[31][901];

ll gcd(ll a,ll b){
    while(a&&b){
        if(a>b)
            a%=b;
        else
            b%=a;
    }
    return a+b;
}

ll muldiv(ll n1,ll n2,ll d){
    ll g1=gcd(n1,d);
    n1/=g1;
    d/=g1;
    ll g2=gcd(n2,d);
    n2/=g2;
    d/=g2;
    return n1*n2/d;
}

ll solve(int n,int k){
    if(k<=0)return 1LL;
    if(k>n)return 0LL;
    if(k==1)return n*n;
    if(f[n][k]!=-1)return f[n][k];
    return f[n][k]=muldiv(solve(n,k-1),(n-k+1)*(n-k+1),k);
}

int main(){
    scanf("%d",&n_test);
    memset(f,-1,sizeof(f));
    for(int no=1;no<=n_test;no++){
        scanf("%d%d",&n,&k);
        printf("Case %d: %lld\n",no,solve(n,k));
    }
    return 0;
}
