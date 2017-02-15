#include<stdio.h>

typedef long long ll;

ll n_case,W;

int main(){
    scanf("%lld",&n_case);
    for(ll no=1;no<=n_case;no++){
        scanf("%lld",&W);
        ll n_even=1;
        while(W%2==0){
            n_even<<=1;
            W>>=1;
        }
        printf("Case %lld: ",no);
        if(n_even==1)
            puts("Impossible");
        else
            printf("%lld %lld\n",W,n_even);
    }
    return 0;
}
