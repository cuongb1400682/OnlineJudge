#include<stdio.h>
#include<string.h>
#include<algorithm>

#define N 16
#define INF 0x3f3f3f3f

int dp[1<<N],n,life[N],damage[N][N];
char line[N];

inline int min(int a,int b){
    return a>b?b:a;
}

inline int cost(int a,int b){
    return (a/b)+(a%b>0);
}

int solve(int st){
    if(dp[st]!=-1)
        return dp[st];
    int ans=INF;
    for(int i=0;i<n;i++){
        if(((st>>i)&1)==0)continue;
        for(int j=0;j<n;j++){
            if(((st>>j)&1)||damage[j][i]==0)continue;
            ans=min(ans,solve(st-(1<<i))+cost(life[i],damage[j][i]));
        }            
    }
    return dp[st]=ans;
}

int main(){
    int n_case;
    scanf("%d",&n_case);
    for(int no=1;no<=n_case;no++){
        scanf("%d",&n);
        for(int i=0;i<n;i++)
            scanf("%d",&life[i]);
        memset(damage,0,sizeof(damage));
        for(int i=0;i<n;i++){
            scanf("%s",line);
            for(int j=0;j<n;j++)
                damage[i][j]=line[j]-'0';
        }
        memset(dp,-1,sizeof(dp));
        dp[0]=0;
        n++;
        life[n-1]=0;
        for(int i=0;i<n-1;i++)
            damage[n-1][i]=1;
        printf("Case %d: %d\n",no,solve((1<<n)-1-(1<<(n-1))));
    }
    return 0;
}
