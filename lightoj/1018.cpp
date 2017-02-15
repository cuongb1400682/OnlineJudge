#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;

#define N 20
#define INF 1000000000

typedef pair<int,int> ii;

int line[N][N],dp[1<<N],n;
ii P[N];

inline bool is_linear(ii p,ii q,ii r){
    return (q.first-p.first)*(r.second-p.second)==
        (q.second-p.second)*(r.first-p.first);
}

int solve(int st){
    if(dp[st]!=-1)return dp[st];
    int ans=INF;
    for(int i=0;i<n;i++){
        if(((st>>i)&1)==0)
            continue;
        for(int j=0;j<n;j++){
            if(((st>>j)&1)==0)
                continue;
            ans=min(ans,solve(st&(~line[i][j]))+1);
        }
        break;//why?
    }
    return dp[st]=ans;
}

int main(){
    int n_case;
    scanf("%d",&n_case);
    for(int no=1;no<=n_case;no++){
        scanf("%d",&n);
        for(int i=0;i<n;i++)
            scanf("%d%d",&P[i].first,&P[i].second);
        sort(P,P+n);
        n=unique(P,P+n)-P;
        memset(line,0,sizeof(line));
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++){
                if(i==j){
                    line[i][j]=1<<i;
                    continue;
                }
                for(int k=0;k<n;k++)
                    if(is_linear(P[i],P[j],P[k]))
                        line[i][j]|=(1<<k);
            }
        memset(dp,-1,sizeof(dp));
        for(int i=0;i<n;i++)
            dp[1<<i]=1;
        dp[0]=0;
        printf("Case %d: %d\n",no,solve((1<<n)-1));
    }
    return 0;
}
