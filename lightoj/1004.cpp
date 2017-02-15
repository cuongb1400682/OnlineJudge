#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;

int dp[2][105],n,val;

int main(){
    int n_case;
    scanf("%d",&n_case);
    for(int no=1;no<=n_case;no++){
        scanf("%d",&n);
        memset(dp,0,sizeof(dp));

        int value;
        for(int i=0,len=1;i<n;i++,len++){
            int curr=i&1;
            int prev=curr^1;
            for(int j=1;j<=len;j++){
                scanf("%d",&value);
                dp[curr][j]=max(dp[prev][j],dp[prev][j-1])+value;
            }
        }

        for(int i=n,len=n-1;i<2*n-1;i++,len--){
            int curr=i&1;
            int prev=curr^1;
            for(int j=1;j<=len;j++){
                scanf("%d",&value);
                dp[curr][j]=max(dp[prev][j],dp[prev][j+1])+value;
            }
        }
        
        printf("Case %d: %d\n",no,dp[0][1]);
    }
    return 0;
}
