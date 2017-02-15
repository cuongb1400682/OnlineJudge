#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define N 20

int dp[N][N],n,m,a[N];

int main(){
    int n_test;
    scanf("%d",&n_test);
    for(int no=1;no<=n_test;no++){
        scanf("%d%d",&n,&m);
        memset(dp,0,sizeof(dp));
        for(int i=0;i<n;i++){
            scanf("%d",&a[i]);
            dp[1][a[i]]=1;
        }
        for(int len=1;len<=m-1;len++){
            for(int i=0;i<n;i++){
                if(dp[len][a[i]]==0)continue;
                for(int j=0;j<n;j++){
                    if(abs(a[j]-a[i])>2)continue;
                    dp[len+1][a[j]]+=dp[len][a[i]];
                }
            }
        }
        int ans=0;
        for(int i=0;i<n;i++)
            ans+=dp[m][a[i]];
        printf("Case %d: %d\n",no,ans);
    }
    return 0;
}

