#include<stdio.h>
#include<string.h>

#define N 16

int dp[N][1<<N],n,p[N][N];

int max(int a,int b){
    return a>b?a:b;
}

int solve(int i,int st){
    if(dp[i][st]!=-1)return dp[i][st];
    int ans=0;
    for(int j=0;j<n;j++)
        if((st>>j)&1)
            ans=max(ans,solve(i-1,st-(1<<j))+p[i][j]);
    return dp[i][st]=ans;
}

int main(){
    int n_case;
    scanf("%d",&n_case);
    for(int no=1;no<=n_case;no++){
        scanf("%d",&n);
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                scanf("%d",&p[i][j]);
        memset(dp,-1,sizeof(dp));
        for(int i=0;i<n;i++)
            dp[0][1<<i]=p[0][i];
        printf("Case %d: %d\n",no,solve(n-1,(1<<n)-1));
    }
    return 0;
}
